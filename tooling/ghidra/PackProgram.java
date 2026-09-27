// Ghidra headless post-script. Usage: -postScript PackProgram.java <output.gzf>
import ghidra.app.script.GhidraScript;
import java.io.File;

public class PackProgram extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Expected output .gzf path");
        File output = new File(args[0]);
        File parent = output.getAbsoluteFile().getParentFile();
        if (parent != null && !parent.isDirectory() && !parent.mkdirs()) {
            throw new IllegalStateException("Could not create " + parent);
        }
        currentProgram.getDomainFile().packFile(output, monitor);
        println("Packed " + currentProgram.getName() + " to " + output + " (" + output.length() + " bytes)");
    }
}
