package bgu.spl.mics.application.passiveObjects;

import java.util.List;

/**
 * Passive data-object representing information about a mission.
 * You must not alter any of the given public methods of this class.
 * <p>
 * You may add ONLY private fields and methods to this class.
 */
public class MissionInfo {

	private String missionName;
	private List<String> serialAgentsNumbers;
	private String gadgets;
	private int timeIssued;
	private int timeExpired;
	private int duration;
    /**
     * Sets the name of the mission.
     */
    public void setMissionName(String missionName) {
        // TODO Implement this
		this.missionName=missionName;
    }

	/**
     * Retrieves the name of the mission.
     */
	public String getMissionName() {
		// TODO Implement this
		return this.missionName;
	}

    /**
     * Sets the serial agent number.
     */
    public void setSerialAgentsNumbers(List<String> serialAgentsNumbers) {
        // TODO Implement this
		this.serialAgentsNumbers=serialAgentsNumbers;
    }

	/**
     * Retrieves the serial agent number.
     */
	public List<String> getSerialAgentsNumbers() {
		// TODO Implement this
		return this.serialAgentsNumbers;
	}

    /**
     * Sets the gadget name.
     */
    public void setGadget(String gadget) {
        // TODO Implement this
		this.gadgets=gadget;
    }

	/**
     * Retrieves the gadget name.
     */
	public String getGadget() {
		// TODO Implement this
		return this.gadgets;
	}

    /**
     * Sets the time the mission was issued in time ticks.
     */
    public void setTimeIssued(int timeIssued) {
        // TODO Implement this
		this.timeIssued=timeIssued;
    }

	/**
     * Retrieves the time the mission was issued in time ticks.
     */
	public int getTimeIssued() {
		// TODO Implement this
		return this.timeIssued;
	}

    /**
     * Sets the time that if it that time passed the mission should be aborted.
     */
    public void setTimeExpired(int timeExpired) {
        // TODO Implement this
		this.timeExpired=timeExpired;
    }

	/**
     * Retrieves the time that if it that time passed the mission should be aborted.
     */
	public int getTimeExpired() {
		// TODO Implement this
		return this.timeExpired;
	}

    /**
     * Sets the duration of the mission in time-ticks.
     */
    public void setDuration(int duration) {
        // TODO Implement this
		this.duration=duration;
    }

	/**
	 * Retrieves the duration of the mission in time-ticks.
	 */
	public int getDuration() {
		// TODO Implement this
		return this.duration;
	}
}
