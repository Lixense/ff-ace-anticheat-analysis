// Ghidra: find xrefs to rodata blob and dump referencing function decomp
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import java.io.*;

public class FindBlobXrefs extends GhidraScript {
    @Override
    public void run() throws Exception {
        PrintWriter pw = new PrintWriter(new FileWriter(new File("blob_xrefs.txt")));
        // addresses of interest in .rodata: we found base64-hex blobs ~0x1c3b9..0x1d800
        Address start = toAddr(0x1c380);
        Address end = toAddr(0x1d900);
        ReferenceManager refs = currentProgram.getReferenceManager();
        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);
        // iterate references to addresses in the range
        AddressIterator it = refs.getReferenceSourceIterator(start, end);
        // simpler: iterate all refs and check 'toAddress' in range
        Address a = currentProgram.getMinAddress();
        int n = 0;
        ReferenceIterator riter = refs.getReferenceIterator(start);
        while (riter.hasNext() && !monitor.isCancelled()) {
            Reference r = riter.next();
            if (r.getToAddress().compareTo(start) >= 0 && r.getToAddress().compareTo(end) <= 0) {
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                if (f != null) {
                    pw.println("REF from " + r.getFromAddress() + " (in " + f.getName() + ") to " + r.getToAddress());
                    n++;
                }
            }
        }
        pw.println("total refs: " + n);
        pw.close();
        println("done " + n);
    }
}
