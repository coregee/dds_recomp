// Write every function in the program as address, size, name and name source.
// Input for tools/function_map.py.
// @category Nocturne
import ghidra.app.script.GhidraScript;
import ghidra.program.model.listing.Function;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class ExportFunctionNames extends GhidraScript {
    @Override
    public void run() throws Exception {
        Path output = Path.of(getScriptArgs()[0]);
        Files.createDirectories(output.toAbsolutePath().getParent());
        try (BufferedWriter out = Files.newBufferedWriter(output, StandardCharsets.UTF_8)) {
            out.write("address\tsize\tname\tsource\n");
            for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                out.write(f.getEntryPoint() + "\t" + f.getBody().getNumAddresses() + "\t"
                    + f.getName() + "\t" + f.getSymbol().getSource() + "\n");
            }
        }
    }
}
