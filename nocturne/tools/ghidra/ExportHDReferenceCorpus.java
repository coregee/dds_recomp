// Export targeted native references in a disposable saved PC project copy.
// @category Nocturne
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.*;
import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.util.parser.FunctionSignatureParser;
import ghidra.program.model.address.*;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.pcode.*;
import com.google.gson.*;
import java.nio.file.*;
import java.util.*;
import java.util.concurrent.*;

public class ExportHDReferenceCorpus extends GhidraScript {
    private static final int VERSION=1;
    private Path output;
    private int timeout;
    private final Gson gson=new GsonBuilder().setPrettyPrinting().create();
    private final ThreadLocal<DecompInterface> dec=new ThreadLocal<>();
    private final Queue<DecompInterface> interfaces=new ConcurrentLinkedQueue<>();

    private JsonObject export(JsonObject spec,Function f) throws Exception {
        String key=spec.get("va").getAsString();
        JsonObject row=spec.deepCopy();row.addProperty("export_version",VERSION);
        if(f==null){row.addProperty("status","entry-unavailable");Files.writeString(output.resolve(key+".json"),gson.toJson(row)+"\n");return row;}
        row.addProperty("function_name",f.getName());row.addProperty("signature",f.getPrototypeString(false,true));
        row.addProperty("entry_body_bytes",f.getBody().getNumAddresses());
        DecompInterface iface=dec.get();
        if(iface==null){iface=new DecompInterface();if(!iface.openProgram(currentProgram))throw new IllegalStateException(iface.getLastMessage());dec.set(iface);interfaces.add(iface);}
        var result=iface.decompileFunction(f,timeout,monitor);
        boolean ok=result.decompileCompleted()&&result.getDecompiledFunction()!=null;
        row.addProperty("status",ok?"decompiled":"decompile-failed");row.addProperty("decompile_message",result.getErrorMessage());
        Map<String,Integer> ops=new TreeMap<>();Set<Long> constants=new TreeSet<>();Set<String> calls=new TreeSet<>();
        if(ok){
            String code=result.getDecompiledFunction().getC();Files.writeString(output.resolve(key+".c"),code);
            int locks=code.split("LOCK\\(",-1).length-1;
            row.addProperty("lock_calls",locks);row.addProperty("code_chars",code.length());
            var high=result.getHighFunction();var it=high.getPcodeOps();
            while(it.hasNext()){
                var op=it.next();ops.merge(PcodeOp.getMnemonic(op.getOpcode()),1,Integer::sum);
                for(int i=0;i<op.getNumInputs();i++)if(op.getInput(i).isConstant()){
                    long value=op.getInput(i).getOffset();if(value>=0&&value<0x100000)constants.add(value);
                }
                if(op.getOpcode()==PcodeOp.CALL)calls.add(op.getInput(0).getAddress().toString());
            }
            row.addProperty("opaque_lock_stub",locks>0&&ops.getOrDefault("LOAD",0)==0&&ops.getOrDefault("STORE",0)==0&&ops.getOrDefault("CALL",0)==0);
        }
        row.add("pcode_ops",gson.toJsonTree(ops));row.add("small_constants",gson.toJsonTree(constants));row.add("native_calls",gson.toJsonTree(calls));
        Files.writeString(output.resolve(key+".json"),gson.toJson(row)+"\n");return row;
    }

