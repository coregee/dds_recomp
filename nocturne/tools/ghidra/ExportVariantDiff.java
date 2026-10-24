// Lists each function of the base program (US Maniax, "candidate") whose
// bytes differ in a version laid out at the same addresses (Hardtype), with
// the instructions that differ side by side.
// A version's new code (in space that is empty in the base) is listed whole
// from the ranges given after the output file, e.g. 0x2fdc20-0x2ff384.
// Headless: -process candidate -readOnly -postScript ExportVariantDiff.java <program path> <output file> [ranges]
// @category Nocturne

import ghidra.app.cmd.disassemble.DisassembleCommand;
import ghidra.app.script.GhidraScript;
import ghidra.framework.model.DomainFile;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.Listing;
import ghidra.program.model.listing.Program;
import ghidra.program.model.mem.Memory;

import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.Arrays;

public class ExportVariantDiff extends GhidraScript {
    @Override
    public void run() throws Exception {
        String[] args = getScriptArgs();
        DomainFile file = state.getProject().getProjectData().getFile(args[0]);
        Program other = (Program) file.getDomainObject(this, false, false, monitor);
        int changed = 0;
        try (PrintWriter out = new PrintWriter(new FileWriter(args[1]))) {
            int transaction = other.startTransaction("disassemble the changed functions");
            try {
                Memory base = currentProgram.getMemory(), version = other.getMemory();
                for (Function f : currentProgram.getFunctionManager().getFunctions(true)) {
                    AddressSetView body = f.getBody();
                    AddressSet set = new AddressSet();
                    boolean differs = false;
                    for (AddressRange r : body) {
                        byte[] a = new byte[(int) r.getLength()], b = new byte[(int) r.getLength()];
                        Address start = other.getAddressFactory().getAddress(r.getMinAddress().toString());
                        try {
                            base.getBytes(r.getMinAddress(), a);
                            version.getBytes(start, b);
                        } catch (Exception e) {
                            continue;
                        }
                        differs |= !Arrays.equals(a, b);
                        set.add(start, other.getAddressFactory().getAddress(r.getMaxAddress().toString()));
                    }
                    if (!differs)
                        continue;
                    ++changed;
                    new DisassembleCommand(set, set, false).applyTo(other, monitor);
                    out.println("== " + f.getEntryPoint() + " " + f.getName() + " (" + body.getNumAddresses() + " bytes)");
                    Listing a = currentProgram.getListing(), b = other.getListing();
                    for (Address at : body.getAddresses(true)) {
                        if ((at.getOffset() & 3) != 0)
                            continue;
                        Instruction ia = a.getInstructionAt(at);
                        Instruction ib = b.getInstructionAt(other.getAddressFactory().getAddress(at.toString()));
                        String sa = ia == null ? "(data)" : ia.toString(), sb = ib == null ? "(data)" : ib.toString();
                        if (!sa.equals(sb))
                            out.println("  " + at + ":  " + sa + "   =>   " + sb);
                    }
                }
                for (int k = 2; k < args.length; ++k) {
                    String[] range = args[k].split("-");
                    Address start = other.getAddressFactory().getAddress(range[0]);
                    Address end = other.getAddressFactory().getAddress(range[1]).subtract(1);
                    out.println("== new code " + start + ".." + end);
                    for (Address at = start; at.compareTo(end) <= 0; at = at.add(4)) {
                        if (other.getListing().getInstructionAt(at) == null)
                            new DisassembleCommand(at, null, false).applyTo(other, monitor);
                        Instruction i = other.getListing().getInstructionAt(at);
                        out.println("  " + at + ":  " + (i == null ? String.format("(word %08x)", other.getMemory().getInt(at)) : i.toString()));
                    }
                }
            } finally {
                other.endTransaction(transaction, false);
            }
        } finally {
            other.release(this);
        }
        println("changed functions: " + changed);
    }
}
