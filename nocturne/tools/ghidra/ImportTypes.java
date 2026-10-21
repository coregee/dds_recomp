// Import the record types from nocturne_types.h into the program, type the
// data tables, and apply function prototypes from nocturne_signatures.tsv.
// Run through import-types.ps1. Safe to re-run: types are replaced.
// @category Nocturne
import ghidra.app.cmd.function.ApplyFunctionSignatureCmd;
import ghidra.app.script.GhidraScript;
import ghidra.app.util.cparser.C.CParser;
import ghidra.app.util.parser.FunctionSignatureParser;
import ghidra.program.model.address.Address;
import ghidra.program.model.data.*;
import ghidra.program.model.listing.Function;
import ghidra.program.model.symbol.SourceType;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class ImportTypes extends GhidraScript {
    private static final CategoryPath CATEGORY = new CategoryPath("/nocturne");

    // Fixed tables: address, element type, count, label (original HD names).
    private static final Object[][] TABLES = {
        {0x003497c0L, "datDevilFormat", 384, "datDevilFormat_tbl"},
        {0x003d7998L, "datNormalSkill", 288, "datNormalSkill_tbl"},
        {0x003dc1e0L, "datSpecialSkill", 88, "datSpecialSkill_tbl"},
        {0x003aefe0L, "datEncount", 1270, "datEncount_tbl"},
        {0x003bade0L, "datEncountPack", 256, "datEncountPack_tbl"},
        {0x003a7fe0L, "datAisyoRow", 448, "datAisyo_tbl"},
        {0x003d6998L, "datSkill", 512, "datSkill_tbl"},
        {0x00333cf8L, "fclSkill", 384, "fclSkill_tbl"},
        {0x003dc4a0L, "datItem", 160, "datItem_tbl"},
        {0x00339e00L, "fclHearts", 26, "fclHearts_tbl"},
        {0x00339640L, "cmbEvoFlag", 6, "cmbEvoFlagTbl"},
        {0x00339658L, "fclKeisyoSkillLevel", 227, "fclKeisyoSkillLevelTbl"},
        {0x003399e8L, "fclKeisyoScore", 1, "fclKeisyoScoreTbl"},
        {0x00339ba8L, "u16", 37, "cmbDarkDevilTbl"},
        {0x00339c20L, "cmbPowerUpSkill", 55, "cmbPowerUpSkillTbl"},
        {0x0032d270L, "u8", 1024, "fclCombineTbl"},
        {0x0032d670L, "u8", 1024, "fclCombineCurseTbl"},
        {0x0032da70L, "fclRankTbl", 4, "fclRankUpDownTbl"},
        {0x0032db78L, "fclCombCom", 3, "fclExtPatternTbl"},
        {0x0032db90L, "fclCombCom", 6, "fclBirthSpiritTbl"},
        {0x0032dbb8L, "fclCombSpirit", 4, "fclSpiritParamUpTbl"},
        {0x0032dbd8L, "fclIkenieExtPattern", 1, "fclIkenieExtPatternTbl"},
        {0x0032dbe0L, "fclIkenieExtPatternDev", 7, "fclIkenieExtPatternDevTbl"},
        {0x0032dc18L, "fclIkenieExtPatternDev2", 19, "fclIkenieExtPatternDev2Tbl"},
        {0x0032dc90L, "fclIkenieExtPatternDevRace", 2, "fclIkenieExtPatternDevRaceTbl"},
        {0x0032dca0L, "u16", 14, "fclAccidentFailTbl"},
        {0x0032dcc0L, "fclEventDevil", 34, "fclEventDevilTbl"},
        {0x0032ddd0L, "fclMoonRange", 5, "fclCombineManinKagTbl"},
        {0x0032dde0L, "u8", 4, "fclCombineManinRaceTbl"},
        {0x0032dde8L, "u16", 20, "fclCombineManinTbl"},
        {0x0054ff18L, "s32", 1, "datDevilNums"},
        {0x0053d6e8L, "s8", 25, "fclItemHeartsTbl"},
        {0x003322c0L, "s8", 5, "fclEncycCompareParamTbl"},
        {0x003989e0L, "datDevilAI", 384, "datDevilAI_tbl"},
        {0x004f0788L, "u32", 29, "nbAiFuncTbl"},
    };

    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        Path header = Path.of(args[0]);
        Path signatures = Path.of(args[1]);
        DataTypeManager dtm = currentProgram.getDataTypeManager();

        // Ghidra's C parser has no preprocessor: expand PTR32 and drop directives.
        String text = Files.readString(header, StandardCharsets.UTF_8)
            .replaceAll("PTR32\\((\\w+)\\)", "$1 *")
            .replaceAll("(?m)^\\s*#.*$", "");
        CParser parser = new CParser(dtm, true, null);
        parser.parse(text);

        int moved = 0;
        for (DataType dt : parser.getComposites().values()) moved += move(dtm, dt);
        for (DataType dt : parser.getTypes().values()) moved += move(dtm, dt);
        for (DataType dt : parser.getEnums().values()) moved += move(dtm, dt);
        println("types in " + CATEGORY + ": " + moved);

        for (Object[] t : TABLES) {
            Address address = toAddr((Long) t[0]);
            DataType element = dtm.getDataType(CATEGORY, (String) t[1]);
            if (element == null) throw new IllegalStateException("missing type " + t[1]);
            ArrayDataType array = new ArrayDataType(element, (Integer) t[2], element.getLength());
            clearListing(address, address.add(array.getLength() - 1));
            createData(address, array);
            createLabel(address, (String) t[3], true, SourceType.USER_DEFINED);
            println("typed " + t[3] + " at " + address);
        }

        FunctionSignatureParser sigParser = new FunctionSignatureParser(dtm, null);
        List<String> lines = Files.readAllLines(signatures, StandardCharsets.UTF_8);
        int applied = 0;
        for (String line : lines.subList(1, lines.size())) {
            if (line.isBlank()) continue;
            String[] parts = line.split("\t", 2);
            Address entry = toAddr(Long.parseLong(parts[0], 16));
            Function f = getFunctionAt(entry);
            // Callbacks reached only through pointers (qsort comparators) may
            // not have been discovered; define them where code is disassembled.
            if (f == null && getInstructionAt(entry) != null) f = createFunction(entry, null);
            if (f == null) { printerr("no function at " + parts[0]); continue; }
            // Older signatures pinned arguments to custom register storage (the
            // legacy C ABI); return to the standard EE convention first.
            f.setCustomVariableStorage(false);
            f.setCallingConvention("default");
            FunctionDefinitionDataType sig = sigParser.parse(f.getSignature(), parts[1]);
            ApplyFunctionSignatureCmd cmd = new ApplyFunctionSignatureCmd(f.getEntryPoint(), sig, SourceType.USER_DEFINED);
            if (!cmd.applyTo(currentProgram, monitor)) {
                printerr("failed at " + parts[0] + ": " + cmd.getStatusMsg());
                continue;
            }
            applied++;
        }
        println("signatures applied: " + applied + "/" + (lines.size() - 1));
    }

    private int move(DataTypeManager dtm, DataType dt) throws Exception {
        DataType resolved = dtm.getDataType(dt.getDataTypePath());
        if (resolved == null) resolved = dtm.getDataType(new CategoryPath("/"), dt.getName());
        if (resolved == null) return 0;
        if (!resolved.getCategoryPath().equals(CATEGORY)) {
            DataType existing = dtm.getDataType(CATEGORY, resolved.getName());
            if (existing != null) dtm.remove(existing, monitor);
            resolved.setCategoryPath(CATEGORY);
        }
        return 1;
    }
}
