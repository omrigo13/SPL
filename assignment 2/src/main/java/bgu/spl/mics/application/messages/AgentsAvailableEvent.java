package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;


import java.util.List;

public class AgentsAvailableEvent implements Event {

    private List<String> agentsSerial;


    public AgentsAvailableEvent(List<String > serialAgents)
    {
        this.agentsSerial=serialAgents;
    }

    public List<String> getAgentsSerial()
    {
        return this.agentsSerial;
    }


}
