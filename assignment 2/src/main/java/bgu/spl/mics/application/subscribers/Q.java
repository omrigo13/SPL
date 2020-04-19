package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.GadgetAvailableEvent;
import bgu.spl.mics.application.messages.Results;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.Inventory;

import java.util.concurrent.CountDownLatch;

/**
 * Q is the only Subscriber\Publisher that has access to the {@link bgu.spl.mics.application.passiveObjects.Inventory}.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Q extends Subscriber {

	private Inventory inventory;
	private int currnetTick;
	public Q() {
		super("Q");
		// TODO Implement this
		inventory=Inventory.getInstance();
		currnetTick=0;

	}

	@Override
	protected void initialize() {
		// TODO Implement this
		subscribeBroadcast(TerminateBroadcast.class, t->{
			terminate();
		});

		subscribeBroadcast(TickBroadcast.class, tick->
		{
			currnetTick=tick.getTick();
		});

		subscribeEvent(GadgetAvailableEvent.class, gadgetAvailableEvent->
		{
			String gadget=gadgetAvailableEvent.getGadget();
			boolean gadgetIsAvailable=inventory.getItem(gadget);
			Results result=new Results();
			result.setqTime(this.currnetTick);
			result.setResult(gadgetIsAvailable);
			complete(gadgetAvailableEvent,result);
		});
	}

}
