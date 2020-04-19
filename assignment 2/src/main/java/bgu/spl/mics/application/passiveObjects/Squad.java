package bgu.spl.mics.application.passiveObjects;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Passive data-object representing a information about an agent in MI6.
 * You must not alter any of the given public methods of this class. 
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class Squad {

	private static Squad instance=null;
	private ConcurrentHashMap<String, Agent> agents;

	/**
	 * Retrieves the single instance of this class.
	 */
	public static Squad getInstance() {
		//TODO: Implement this
		if(instance==null)
			instance=new Squad();
		return instance;
	}

	/**
	 * Initializes the squad. This method adds all the agents to the squad.
	 * <p>
	 * @param agents 	Data structure containing all data necessary for initialization
	 * 						of the squad.
	 */
	public void load (Agent[] agents) {
		// TODO Implement this
		this.agents=new ConcurrentHashMap<>();
		for(int i=0;i<agents.length;i++)
		{
			this.agents.put(agents[i].getSerialNumber(),agents[i]);
		}

	}

	/**
	 * Releases agents.
	 */
	public    void releaseAgents(List<String> serials) {
		if(!serials.isEmpty()){
			synchronized (this) {
				// TODO Implement this
				for (String ser : serials) {
					if(agents.containsKey(ser)){
						Agent agent = this.agents.get(ser);
						agent.release();
					}
				}
			notifyAll();
			}
		}

	}

	/**
	 * simulates executing a mission by calling sleep.
	 * @param time   time ticks to sleep
	 */
	public  void sendAgents(List<String> serials, int time) {
		// TODO Implement this
			try {
				Thread.sleep(time*100);
			} catch (Exception e) {
				e.printStackTrace();
			}
			releaseAgents(serials);
		}

	/**
	 * acquires an agent, i.e. holds the agent until the caller is done with it
	 * @param serials   the serial numbers of the agents
	 * @return ‘false’ if an agent of serialNumber ‘serial’ is missing, and ‘true’ otherwise
	 */
	public  boolean getAgents(List<String> serials) {
		// TODO Implement this
			for (String ser : serials) {
				Agent agent = this.agents.get(ser);
				if (agent == null)
					return false;
				synchronized (this) { // to prevent someone else to reach agents
					try {
						while (!agent.isAvailable()) {

							wait();
						}
						} catch(Exception e){
							e.printStackTrace();
						}
					}
				}
			synchronized (serials) {
				for (String str : serials) {
					this.agents.get(str).acquire();
				}
			}
			return true;
		}

    /**
     * gets the agents names
     * @param serials the serial numbers of the agents
     * @return a list of the names of the agents with the specified serials.
     */
    public List<String> getAgentsNames(List<String> serials) {
		// TODO Implement this

			List<String> names = new ArrayList<>();
			for (String ser : serials) {
				Agent agent = this.agents.get(ser);
				if (agent == null)
					return null;
				names.add(agent.getName());
			}
			return names;
		}

}
