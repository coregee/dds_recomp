import ghidra.app.plugin.processors.sleigh.SleighLanguage;
import ghidra.program.model.lang.*;
import ghidra.program.model.listing.Program;
import generic.jar.ResourceFile;
import java.io.File;
import java.lang.reflect.Constructor;
import java.util.Map;

/** Load the validated workspace language without replacing the installed extension. */
public class PatchedEELanguage {
    public static SleighLanguage load(Program reference, File dir) throws Exception {
        SleighLanguageDescription old = (SleighLanguageDescription) reference.getLanguage().getLanguageDescription();
        SleighLanguageDescription desc = new SleighLanguageDescription(old.getLanguageID(), old.getDescription(),
            old.getProcessor(), old.getEndian(), old.getInstructionEndian(), old.getSize(), old.getVariant(),
            old.getVersion(), old.getMinorVersion(), false, Map.of(), old.getCompatibleCompilerSpecDescriptions(), Map.of());
        desc.setDefsFile(new ResourceFile(new File(dir, "emotionengine.ldefs")));
        desc.setSpecFile(new ResourceFile(new File(dir, "r5900.pspec")));
        desc.setSlaFile(new ResourceFile(new File(dir, "r5900.sla")));
        Constructor<SleighLanguage> ctor = SleighLanguage.class.getDeclaredConstructor(SleighLanguageDescription.class);
        ctor.setAccessible(true);
        return ctor.newInstance(desc);
    }
}
