// Export complete or selected functions directly from the saved project read-only.
// @category Nocturne
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.program.model.listing.*;
import ghidra.program.model.scalar.Scalar;
import ghidra.program.model.pcode.*;
import ghidra.program.model.symbol.Reference;
import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonParser;
import java.nio.file.*;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.util.concurrent.*;

public class ExportExecutableEvidence extends GhidraScript {
    private final Gson gson = new GsonBuilder().setPrettyPrinting().create();
    private Path output;
    private int timeout;
    private final ThreadLocal<DecompInterface> dec = new ThreadLocal<>();
    private final Queue<DecompInterface> interfaces = new ConcurrentLinkedQueue<>();

    private Map<String,Object> export(Function f) throws Exception {
        Map<String,Object> row = new LinkedHashMap<>();
        String address = f.getEntryPoint().toString();
        String key = address.replaceAll("[^A-Za-z0-9._-]", "_");
        row.put("address", address);
        row.put("name", f.getName(true));
        row.put("size", f.getBody().getNumAddresses());
        row.put("signature", f.getPrototypeString(false, true));
        row.put("signature_source", f.getSignatureSource().toString());
        row.put("symbol_source", f.getSymbol().getSource().toString());
        row.put("thunk", f.isThunk());
        row.put("comment", f.getRepeatableComment());
        List<String> callees = new ArrayList<>();
        for (Function called : f.getCalledFunctions(monitor)) callees.add(called.getEntryPoint().toString());
        Collections.sort(callees);
        row.put("callees", callees);
        Set<Long> scalars = new TreeSet<>();
        Set<String> strings = new TreeSet<>();
        Set<String> dataRefs = new TreeSet<>();
        StringBuilder assembly = new StringBuilder();
        int instructions = 0, branches = 0;
        for (Instruction inst : currentProgram.getListing().getInstructions(f.getBody(), true)) {
            instructions++;
            if (inst.getFlowType().isConditional()) branches++;
            assembly.append(inst.getAddress()).append(": ").append(inst).append('\n');
            for (int operand = 0; operand < inst.getNumOperands(); operand++) {
                for (Object object : inst.getOpObjects(operand))
                    if (object instanceof Scalar) scalars.add(((Scalar)object).getSignedValue());
            }
            for (Reference ref : inst.getReferencesFrom()) {
                if (ref.getReferenceType().isData()) {
                    dataRefs.add(ref.getToAddress().toString());
                    Data d = currentProgram.getListing().getDataContaining(ref.getToAddress());
                    if (d != null && d.getValue() instanceof String) strings.add((String)d.getValue());
                }
            }
        }
        row.put("instruction_count", instructions);
        row.put("conditional_branches", branches);
        row.put("scalars", scalars);
        row.put("strings", strings);
        row.put("data_refs", dataRefs);
        Files.writeString(output.resolve("functions").resolve(key + ".asm"), assembly, StandardCharsets.UTF_8);
        DecompInterface interfaceForThread = dec.get();
        if (interfaceForThread == null) {
            interfaceForThread = new DecompInterface();
            if (!interfaceForThread.openProgram(currentProgram)) throw new IllegalStateException(interfaceForThread.getLastMessage());
            interfaces.add(interfaceForThread);
            dec.set(interfaceForThread);
        }
        var result = interfaceForThread.decompileFunction(f, timeout, monitor);
        boolean ok = result.decompileCompleted() && result.getDecompiledFunction() != null;
        row.put("decompile_completed", ok);
        row.put("decompile_message", result.getErrorMessage());
        Map<String,Integer> ops = new TreeMap<>();
        if (ok) {
            Files.writeString(output.resolve("functions").resolve(key + ".c"), result.getDecompiledFunction().getC(), StandardCharsets.UTF_8);
            var high = result.getHighFunction();
            if (high != null) {
                var it = high.getPcodeOps();
                while (it.hasNext()) {
                    var op = it.next();
                    ops.merge(PcodeOp.getMnemonic(op.getOpcode()), 1, Integer::sum);
                }
            }
        } else {
            Files.writeString(output.resolve("functions").resolve(key + ".c"), "/* Decompilation failed: " + result.getErrorMessage() + " */\n", StandardCharsets.UTF_8);
        }
        row.put("pcode_ops", ops);
        Files.writeString(output.resolve("functions").resolve(key + ".json"), gson.toJson(row) + "\n", StandardCharsets.UTF_8);
        return row;
    }

    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length < 1) throw new IllegalArgumentException("Expected output directory [workers] [timeout seconds]");
        output = Path.of(args[0]);
        int workers = args.length > 1 ? Integer.parseInt(args[1]) : 3;
        timeout = args.length > 2 ? Integer.parseInt(args[2]) : 30;
        if (workers < 1 || workers > 8 || timeout < 1) throw new IllegalArgumentException("Invalid worker/timeout arguments");
        if (!"a26e86e59cab447d9b1839ec11ab82b1557230bcc99746b78e3b5d4359dcc6ff".equals(currentProgram.getExecutableSHA256()))
            throw new IllegalStateException("Unexpected executable; this export is scoped to the inspected Nocturne ELF");
        boolean divuUnsigned = false;
        for (PcodeOp op : getInstructionAt(toAddr(0x2c0c74)).getPcode())
            if (op.getOpcode() == PcodeOp.INT_REM) divuUnsigned = true;
        if (args.length > 3 && args[3].equals("require-unsigned-divu") && !divuUnsigned)
            throw new AssertionError("Corrected DIVU required; preserving existing exports");
        boolean partial = args.length > 4;
        boolean allowNewEntries = false;
        Set<String> selected = new HashSet<>(), retired = new HashSet<>();
        if (partial) {
            var specification = JsonParser.parseString(Files.readString(Path.of(args[4])));
            if(specification.isJsonObject()&&specification.getAsJsonObject().has("retired_entries"))
                for(var item:specification.getAsJsonObject().getAsJsonArray("retired_entries")){
                    String entry=item.getAsString();
                    if(!entry.matches("[0-9a-f]{8}")||currentProgram.getFunctionManager().getFunctionAt(toAddr(entry))!=null)throw new IllegalStateException("Retired entry still recognized or invalid");
                    retired.add(entry);
                }
            allowNewEntries = specification.isJsonObject()
                && specification.getAsJsonObject().has("allow_new_entries")
                && specification.getAsJsonObject().get("allow_new_entries").getAsBoolean();
            var entries = specification.isJsonArray() ? specification.getAsJsonArray()
                : specification.getAsJsonObject().getAsJsonArray("entries");
            for (var item : entries) selected.add(item.isJsonObject()
                ? item.getAsJsonObject().get("entry").getAsString() : item.getAsString());
            if (selected.isEmpty()) throw new IllegalArgumentException("Empty selected export");
        }
        Files.createDirectories(output.resolve("functions"));
        Map<String,Object> summary = new LinkedHashMap<>();
        summary.put("program", currentProgram.getName());
        summary.put("sha256", currentProgram.getExecutableSHA256());
        summary.put("language", currentProgram.getLanguageID().toString());
        summary.put("divu_unsigned", divuUnsigned);
        summary.put("function_count", currentProgram.getFunctionManager().getFunctionCount());
        summary.put("workers", workers);
        summary.put("timeout_seconds", timeout);
        summary.put("status", "running");
        Path summaryPath = output.resolve(partial ? "partial-export-summary.json" : "summary.json");
        Files.writeString(summaryPath, gson.toJson(summary) + "\n");
        ExecutorService pool = Executors.newFixedThreadPool(workers);
        CompletionService<Map<String,Object>> done = new ExecutorCompletionService<>(pool);
        List<Function> functions = new ArrayList<>();
        for (Function f : currentProgram.getFunctionManager().getFunctions(true))
            if (!partial || selected.contains(f.getEntryPoint().toString())) functions.add(f);
        if (partial && functions.size() != selected.size()) throw new IllegalArgumentException("Missing selected functions");
        summary.put("selected_functions", functions.size());
        int completed = 0, success = 0;
        Path indexPath = output.resolve(partial ? "partial-index.jsonl" : "index.jsonl");
        try (var writer = Files.newBufferedWriter(indexPath, StandardCharsets.UTF_8)) {
            for (Function f : functions) done.submit(() -> export(f));
            while (completed < functions.size()) {
                monitor.checkCancelled();
                var future = done.poll(1, TimeUnit.SECONDS);
                if (future == null) continue;
                Map<String,Object> row = future.get();
                writer.write(new Gson().toJson(row));
                writer.newLine();
                completed++;
                if (Boolean.TRUE.equals(row.get("decompile_completed"))) success++;
                if (completed % 100 == 0 || completed == functions.size()) {
                    writer.flush();
                    println("Exported " + completed + "/" + functions.size() + " functions; decompiled " + success);
                    summary.put("exported", completed);
                    summary.put("decompiled", success);
                    Files.writeString(summaryPath, gson.toJson(summary) + "\n");
                }
            }
            summary.put("status", "complete");
            summary.put("exported", completed);
            summary.put("decompiled", success);
            summary.put("failed", completed - success);
            Files.writeString(summaryPath, gson.toJson(summary) + "\n");
        } finally {
            pool.shutdownNow();
            pool.awaitTermination(timeout + 5, TimeUnit.SECONDS);
            for (var iface : interfaces) iface.dispose();
        }
        if (partial) {
            Map<String,String> replacements = new HashMap<>();
            for (String line : Files.readAllLines(indexPath))
                replacements.put(JsonParser.parseString(line).getAsJsonObject().get("address").getAsString(), line);
            List<String> merged = new ArrayList<>();
            for (String line : Files.readAllLines(output.resolve("index.jsonl"))) {
                String address = JsonParser.parseString(line).getAsJsonObject().get("address").getAsString();
                if(retired.contains(address))continue;
                merged.add(replacements.containsKey(address) ? replacements.remove(address) : line);
            }
            if (!replacements.isEmpty()) {
                if (!allowNewEntries) throw new IllegalStateException("Partial export has new entries; explicitly reviewed discovery refresh required");
                merged.addAll(replacements.values());
                merged.sort(Comparator.comparing(line -> JsonParser.parseString(line).getAsJsonObject().get("address").getAsString()));
            }
            Set<String> indexed = new HashSet<>(), recognized = new HashSet<>();
            for (String line : merged) indexed.add(JsonParser.parseString(line).getAsJsonObject().get("address").getAsString());
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) recognized.add(f.getEntryPoint().toString());
            if (indexed.size()!=merged.size() || !indexed.equals(recognized))
                throw new IllegalStateException("Rolling index differs from current recognized inventory");
            Files.write(output.resolve("index.jsonl"), merged, StandardCharsets.UTF_8);
            for(String entry:retired)for(String extension:new String[]{".json",".asm",".c"})Files.deleteIfExists(output.resolve("functions").resolve(entry+extension));
            Files.delete(indexPath);
            summary.put("inventory_merged", true);
            summary.put("rolling_index_entries", merged.size());
            summary.put("new_entries_allowed", allowNewEntries);
            Files.writeString(summaryPath, gson.toJson(summary) + "\n");
        }
    }
}
