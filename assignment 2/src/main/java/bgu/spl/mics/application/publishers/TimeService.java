package bgu.spl.mics.application.publishers;


import bgu.spl.mics.Publisher;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.messages.TickBroadcast;

import java.util.Timer;
import java.util.*;


/**
 * TimeService is the global system timer There is only one instance of this Publisher.
 * It keeps track of the amount of ticks passed since initialization and notifies
 * all other subscribers about the current time tick using {@link Tick Broadcast}.
 * This class may not hold references for objects which it is not responsible for.
 * 
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class TimeService extends Publisher {

	private int currentTick;
	private int duration;
	private Timer timer;

	public TimeService(int duration) {
		super("TickBroadcast");
		// TODO Implement this
		this.currentTick=0;
		this.duration=duration;
		timer =new Timer();
		try{
			Thread.sleep(500);
			}catch (InterruptedException e)
		{
			Thread.currentThread().interrupt();
			e.printStackTrace();
		}

	}

	@Override
	protected void initialize() {
		// TODO Implement this


		TimerTask k = new TimerTask() {
			@Override
			public void run() {
				currentTick++;
				if (currentTick <= duration) {
					getSimplePublisher().sendBroadcast(new TickBroadcast(currentTick));

				} else {
					timer.cancel();
					timer.purge();

					getSimplePublisher().sendBroadcast(new TerminateBroadcast());

				}
			}
		};


		timer.schedule(k, 0, 100);
	}

	@Override
	public void run() {
		// TODO Implement this
			initialize();

	}

}
