package bgu.spl.mics.application.messages;

import bgu.spl.mics.Event;

public class GadgetAvailableEvent implements Event {

    private String gadget;



    public GadgetAvailableEvent(String gadgName)
    {
        gadget=gadgName;
    }

    public String getGadget()
    {
        return this.gadget;
    }


}
