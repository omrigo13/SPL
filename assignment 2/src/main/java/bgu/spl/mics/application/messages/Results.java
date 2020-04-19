package bgu.spl.mics.application.messages;

import java.util.ArrayList;
import java.util.List;

public class Results {
    // class result to pass information from subscriber to anther

    private List<String> agentsName;
    private int moneyPennySer;
    private int qTime;
    private boolean result;


    public Results()
    {
        agentsName=new ArrayList<>();
        moneyPennySer=0;
        qTime=0;
        result=false;
    }

    public void setAgentsName(List<String> agentsName) {
        this.agentsName = agentsName;
    }

    public void setMoneyPennySer(int moneyPennySer) {
        this.moneyPennySer = moneyPennySer;
    }

    public void setqTime(int qTime) {
        this.qTime = qTime;
    }

    public List<String> getAgentsName() {
        return agentsName;
    }

    public boolean isResult() {
        return result;
    }

    public void setResult(boolean result) {
        this.result = result;
    }

    public int getMoneyPennySer() {
        return moneyPennySer;
    }

    public int getqTime() {
        return qTime;
    }




}
