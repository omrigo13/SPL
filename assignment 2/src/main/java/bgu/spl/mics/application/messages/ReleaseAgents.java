package bgu.spl.mics.application.messages;


import bgu.spl.mics.Event;

import java.util.ArrayList;
import java.util.List;

public class ReleaseAgents implements Event {

    private List<String> agentsSerial;

    public ReleaseAgents(List<String > serialAgents)
    {
        this.agentsSerial=serialAgents;

    }
    public List<String> getAgentsSerial()
    {
        return this.agentsSerial;
    }

}
