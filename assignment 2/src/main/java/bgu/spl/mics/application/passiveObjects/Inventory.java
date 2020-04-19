package bgu.spl.mics.application.passiveObjects;

import com.google.gson.Gson;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

/**
 *  That's where Q holds his gadget (e.g. an explosive pen was used in GoldenEye, a geiger counter in Dr. No, etc).
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private fields and methods to this class as you see fit.
 */
public class Inventory {
	private static Inventory instance=null;
	private List<String> gadgets;
	/**
     * Retrieves the single instance of this class.
     */
	public static Inventory getInstance() {
		if(instance==null )
			instance=new Inventory();
		//TODO: Implement this
		return instance;
	}

	/**
     * Initializes the inventory. This method adds all the items given to the gadget
     * inventory.
     * <p>
     * @param inventory 	Data structure containing all data necessary for initialization
     * 						of the inventory.
     */
	public void load (String[] inventory) {
		gadgets=new ArrayList<>();
		for(String gadg:inventory)
			gadgets.add(gadg);
	}
	
	/**
     * acquires a gadget and returns 'true' if it exists.
     * <p>
     * @param gadget 		Name of the gadget to check if available
     * @return 	‘false’ if the gadget is missing, and ‘true’ otherwise
     */
	public synchronized boolean getItem(String gadget){

		boolean gadgetExsist=this.gadgets.remove(gadget);
		//TODO: Implement this

		return gadgetExsist;
	}

	/**
	 *
	 * <p>
	 * Prints to a file name @filename a serialized object List<String> which is a
	 * list of all the of the gadgeds.
	 * This method is called by the main method in order to generate the output.
	 */
	public void printToFile(String filename){
		//TODO: Implement this
		Gson gson = new Gson();
		try {
			Writer w = new OutputStreamWriter(new FileOutputStream(filename));
			w.write(gson.toJson(gadgets));
			w.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
