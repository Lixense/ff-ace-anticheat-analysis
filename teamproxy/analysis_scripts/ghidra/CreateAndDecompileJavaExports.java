// Ghidra: create functions at every exported Java_* symbol address, then decompile them all
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import java.io.*;

public class CreateAndDecompileJavaExports extends GhidraScript {
    @Override
    public void run() throws Exception {
        PrintWriter pw = new PrintWriter(new FileWriter(new File(System.getenv("GHIDRA_JAVA_EXPORTS"))));
        SymbolTable st = currentProgram.getSymbolTable();
        FunctionManager fm = currentProgram.getFunctionManager();
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        decomp.toggleCCode(true);

        int n = 0;
        for (Symbol sym : st.getAllSymbols(true)) {
            if (monitor.isCancelled()) break;
            String nm = sym.getName();
            if (!nm.startsWith("Java_")) continue;
            Address a = sym.getAddress();
            Function f = fm.getFunctionAt(a);
            if (f == null) {
                f = fm.createFunction(nm, a, null, null);
            }
            if (f == null) continue;
            monitor.setMessage("decompiling " + nm);
            DecompileResults res = decomp.decompileFunction(f, 120, monitor);
            pw.println("\n/* ===== " + nm + " @ " + a + " ==== */");
            pw.println("/* signature: " + f.getSignature() + " */");
            if (res != null && res.decompileCompleted()) {
                pw.println(res.getDecompiledFunction().getC());
            } else {
                pw.println("// decompile failed");
            }
            pw.flush();
            n++;
        }
        pw.println("\n/* total: " + n + " */");
        pw.close();
        println("done " + n);
    }
}
