// Ghidra: define the rodata blob region as data, then list functions that xref it
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.*;
import ghidra.program.model.symbol.*;
import ghidra.program.model.mem.*;
import ghidra.program.database.data.*;
import ghidra.program.model.data.*;
import java.io.*;

public class DefineAndFindXrefs extends GhidraScript {
    @Override
    public void run() throws Exception {
        PrintWriter pw = new PrintWriter(new FileWriter(new File(System.getenv("GHIDRA_XREF_PATH"))));
        Listing listing = currentProgram.getListing();
        // define the blob range as byte arrays so decompiler picks refs
        Address start = toAddr(0x1c380);
        Address end = toAddr(0x1d900);
        Data d = listing.getDataAt(start);
        if (d == null) {
            // clear existing then create string-ish data
            listing.clearCodeUnits(start, end, true);
        }
        // Mark some known string starts (base64 runs)
        // Instead of full definition, just disassemble every function that has a load from these
        // Use the memory block to search for ADRP immediates is hard; simpler: use existing refs after 'create data'
        createDataAtString(0x1c3b9, 100);
        createDataAtString(0x1cba1, 100);
        createDataAtString(0x1d31b, 100);
        createDataAtString(0x1d6f6, 100);

        ReferenceManager refs = currentProgram.getReferenceManager();
        int n = 0;
        for (long addr = 0x1c380; addr <= 0x1d900 && !monitor.isCancelled(); addr += 1) {
            Address toa = toAddr(addr);
            ReferenceIterator it = refs.getReferencesTo(toa);
            while (it.hasNext()) {
                Reference r = it.next();
                Function f = currentProgram.getFunctionManager().getFunctionContaining(r.getFromAddress());
                if (f != null) {
                    pw.println("REF 0x" + Long.toHexString(addr) + " <- " + r.getFromAddress() + " in " + f.getName());
                    n++;
                }
            }
        }
        pw.println("total: " + n);
        pw.close();
        println("done " + n);
    }
    void createDataAtString(long addr, int len) throws Exception {
        Address a = toAddr(addr);
        Listing listing = currentProgram.getListing();
        Data d = listing.getDataAt(a);
        if (d == null) {
            listing.createData(a, new ByteDataType(), len);
        }
    }
}
