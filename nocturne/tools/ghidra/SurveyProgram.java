// Export a small reproducible inventory after analysis.
// @category Nocturne
import ghidra.app.util.headless.HeadlessScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.program.model.listing.*;
import java.io.*;
import java.nio.charset.StandardCharsets;

public class SurveyProgram extends HeadlessScript {
    public void run() throws Exception {
        File out = new File(getScriptArgs()[0]);
        out.mkdirs();
        try (PrintWriter w = writer(out, "summary.txt")) {
            w.println("Program: " + currentProgram.getName());
            w.println("Language: " + currentProgram.getLanguageID());
            w.println("Compiler: " + currentProgram.getCompilerSpec().getCompilerSpecID());
            w.println("SHA256: " + currentProgram.getExecutableSHA256());
            w.println("Image base: " + currentProgram.getImageBase());
            w.println("Functions: " + currentProgram.getFunctionManager().getFunctionCount());
            w.println("Instructions: " + currentProgram.getListing().getNumInstructions());
            w.println("Analysis timed out: " + analysisTimeoutOccurred());
            for (var b : currentProgram.getMemory().getBlocks())
                w.println("Block: " + b.getName() + " " + b.getStart() + "-" + b.getEnd() + " execute=" + b.isExecute());
        }
        try (PrintWriter w = writer(out, "functions.tsv")) {
            w.println("address\tname\tsize\tsignature");
            for (var f : currentProgram.getFunctionManager().getFunctions(true)) {
                monitor.checkCancelled();
                w.println(f.getEntryPoint() + "\t" + f.getName(true) + "\t" + f.getBody().getNumAddresses() + "\t" + f.getSignature());
            }
        }
        try (PrintWriter w = writer(out, "strings.tsv")) {
            w.println("address\tvalue");
            for (var d : currentProgram.getListing().getDefinedData(true)) {
                monitor.checkCancelled();
                if (d.getValue() instanceof String)
                    w.println(d.getAddress() + "\t" + ((String)d.getValue()).replace("\n", "\\n").replace("\r", "\\r").replace("\t", "\\t"));
            }
        }
        DecompInterface dec = new DecompInterface();
        try {
            dec.openProgram(currentProgram);
            try (PrintWriter w = writer(out, "samples.c")) {
                int n = 0;
                for (var f : currentProgram.getFunctionManager().getFunctions(true)) {
                    if (++n > 6) break;
                    var result = dec.decompileFunction(f, 30, monitor);
                    w.println("/* " + f.getEntryPoint() + " " + f.getName() + " */");
                    if (result.decompileCompleted()) w.println(result.getDecompiledFunction().getC());
                    else w.println("/* Decompilation failed: " + result.getErrorMessage() + " */");
                }
            }
        } finally { dec.dispose(); }
        println("Survey exported to " + out.getAbsolutePath());
    }
    private PrintWriter writer(File dir, String name) throws Exception {
        return new PrintWriter(new OutputStreamWriter(new FileOutputStream(new File(dir, name)), StandardCharsets.UTF_8));
    }
}
