// Ghidra: find all functions whose code references the rodata encrypted table (0x1c000-0x1e000)
// and decompile each to a file.
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressRange;
import ghidra.program.model.address.AddressRangeIterator;
import ghidra.program.model.address.AddressSet;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import java.io.*;
import java.util.*;

public class TraceRdataUsers extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outPath = System.getenv("GHIDRA_RDATA_USERS");
        PrintWriter pw = new PrintWriter(new FileWriter(new File(outPath)));
        long lo = 0x1b000;  // include a bit of margin before the table
        long hi = 0x1e800;
        AddressSet roi = new AddressSet(toAddr(lo), toAddr(hi));

        // pass 1: collect functions that have an instruction-level reference into roi
        Set<String> funcNames = new TreeSet<String>();
        Map<String, List<String>> refMap = new TreeMap<String, List<String>>();
        FunctionManager fm = currentProgram.getFunctionManager();
        InstructionIterator iter = currentProgram.getListing().getInstructions(true);
        int cnt = 0;
        while (iter.hasNext() && !monitor.isCancelled()) {
            Instruction insn = iter.next();
            Reference[] refs = insn.getReferencesFrom();
            if (refs == null) continue;
            for (Reference r : refs) {
                Address to = r.getToAddress();
                if (to != null && roi.contains(to)) {
                    Function f = fm.getFunctionContaining(insn.getAddress());
                    String fn = (f == null) ? ("NONE@" + insn.getAddress()) : f.getName();
                    funcNames.add(fn);
                    refMap.computeIfAbsent(fn, k -> new ArrayList<String>())
                           .add(insn.getAddress() + " -> " + to);
                    cnt++;
                }
            }
        }
        pw.println("// functions referencing rodata table: " + funcNames.size() + ", refs=" + cnt);
        for (String fn : funcNames) {
            pw.println("// === " + fn);
            for (String r : refMap.get(fn)) pw.println("//   ref " + r);
        }

        // pass 2: decompile each function fully
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        decomp.toggleCCode(true);
        for (String fn : funcNames) {
            if (monitor.isCancelled()) break;
            Function f = null;
            for (Function g : fm.getFunctions(true)) {
                if (g.getName().equals(fn)) { f = g; break; }
            }
            if (f == null) continue;
            monitor.setMessage("decompiling " + fn);
            DecompileResults res = decomp.decompileFunction(f, 120, monitor);
            pw.println("\n\n/* ============ FUNCTION " + fn + " @ " + f.getEntryPoint() + " ============ */");
            pw.println("/* signature: " + f.getSignature() + " */");
            if (res != null && res.decompileCompleted()) {
                pw.println(res.getDecompiledFunction().getC());
            } else {
                pw.println("// decompile failed");
            }
            pw.flush();
        }
        pw.close();
        println("done: " + funcNames.size() + " funcs, refs=" + cnt);
    }
}
