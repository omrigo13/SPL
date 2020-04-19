package bgu.spl.mics.application.passiveObjects;

import com.google.gson.Gson;

import com.google.gson.GsonBuilder;
import com.google.gson.JsonArray;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import java.io.*;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;


/**
 * Passive object representing the diary where all reports are stored.
 * <p>
 * This class must be implemented safely as a thread-safe singleton.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You can add ONLY private fields and methods to this class as you see fit.
 */
public class Diary {

	private static Diary instance=null;
	private List<Report> reports=new ArrayList<>();
	private AtomicInteger total = new AtomicInteger(0);
	/**
	 * Retrieves the single instance of this class.
	 */
	public static Diary getInstance() {
		//TODO: Implement this
		if(instance==null)
			instance=new Diary();

		return instance;
	}

	public List<Report> getReports() {
		return reports;
	}

	/**
	 * adds a report to the diary
	 * @param reportToAdd - the report to add
	 */
	public  void addReport(Report reportToAdd){
		//TODO: Implement this
		this.reports.add(reportToAdd);

	}

	/**
	 *
	 * <p>
	 * Prints to a file name @filename a serialized object List<Report> which is a
	 * List of all the reports in the diary.
	 * This method is called by the main method in order to generate the output.
	 */
	public void printToFile(String filename){
		//TODO: Implement this
		JSONObject jsonObject;
		JSONObject rep1=new JSONObject();
		JsonArray serial;
		JsonArray names;
		JSONArray reportsToJson = new JSONArray();
		for( Report rep:this.reports)
		{
			jsonObject=new JSONObject();
			jsonObject.put("qTime",rep.getQTime());
			jsonObject.put("timeIssued",rep.getTimeIssued());
			jsonObject.put("missionName",rep.getMissionName());
			jsonObject.put("m",rep.getM());
			jsonObject.put("moneypenny",rep.getMoneypenny());

			serial=new JsonArray();
			for(String ser:rep.getAgentsSerialNumbersNumber())
			{
				serial.add(ser);
			}
			jsonObject.put("agentsSerialNumbers",serial);
			names=new JsonArray();
			for(String name:rep.getAgentsNames())
			{
				names.add(name);
			}
			jsonObject.put("agentsNames",names);
			jsonObject.put("gadgetName",rep.getGadgetName());
			jsonObject.put("timeCreated",rep.getTimeCreated());




			reportsToJson.add(jsonObject);


		}

		rep1.put("reports",reportsToJson);

		rep1.put("total",this.total);



		try {
			PrintWriter pw = new PrintWriter(filename);
			Gson gson=new GsonBuilder().setPrettyPrinting().create();
			String out=gson.toJson(rep1);

			pw.append(out);

			pw.flush();
			pw.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * Gets the total number of received missions (executed / aborted) be all the M-instances.
	 * @return the total number of received missions (executed / aborted) be all the M-instances.
	 */
	public int getTotal(){
		//TODO: Implement this
		return this.total.intValue();
	}

	/**
	 * Increments the total number of received missions by 1
	 */
	public  void incrementTotal(){
		this.total.incrementAndGet();

	}
}