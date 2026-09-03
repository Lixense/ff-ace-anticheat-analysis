// Ghidra headless script: dump all functions (decompiled C) to a file
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.*;
import ghidra.program.model.address.Address;
import ghidra.program.model.symbol.SymbolTable;
import ghidra.program.model.symbol.Symbol;
import ghidra.program.model.symbol.SymbolType;
import java.io.*;

public class DumpAllFunctions extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outPath = System.getenv("GHIDRA_DUMP_PATH");
        if (outPath == null) outPath = "functions.c";
        File outFile = new File(outPath);
        PrintWriter pw = new PrintWriter(new FileWriter(outFile));

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        decomp.toggleCCode(true);
        decomp.toggleSyntaxTree(true);

        Listing listing = currentProgram.getListing();
        FunctionIterator fiter = listing.getFunctions(true);
        int count = 0;
        while (fiter.hasNext() && !monitor.isCancelled()) {
            Function f = fiter.next();
            monitor.setMessage("Decompiling " + f.getName());
            pw.println("/* ===== " + f.getName() + " @ " + f.getEntryPoint() + " ==== */");
            pw.println("/* signature: " + f.getSignature() + " */");
            DecompileResults res = decomp.decompileFunction(f, 90, monitor);
            if (res != null && res.decompileCompleted()) {
                pw.println(res.getDecompiledFunction().getC());
            } else {
                pw.println("// decompile failed");
            }
            pw.println();
            count++;
        }
        pw.println("/* total functions: " + count + " */");
        pw.close();
        decomp.dispose();
        println("Dumped " + count + " functions to " + outFile.getAbsolutePath());
    }
}
