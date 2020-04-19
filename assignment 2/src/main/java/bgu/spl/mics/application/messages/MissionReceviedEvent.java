package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;
import bgu.spl.mics.application.passiveObjects.MissionInfo;


import java.util.List;

public class MissionReceviedEvent implements Event {
    // missions details
    private List<String> agentsSerialNumbers;
    private String gadgetsName;
    private MissionInfo missionInfo;
    private int durationEvent;
    private int inteligTick;


    public MissionReceviedEvent(MissionInfo mission, int time)
    {
        agentsSerialNumbers=mission.getSerialAgentsNumbers();
        gadgetsName=mission.getGadget();
        missionInfo=mission;
        durationEvent=mission.getDuration();
        inteligTick=time;
    }

    public List<String> getAgentsSerialNumbers()
    {
        return this.agentsSerialNumbers;
    }

    public String getGadgetsName()
    {
        return gadgetsName;
    }

    public int getExpiredTime()
    {
        return missionInfo.getTimeExpired();
    }

    public int getDurationEvent(){return this.durationEvent;}
    public MissionInfo getMissionInfo(){return this.missionInfo;}
    public int getInteligTick(){return this.inteligTick;}
}
