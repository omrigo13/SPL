package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Future;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.MissionReceviedEvent;
import bgu.spl.mics.application.messages.TerminateBroadcast;
import bgu.spl.mics.application.messages.TickBroadcast;
import bgu.spl.mics.application.passiveObjects.MissionInfo;

import java.util.*;

/**
 * A Publisher\Subscriber.
 * Holds a list of Info objects and sends them
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class  Intelligence extends Subscriber {

	private List<MissionInfo> listOfMissions;

	private int currentTick;
	private Integer Iid;


	public Intelligence(List<MissionInfo> missions,int id) {
		super("Intelligence " + id);
		// TODO Implement this
		listOfMissions = missions;
		currentTick = 0;

		this.Iid = id;
	}

	@Override
	protected void initialize() {
		// TODO Implement this
		subscribeBroadcast(TerminateBroadcast.class, t->{
			terminate();
		});

		subscribeBroadcast(TickBroadcast.class, tickBrod->{
			currentTick=tickBrod.getTick();
			synchronized (listOfMissions){
				for(MissionInfo mission:listOfMissions)
				{
					if(mission.getTimeIssued()==currentTick)
					{
						Future<Boolean> futureMission=getSimplePublisher().sendEvent(new MissionReceviedEvent(mission,currentTick));

					}
				}
				listOfMissions.notifyAll();
			}

		});


	}
}