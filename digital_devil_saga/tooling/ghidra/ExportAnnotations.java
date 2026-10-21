// Ghidra headless post-script. Usage: -postScript ExportAnnotations.java <output.tsv> <executable-sha256>
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressIterator;
import ghidra.program.model.listing.CommentType;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.listing.Variable;
import ghidra.program.model.symbol.SourceType;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolIterator;
import java.io.BufferedWriter;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class ExportAnnotations extends GhidraScript {
    private BufferedWriter out;
    private int rows;

    private String clean(String value) {
        if (value == null) return "";
        return value.replace("\\", "\\\\").replace("\t", "\\t")
            .replace("\r", "\\r").replace("\n", "\\n");
    }

    private void row(String kind, String address, String context, String name, String value)
            throws Exception {
        out.write(clean(kind) + "\t" + clean(address) + "\t" + clean(context)
            + "\t" + clean(name) + "\t" + clean(value) + "\n");
        rows++;
    }

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 2) throw new IllegalArgumentException("Expected output path and SHA256");
        Path output = Path.of(args[0]);
        Files.createDirectories(output.toAbsolutePath().getParent());
        Listing listing = currentProgram.getListing();
        try (BufferedWriter writer = Files.newBufferedWriter(output, StandardCharsets.UTF_8)) {
            out = writer;
            out.write("# program\t" + clean(currentProgram.getName()) + "\n");
            out.write("# executable_sha256\t" + clean(args[1]) + "\n");
            out.write("kind\taddress\tcontext\tname\tvalue\n");

            SymbolIterator symbols = currentProgram.getSymbolTable().getAllSymbols(false);
            while (symbols.hasNext()) {
                monitor.checkCancelled();
                Symbol symbol = symbols.next();
                if (symbol.getSource() == SourceType.USER_DEFINED) {
                    row("symbol", symbol.getAddress().toString(),
                        symbol.getSymbolType().toString(), symbol.getName(),
                        symbol.getParentNamespace().getName(true));
                }
            }

            FunctionIterator functions = listing.getFunctions(true);
            while (functions.hasNext()) {
                monitor.checkCancelled();
                Function function = functions.next();
                String address = function.getEntryPoint().toString();
                if (function.getSignatureSource() == SourceType.USER_DEFINED) {
                    row("signature", address, "", function.getName(),
                        function.getPrototypeString(false, true));
                }
                if (function.getComment() != null && !function.getComment().isEmpty()) {
                    row("function_comment", address, "", function.getName(), function.getComment());
                }
                for (Variable variable : function.getAllVariables()) {
                    if (variable.getSource() == SourceType.USER_DEFINED) {
                        row("variable", address, variable.getVariableStorage().toString(),
                            variable.getName(), variable.getDataType().getDisplayName());
                    }
                }
            }

            AddressIterator addresses = listing.getCommentAddressIterator(currentProgram.getMemory(), true);
            while (addresses.hasNext()) {
                monitor.checkCancelled();
                Address address = addresses.next();
                for (CommentType type : CommentType.values()) {
                    String comment = listing.getComment(type, address);
                    if (comment != null && !comment.isEmpty()) {
                        row("comment", address.toString(), type.toString(), "", comment);
                    }
                }
            }
        }
        println("Exported " + rows + " annotation rows to " + output);
    }
}
