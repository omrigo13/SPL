package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;

import java.util.List;

public class SendAgentsEvent implements Event {
    private List<String> agentsSerial;
    private int time;

    public SendAgentsEvent(List<String > serialAgents, int time)
    {
        this.agentsSerial=serialAgents;
        this.time=time;

    }
    public List<String> getAgentsSerial()
    {
        return this.agentsSerial;
    }
    public int getTime(){return this.time;}
}
