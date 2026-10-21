// Apply Il2CppDumper names and inspect a small game-logic sample.
// @category Nocturne
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.program.model.symbol.SourceType;
import com.google.gson.*;
import java.io.*;
import java.nio.charset.StandardCharsets;
import java.util.*;

public class ImportIL2CppSymbols extends GhidraScript {
    public void run() throws Exception {
        String[] args = getScriptArgs();
        JsonObject root;
        try (Reader reader = new InputStreamReader(new FileInputStream(args[0]), StandardCharsets.UTF_8)) {
            root = JsonParser.parseReader(reader).getAsJsonObject();
        }
        File dir = new File(args[1]);
        dir.mkdirs();
        var base = currentProgram.getImageBase();
        Set<String> selected = Set.of("datCalc$$datAddHp", "datCalc$$datAddMp", "datCalc$$datGetMaxHp",
            "datCalc$$datGetMaxMp", "datCalc$$datGetSkillKouka", "datCalc$$datCheckItemFull",
            "datCalc$$datAddItem", "datCalc$$datGetAisyo", "datCalc$$datCheckDying");
        List<ghidra.program.model.listing.Function> sample = new ArrayList<>();
        Set<Long> addresses = new HashSet<>();
        int labels = 0, failures = 0;
        try (PrintWriter index = writer(dir, "methods.tsv")) {
            index.println("rva\tva\tname\tsignature");
            for (JsonElement element : root.getAsJsonArray("ScriptMethod")) {
                monitor.checkCancelled();
                JsonObject m = element.getAsJsonObject();
                long rva = m.get("Address").getAsLong();
                String name = m.get("Name").getAsString();
                String signature = m.get("Signature").getAsString();
                var addr = base.add(rva);
                index.println(Long.toHexString(rva) + "\t" + addr + "\t" + name + "\t" + signature);
                if (!currentProgram.getMemory().contains(addr)) { failures++; continue; }
                String label = name.replace("$$", "__").replaceAll("[^A-Za-z0-9_$]", "_");
                try { createLabel(addr, label, addresses.add(rva), SourceType.IMPORTED); labels++; }
                catch (Exception ex) { failures++; }
                if (selected.contains(name)) {
                    setPlateComment(addr, "IL2CPP metadata: " + signature);
                    disassemble(addr);
                    var f = getFunctionAt(addr);
                    if (f == null) f = createFunction(addr, label);
                    if (f != null) sample.add(f);
                }
            }
        }
        DecompInterface dec = new DecompInterface();
        try {
            dec.openProgram(currentProgram);
            try (PrintWriter w = writer(dir, "samples.c")) {
                for (var f : sample) {
                    var result = dec.decompileFunction(f, 45, monitor);
                    w.println("/* " + f.getEntryPoint() + " " + f.getName() + " */");
                    if (result.decompileCompleted()) w.println(result.getDecompiledFunction().getC());
                    else w.println("/* " + result.getErrorMessage() + " */");
                }
            }
        } finally { dec.dispose(); }
        try (PrintWriter w = writer(dir, "summary.txt")) {
            w.println("Program: " + currentProgram.getName());
            w.println("SHA256: " + currentProgram.getExecutableSHA256());
            w.println("Language: " + currentProgram.getLanguageID());
            w.println("Image base: " + base);
            w.println("Applied method labels: " + labels);
            w.println("Unmapped or rejected labels: " + failures);
            w.println("Selected functions inspected: " + sample.size());
            w.println("Full native auto-analysis: not run; targeted disassembly and decompilation only.");
        }
        println("Imported " + labels + " labels, inspected " + sample.size() + " functions; failures=" + failures);
    }
    private PrintWriter writer(File dir, String name) throws Exception {
        return new PrintWriter(new OutputStreamWriter(new FileOutputStream(new File(dir, name)), StandardCharsets.UTF_8));
    }
}
