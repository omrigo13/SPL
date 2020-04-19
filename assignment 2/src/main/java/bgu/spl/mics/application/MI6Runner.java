package bgu.spl.mics.application;

import bgu.spl.mics.application.passiveObjects.*;
import bgu.spl.mics.application.publishers.TimeService;
import bgu.spl.mics.application.subscribers.Intelligence;
import bgu.spl.mics.application.subscribers.M;
import bgu.spl.mics.application.subscribers.Moneypenny;
import bgu.spl.mics.application.subscribers.Q;
import com.google.gson.*;


import java.io.*;
import java.util.ArrayList;

import java.util.List;


/** This is the Main class of the application. You should parse the input file,
 * create the different instances of the objects, and run the system.
 * In the end, you should output serialized objects.
 */
public class MI6Runner {
    public static void main(String[] args) {
        // TODO Implement this

        JsonParser parser = new JsonParser();
        try{
            ////////////////TODO create inventory/////////////
            Object obj = parser.parse(new FileReader(args[0]));
            JsonObject jsonObj = (JsonObject) obj;
            JsonArray initialInventoryArray = (JsonArray) jsonObj.get("inventory");
            int size=initialInventoryArray.size();
            String[] gadgetsArray=new String[size];
            for(int j=0;j<gadgetsArray.length;j++)
            {
                gadgetsArray[j]=initialInventoryArray.get(j).getAsString();
            }

            Inventory inventory=Inventory.getInstance();
            inventory.load(gadgetsArray);

            ////////////////TODO create squad/////////////

            JsonArray initialSquadArray = (JsonArray) jsonObj.get("squad");
            int sizeSquad=initialSquadArray.size();
            Agent[] agentsArray=new Agent[sizeSquad];
            int i=0;
            for (JsonElement sq: initialSquadArray) {
                JsonObject sqInfo = sq.getAsJsonObject();
                agentsArray[i]=new Agent();
                agentsArray[i].setName(sqInfo.get("name").getAsString());
                agentsArray[i].setSerialNumber(sqInfo.get("serialNumber").getAsString());
                i++;
            }

            Squad squad=Squad.getInstance();
            squad.load(agentsArray);

            ////////////////TODO create intelligence/////////////

            JsonObject initialServicesArray = (JsonObject) jsonObj.get("services");
            JsonArray inteli = (JsonArray) initialServicesArray.get("intelligence");
            JsonPrimitive jsonM = (JsonPrimitive) initialServicesArray.get("M");
            JsonPrimitive jsonMoneypenny = (JsonPrimitive) initialServicesArray.get("Moneypenny");
            JsonPrimitive jsontime = (JsonPrimitive) initialServicesArray.get("time");
            ArrayList<MissionInfo> missionsInfo;
            List<String> agentsSerial;
            MissionInfo m;
            ArrayList<Thread> mList=new ArrayList<>();
            ArrayList<Thread> monneyList=new ArrayList<>();
            ArrayList<Thread> inteliList=new ArrayList<>();
            int inteliCount=1;
            for(JsonElement mis: inteli)
            {
                missionsInfo=new ArrayList<>();
                JsonObject missionInfo = mis.getAsJsonObject();
                JsonArray missions = (JsonArray) missionInfo.get("missions");
                for (JsonElement details: missions) {
                    JsonObject mission = details.getAsJsonObject();
                    agentsSerial=new ArrayList<>();
                    JsonArray agents = (JsonArray) mission.get("serialAgentsNumbers");
                    for (JsonElement a: agents) {
                        agentsSerial.add(a.getAsString());

                    }
                    m=new MissionInfo();
                    m.setSerialAgentsNumbers(agentsSerial);
                    m.setDuration(mission.get("duration").getAsInt());
                    m.setGadget(mission.get("gadget").getAsString());
                    m.setMissionName(mission.get("name").getAsString());
                    m.setTimeExpired(mission.get("timeExpired").getAsInt());
                    m.setTimeIssued(mission.get("timeIssued").getAsInt());
                    missionsInfo.add(m);
                }
                Thread t=new Thread(new Intelligence(missionsInfo,inteliCount));
                inteliList.add(t);
                inteliCount++;
            }




            ///////////////TODO create M and MoneyPenny Threads/////////////
            for(int j=0;j<jsonM.getAsInt();j++)
            {
                Thread t=new Thread(new M(j+1,"m"+(j+1)));
                mList.add(t);
            }
            for (int j=0;j<jsonMoneypenny.getAsInt();j++)
            {
                Thread moneypenny=new Thread(new Moneypenny(j+1,"moneyPenny"+(j+1)));
                monneyList.add(moneypenny);
            }

            //start the threads
            Thread qThread=new Thread(new Q());
            qThread.start();
            for(Thread t: mList)
                t.start();
            for(Thread t: monneyList)
                t.start();
            for(Thread t: inteliList)
                t.start();
            Thread timeService=new Thread(new TimeService(jsontime.getAsInt()));
            timeService.start();

            //join threads
            try{
                qThread.join();
                for(Thread t: mList)
                    t.join();
                for(Thread t: monneyList)
                    t.join();
                for(Thread t: inteliList)
                    t.join();

            }catch (InterruptedException e)
            {
                Thread.currentThread().interrupt();
                e.printStackTrace();
            }


            Inventory.getInstance().printToFile(args[1]); // inventory output
            Diary.getInstance().printToFile(args[2]); // diary reports output



        }
        catch (FileNotFoundException e) {e.printStackTrace();}
        catch (IOException e) {e.printStackTrace();}
        catch (Exception e) {e.printStackTrace();}
        finally {
            System.exit(0);
        }


    }
}

