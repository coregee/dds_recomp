// Replace the language only in this disposable read-only headless project copy.
// @category Nocturne
import ghidra.app.script.GhidraScript;
import ghidra.program.model.pcode.PcodeOp;
import ghidra.program.model.lang.CompilerSpecID;
import ghidra.program.database.ProgramDB;
import ghidra.program.util.LanguageTranslator;
import ghidra.program.util.LanguageTranslatorAdapter;
import ghidra.util.task.TaskMonitor;
import java.lang.reflect.Method;
import java.io.File;

public class UsePatchedEELanguage extends GhidraScript {
    public void run() throws Exception {
        int count = currentProgram.getFunctionManager().getFunctionCount();
        int tx = currentProgram.startTransaction("Apply validated DIVU semantics in disposable export copy");
        try {
            // The public API forbids replacing a language with the same version.
            // Use Ghidra 12.1.2's default register/space translator explicitly;
            // this private call is scoped to the disposable headless copy.
            LanguageTranslator translator = LanguageTranslatorAdapter.getDefaultLanguageTranslator(
                currentProgram.getLanguage(), PatchedEELanguage.load(currentProgram,new File(getScriptArgs()[0])));
            if (translator == null) throw new AssertionError("Register/space translation failed");
            Method setter = ProgramDB.class.getDeclaredMethod("setLanguage",LanguageTranslator.class,
                CompilerSpecID.class,boolean.class,TaskMonitor.class);
            setter.setAccessible(true);
            setter.invoke(currentProgram,translator,currentProgram.getCompilerSpec().getCompilerSpecID(),true,monitor);
            boolean unsigned = false;
            for (PcodeOp op : getInstructionAt(toAddr(0x2c0c74)).getPcode()) {
                if (op.getOpcode() == PcodeOp.INT_SDIV || op.getOpcode() == PcodeOp.INT_SREM)
                    throw new AssertionError("DIVU is still signed");
                if (op.getOpcode() == PcodeOp.INT_REM) unsigned = true;
            }
            if (!unsigned || count != currentProgram.getFunctionManager().getFunctionCount())
                throw new AssertionError("DIVU patch/inventory check failed");
            println("Validated patched DIVU in disposable program; preserved " + count + " functions");
        } finally { currentProgram.endTransaction(tx,true); }
    }
}
