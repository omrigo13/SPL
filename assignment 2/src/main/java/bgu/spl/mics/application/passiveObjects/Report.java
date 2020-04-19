package bgu.spl.mics.application.passiveObjects;

import java.util.ArrayList;
import java.util.List;

/**
 * Passive data-object representing a delivery vehicle of the store.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class Report {
	String missionName;
	int M;
	int moneyPenny;
	List<String> serialAgentsNumbers=new ArrayList<>();
	List<String> agentsNames=new ArrayList<>();
	String gadgetName;
	int timeCreated;
	int timeIssued;
	int qTime;
	/**
     * Retrieves the mission name.
     */
	public String getMissionName() {
		// TODO Implement this
		return this.missionName;
	}

	/**
	 * Sets the mission name.
	 */
	public void setMissionName(String missionName) {
		// TODO Implement this
		this.missionName=missionName;
	}

	/**
	 * Retrieves the M's id.
	 */
	public int getM() {
		// TODO Implement this
		return this.M;
	}

	/**
	 * Sets the M's id.
	 */
	public void setM(int m) {
		// TODO Implement this
		this.M=m;
	}

	/**
	 * Retrieves the Moneypenny's id.
	 */
	public int getMoneypenny() {
		// TODO Implement this
		return this.moneyPenny;
	}

	/**
	 * Sets the Moneypenny's id.
	 */
	public void setMoneypenny(int moneypenny) {
		// TODO Implement this
		this.moneyPenny=moneypenny;
	}

	/**
	 * Retrieves the serial numbers of the agents.
	 * <p>
	 * @return The serial numbers of the agents.
	 */
	public List<String> getAgentsSerialNumbersNumber() {
		// TODO Implement this
		return serialAgentsNumbers;
	}

	/**
	 * Sets the serial numbers of the agents.
	 */
	public void setAgentsSerialNumbersNumber(List<String> agentsSerialNumbersNumber) {
		// TODO Implement this
		this.serialAgentsNumbers=agentsSerialNumbersNumber;
	}

	/**
	 * Retrieves the agents names.
	 * <p>
	 * @return The agents names.
	 */
	public List<String> getAgentsNames() {
		// TODO Implement this
		return this.agentsNames;
	}

	/**
	 * Sets the agents names.
	 */
	public void setAgentsNames(List<String> agentsNames) {
		// TODO Implement this
		this.agentsNames=agentsNames;
	}

	/**
	 * Retrieves the name of the gadget.
	 * <p>
	 * @return the name of the gadget.
	 */
	public String getGadgetName() {
		// TODO Implement this
		return gadgetName;
	}

	/**
	 * Sets the name of the gadget.
	 */
	public void setGadgetName(String gadgetName) {
		// TODO Implement this
		this.gadgetName=gadgetName;
	}

	/**
	 * Retrieves the time-tick in which Q Received the GadgetAvailableEvent for that mission.
	 */
	public int getQTime() {
		// TODO Implement this
		return this.qTime;
	}

	/**
	 * Sets the time-tick in which Q Received the GadgetAvailableEvent for that mission.
	 */
	public void setQTime(int qTime) {
		// TODO Implement this
		this.qTime=qTime;
	}

	/**
	 * Retrieves the time when the mission was sent by an Intelligence Publisher.
	 */
	public int getTimeIssued() {
		// TODO Implement this
		return this.timeIssued;
	}

	/**
	 * Sets the time when the mission was sent by an Intelligence Publisher.
	 */
	public void setTimeIssued(int timeIssued) {
		// TODO Implement this
		this.timeIssued=timeIssued;
	}

	/**
	 * Retrieves the time-tick when the report has been created.
	 */
	public int getTimeCreated() {
		// TODO Implement this
		return this.timeCreated;
	}

	/**
	 * Sets the time-tick when the report has been created.
	 */
	public void setTimeCreated(int timeCreated) {
		// TODO Implement this
		this.timeCreated=timeCreated;
	}
}
