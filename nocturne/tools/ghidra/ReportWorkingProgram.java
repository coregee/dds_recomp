// @category Nocturne
import ghidra.app.script.GhidraScript;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.LinkedHashMap;
import com.google.gson.GsonBuilder;

public class ReportWorkingProgram extends GhidraScript {
    public void run() throws Exception {
        var report = new LinkedHashMap<String, Object>();
        report.put("program", currentProgram.getName());
        report.put("domain_file", currentProgram.getDomainFile().getPathname());
        report.put("executable_sha256", currentProgram.getExecutableSHA256());
        report.put("recognized_functions", currentProgram.getFunctionManager().getFunctionCount());
        report.put("language", currentProgram.getLanguageID().toString());
        Files.writeString(Paths.get(getScriptArgs()[0]),
            new GsonBuilder().setPrettyPrinting().create().toJson(report) + "\n");
        println("Working project: " + report);
    }
}
