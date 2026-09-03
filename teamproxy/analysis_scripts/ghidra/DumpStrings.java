// Ghidra: dump all defined strings
// @category Analysis
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.address.AddressSetView;
import ghidra.program.model.mem.*;
import ghidra.program.model.listing.*;
import java.io.*;

public class DumpStrings extends GhidraScript {
    @Override
    public void run() throws Exception {
        String outPath = System.getenv("GHIDRA_STRINGS_PATH");
        if (outPath == null) outPath = "strings.txt";
        PrintWriter pw = new PrintWriter(new FileWriter(new File(outPath)));
        DataIterator diter = currentProgram.getListing().getDefinedData(true);
        while (diter.hasNext() && !monitor.isCancelled()) {
            Data d = diter.next();
            if (d.getDataType() != null && d.getDataType().getName().toLowerCase().contains("string")) {
                Object v = d.getValue();
                if (v != null) {
                    pw.println(d.getAddress() + "\t" + v.toString().replace("\n", "\\n"));
                }
            }
        }
        pw.close();
        println("strings dumped");
    }
}
