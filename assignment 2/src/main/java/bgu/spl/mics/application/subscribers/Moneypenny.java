package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Squad;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * Only this type of Subscriber can access the squad.
 * Three are several Moneypenny-instances - each of them holds a unique serial number that will later be printed on the report.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class Moneypenny extends Subscriber {
	private int serialNumber;
	Squad squad;
	private List<String> agentSerialNumbers;


	public Moneypenny(int serNumber , String name) {
		super(name);
		// TODO Implement this
		this.serialNumber=serNumber;
		squad=Squad.getInstance();
		agentSerialNumbers=new ArrayList<>();


	}

	@Override
	protected void initialize() {
		// TODO Implement this
		subscribeBroadcast(TerminateBroadcast.class, t->{
			synchronized (this)
			{
				squad.releaseAgents(this.agentSerialNumbers);
				notifyAll();
			}
			terminate();
		});

		if(serialNumber%2==0) // only even moneypeny will receives AgentsAvailableEvent- to prevent deadlock
		{
			subscribeEvent(AgentsAvailableEvent.class,agentAvailableEvent->{
				synchronized (this) {
					List<String> agentsSerial = agentAvailableEvent.getAgentsSerial();
					boolean isAvailble = squad.getAgents(agentsSerial);
					List<String> agentsName = squad.getAgentsNames(agentsSerial);
					this.agentSerialNumbers = agentsSerial;
					Results result=new Results();
					result.setAgentsName(agentsName);
					result.setMoneyPennySer(this.serialNumber);
					result.setResult(isAvailble);
					complete(agentAvailableEvent, result);

					notifyAll();
				}
			});
		}
		else // every other moneypeny will subscribe to these events
		{
			subscribeEvent(ReleaseAgents.class, releaseAgents->{
				List<String> agentsSerial=releaseAgents.getAgentsSerial();
				squad.releaseAgents(agentsSerial);
				complete(releaseAgents,true);
			});

			subscribeEvent(SendAgentsEvent.class,sendAgents->{
				squad.sendAgents(sendAgents.getAgentsSerial(),sendAgents.getTime());
				complete(sendAgents,true);
			});
		}
	}

}
