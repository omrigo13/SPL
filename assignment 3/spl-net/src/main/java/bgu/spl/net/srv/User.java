package bgu.spl.net.srv;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;

public class User  {

    private String userName;
    private String password;
    private int connectionId;
    private boolean isConnected;
    private ConcurrentHashMap<Integer,String> subIdTopicsMap;

    public User(String userName, String password, int connectionId)
    {
        this.userName=userName;
        this.password=password;
        this.connectionId=connectionId;
        isConnected=true;
        subIdTopicsMap=new ConcurrentHashMap<>();
    }

    public String getUserName() {
        return userName;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public int getConnectionId() {
        return connectionId;
    }

    public void setConnectionId(int connectionId) {
        this.connectionId = connectionId;
    }

    public boolean isConnected() {
        return isConnected;
    }

    public void logIn(){isConnected=true;}
    public void logOut(){isConnected=false;}

    public Map<Integer, String> getSubIdTopicsMap() {
        return subIdTopicsMap;
    }

    public void setTopics(ConcurrentHashMap<Integer, String> topics) {
        this.subIdTopicsMap = topics;
    }

    public void addTopic(int id, String topic)
    {
        subIdTopicsMap.put(id,topic);
    }

    public String deleteTopics(int id)
    {
        return subIdTopicsMap.remove(id);
    }
}