    public void run() throws Exception {
        String[] args=getScriptArgs();JsonObject root=JsonParser.parseString(Files.readString(Paths.get(args[0]))).getAsJsonObject();
        if(!currentProgram.getExecutableSHA256().equals(root.get("dll_sha256").getAsString()))throw new AssertionError("HD DLL hash differs");
        output=Paths.get(args[1]);Files.createDirectories(output);
        int workers=args.length>2?Integer.parseInt(args[2]):4;timeout=args.length>3?Integer.parseInt(args[3]):20;
        if(workers<1||workers>8||timeout<1)throw new IllegalArgumentException("Invalid limits");
        List<JsonObject> specs=new ArrayList<>();List<Function> functions=new ArrayList<>();
        var parser=new FunctionSignatureParser(currentProgram.getDataTypeManager(),null);
        int reused=0,prepared=0,unavailable=0,prototypeFailures=0;
        int tx=currentProgram.startTransaction("Prepare metadata-named native reference entries in disposable copy");
        try {
            for(JsonElement element:root.getAsJsonArray("entries")){
                monitor.checkCancelled();JsonObject spec=element.getAsJsonObject();String key=spec.get("va").getAsString();
                Path cached=output.resolve(key+".json");
                if(Files.exists(cached)){
                    JsonObject old=JsonParser.parseString(Files.readString(cached)).getAsJsonObject();
                    if(old.has("export_version")&&old.get("export_version").getAsInt()==VERSION&&old.get("spec_sha256").equals(spec.get("spec_sha256"))&&old.get("status").getAsString().equals("decompiled")&&Files.exists(output.resolve(key+".c"))){reused++;continue;}
                }
                Address address=toAddr(key);Function f=getFunctionAt(address);
                if(f==null&&getFunctionContaining(address)==null&&currentProgram.getMemory().contains(address)){
                    // Define only the entry instruction. Native decompilation reads
                    // and follows the original byte stream beyond the stub body;
                    // broad GUI auto-analysis is unnecessary for this export.
                    new DisassembleCommand(address,new AddressSet(address,address.add(31)),false).applyTo(currentProgram,monitor);
                    Instruction instruction=getInstructionAt(address);
                    if(instruction!=null){
                        String name=spec.getAsJsonArray("methods").get(0).getAsJsonObject().get("Name").getAsString().replace("$$","__").replaceAll("[^A-Za-z0-9_$]","_");
                        f=currentProgram.getFunctionManager().createFunction(name,address,new AddressSet(address,instruction.getMaxAddress()),SourceType.IMPORTED);
                    }
                }
                if(f!=null){
                    // Shared native bodies may have incompatible managed signatures.
                    // Apply primitive/opaque-pointer metadata only when all aliases agree.
                    Set<String> abi=new HashSet<>();String prototype=null;boolean missing=false;
                    for(JsonElement alias:spec.getAsJsonArray("methods")){
                        JsonElement p=alias.getAsJsonObject().get("prototype");
                        if(p==null||p.isJsonNull()){missing=true;continue;}
                        String proto=p.getAsString();String types=proto.replaceFirst("\\w+\\(","(").replaceAll("\\s+\\w+(?=[,)])","");abi.add(types);prototype=proto;
                    }
                    if(!missing&&abi.size()==1&&prototype!=null){
                        try{
                            var definition=parser.parse(f.getSignature(),prototype);definition.setCallingConvention("__fastcall");
                            if(!new ApplyFunctionSignatureCmd(address,definition,SourceType.IMPORTED,true,false).applyTo(currentProgram,monitor))prototypeFailures++;
                        }catch(Exception error){prototypeFailures++;spec.addProperty("prototype_error",error.getMessage());}
                    }else spec.addProperty("prototype_skipped","Shared/unsupported managed ABI");
                }else unavailable++;
                specs.add(spec);functions.add(f);prepared++;
                if(prepared%250==0)println("Prepared "+prepared+" native entries; reused "+reused);
            }
        }finally{currentProgram.endTransaction(tx,true);}
        Map<String,Object> summary=new LinkedHashMap<>();summary.put("dll_sha256",currentProgram.getExecutableSHA256());
        summary.put("requested_native_bodies",root.getAsJsonArray("entries").size());summary.put("reused",reused);summary.put("entry_unavailable",unavailable);
        summary.put("prototype_failures",prototypeFailures);summary.put("status","running");
        Files.writeString(output.resolve("summary.json"),gson.toJson(summary)+"\n");
        ExecutorService pool=Executors.newFixedThreadPool(workers);CompletionService<JsonObject> done=new ExecutorCompletionService<>(pool);
        int completed=0,success=0,opaque=0;
        try(var writer=Files.newBufferedWriter(output.resolve("index-current.jsonl"))){
            for(int i=0;i<specs.size();i++){final int n=i;done.submit(()->export(specs.get(n),functions.get(n)));}
            while(completed<specs.size()){
                monitor.checkCancelled();var future=done.poll(1,TimeUnit.SECONDS);if(future==null)continue;
                JsonObject row=future.get();writer.write(new Gson().toJson(row));writer.newLine();completed++;
                if(row.get("status").getAsString().equals("decompiled"))success++;
                if(row.has("opaque_lock_stub")&&row.get("opaque_lock_stub").getAsBoolean())opaque++;
                if(completed%100==0||completed==specs.size()){
                    writer.flush();summary.put("exported_this_run",completed);summary.put("decompiled_this_run",success);summary.put("opaque_lock_stubs_this_run",opaque);
                    Files.writeString(output.resolve("summary.json"),gson.toJson(summary)+"\n");println("Exported "+completed+"/"+specs.size()+" HD native bodies; decompiled "+success+"; opaque "+opaque);
                }
            }
            summary.put("status","complete");Files.writeString(output.resolve("summary.json"),gson.toJson(summary)+"\n");
        }finally{pool.shutdownNow();pool.awaitTermination(timeout+5,TimeUnit.SECONDS);for(var iface:interfaces)iface.dispose();}
    }
}
