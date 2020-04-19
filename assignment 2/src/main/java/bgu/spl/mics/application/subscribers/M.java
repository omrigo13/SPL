package bgu.spl.mics.application.subscribers;

import bgu.spl.mics.Future;
import bgu.spl.mics.Subscriber;
import bgu.spl.mics.application.messages.*;
import bgu.spl.mics.application.passiveObjects.Diary;
import bgu.spl.mics.application.passiveObjects.Report;

import java.util.ArrayList;
import java.util.List;


/**
 * M handles ReadyEvent - fills a report and sends agents to mission.
 *
 * You can add private fields and public methods to this class.
 * You MAY change constructor signatures and even add new public constructors.
 */
public class M extends Subscriber {

	private int serialNumber;
	private int currentTick;
	private Diary diary;
	private int moneyPennyser;
	private List<String> agentsNAmes;
	private List<String> agentsSerial;
	private String gadgName;
	private int createrep;
	private int Qtime;
	private int missionDuraton;
	private String missionName;
	private int InteliigTick;


	public M(int ser, String name){
		super(name);
		serialNumber=ser;
		currentTick=0;
		diary=Diary.getInstance();
		agentsNAmes=new ArrayList<>();
		agentsSerial=new ArrayList<>();
		gadgName="";
		createrep=0;
		Qtime=0;
		moneyPennyser=0;
		missionDuraton=0;
		missionName="";
		InteliigTick=0;

	}

	public M()
	{
		//for framework test
		super("M");
		serialNumber=1;
		currentTick=0;
		diary=Diary.getInstance();
		agentsNAmes=new ArrayList<>();
		agentsSerial=new ArrayList<>();
		gadgName="";
		createrep=0;
		Qtime=0;
		moneyPennyser=0;
		missionDuraton=0;
		missionName="";
		InteliigTick=0;

	}

	@Override
	protected void initialize() {
		// TODO Implement this
		subscribeBroadcast(TerminateBroadcast.class, t->{
			terminate();
		});

		subscribeBroadcast(TickBroadcast.class, tick->{
			currentTick=tick.getTick();
		});


		subscribeEvent(MissionReceviedEvent.class, missionEvent->{
			diary.incrementTotal();
			missionDuraton=missionEvent.getDurationEvent();
			agentsSerial=missionEvent.getAgentsSerialNumbers();
			gadgName=missionEvent.getGadgetsName();
			missionName=missionEvent.getMissionInfo().getMissionName();
			InteliigTick=missionEvent.getInteligTick();
			AgentsAvailableEvent agentsAvailableEvent=new AgentsAvailableEvent(agentsSerial);
			Future<Results> futureObj=getSimplePublisher().sendEvent(agentsAvailableEvent);
			if(futureObj!=null)
//			|| futureObj.get()!=null)

			{
				Results agentResult=futureObj.get();
				this.agentsNAmes=agentResult.getAgentsName();
				this.moneyPennyser=agentResult.getMoneyPennySer();
				if (agentResult.isResult() != true || currentTick>missionEvent.getExpiredTime())
				{
					ReleaseAgents relAgents=new ReleaseAgents(this.agentsSerial);
					Future<Boolean> futeueRelease = getSimplePublisher().sendEvent(relAgents);
					if (futeueRelease != null)
					{
						complete(missionEvent, false);

					}
					else complete(relAgents,null);
				}

				else
				{
					GadgetAvailableEvent gadgetAvailableEvent = new GadgetAvailableEvent(gadgName);
					Future<Results> futerGadget = getSimplePublisher().sendEvent(gadgetAvailableEvent);
					Results gadgetResult=futerGadget.get();
					Qtime = gadgetResult.getqTime();
					if (futerGadget.get() != null || futerGadget!=null)
					{
						if (gadgetResult.isResult() != true)
						{
							ReleaseAgents relAgents=new ReleaseAgents(this.agentsSerial);
							Future<Boolean> futeueRelease = getSimplePublisher().sendEvent(relAgents);
							if (futeueRelease != null)
							{
								complete(missionEvent, false);

							}
							else complete(relAgents,null);

						}
						else
						{
							if (missionEvent.getExpiredTime() < Qtime)
							{
								ReleaseAgents relAgents=new ReleaseAgents(this.agentsSerial);
								Future<Boolean> futeueRelease = getSimplePublisher().sendEvent(relAgents);
								if (futeueRelease != null)
								{
									complete(missionEvent, false);

								}
								else complete(relAgents,null);
							}
							else
							{
								Future<Boolean> futureSend = getSimplePublisher().sendEvent(new SendAgentsEvent(this.agentsSerial, this.missionDuraton));
								if(futureSend.get()!=null)
								{
									if (futureSend.get() == true)
									{
										Report rep = new Report();
										rep.setMissionName(this.missionName);
										rep.setM(this.serialNumber);
										rep.setMoneypenny(this.moneyPennyser);
										rep.setAgentsSerialNumbersNumber(this.agentsSerial);
										rep.setAgentsNames(this.agentsNAmes);
										rep.setGadgetName(this.gadgName);
										rep.setTimeIssued(this.InteliigTick);
										rep.setQTime(this.Qtime);
										rep.setTimeCreated(this.currentTick);

										diary.addReport(rep);
										complete(missionEvent, true);
									}
								}

							}
						}
					}

				}

			}

	});

}
}
