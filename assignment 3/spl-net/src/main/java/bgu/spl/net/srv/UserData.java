package bgu.spl.net.srv;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

public class UserData {

    private ConcurrentHashMap<String, User> nameUsersMap;
    private ConcurrentHashMap<String, ConcurrentHashMap<User,Integer>> topics;  // user with subId
    private ConcurrentHashMap<Integer, User> userIdMap; // connectionId, user
    private AtomicInteger msgId;
    private static UserData instance=new UserData();

    private UserData()
    {
        nameUsersMap=new ConcurrentHashMap<>();
        topics=new ConcurrentHashMap<>();
        userIdMap=new ConcurrentHashMap<>();
        msgId=new AtomicInteger(1);
    }

    public static UserData getInstance()
    {
        return  instance;
    }

    public User getUser(String name) {
        if (nameUsersMap.containsKey(name))
            return nameUsersMap.get(name);
        return null;
    }

    public void addUser(User user, int connectionId) {
        nameUsersMap.putIfAbsent(user.getUserName(), user);
        userIdMap.putIfAbsent(connectionId,user);
        user.logIn();
    }

    public List<Integer> getconId(String topic)
    {
        List<Integer> usersId=new ArrayList<>();
        if(topics.get(topic)!=null){
            for(User user: topics.get(topic).keySet())
            {
                usersId.add(user.getConnectionId());
            }
        }

        return usersId;
    }

    public int getSubId(String topic, int coId)
    {
        User user=userIdMap.get(coId);
        for(Map.Entry<User,Integer> entry: topics.get(topic).entrySet())
        {
            if(user==entry.getKey())
                return entry.getValue();

        }
        return -1;
    }

    public Integer getAndIncrement() {
        return msgId.getAndIncrement();
    }

    public void subscribeUser(String topic, int subId, int connectionId) {
        topics.putIfAbsent(topic, new ConcurrentHashMap<>());
        topics.get(topic).put(userIdMap.get(connectionId),subId);
        userIdMap.get(connectionId).addTopic(subId,topic);
    }

    public void unsubscribe( int subId, int connectionId)
    {
        User user=userIdMap.get(connectionId);
        String topic=user.getSubIdTopicsMap().get(subId);
        if(topics.get(topic)!=null)
        {
            topics.get(topic).remove(user);
        }
        user.deleteTopics(subId);
    }

    public void userDiscon(int connectionId)
    {
        User user=userIdMap.get(connectionId);

        userIdMap.remove(connectionId); // remove from con id and user
        for(String genre: topics.keySet())
        {
            topics.get(genre).remove(user); // remove from each topic the user
        }
        user.logOut();
    }



}
