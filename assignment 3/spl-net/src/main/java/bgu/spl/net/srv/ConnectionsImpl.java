package bgu.spl.net.srv;
import java.util.*;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentLinkedQueue;
import java.util.concurrent.atomic.AtomicInteger;

public class ConnectionsImpl<T> implements Connections<T> {

    private Map<Integer, ConnectionHandler<T>> conections;
    private Map<String, ConcurrentLinkedQueue<Integer>> topics;


    public ConnectionsImpl() {
        this.conections = new ConcurrentHashMap<>();
        this.topics = new ConcurrentHashMap<>();

    }

    @Override
    public boolean send(int connectionId, T msg) {
        if (conections.containsKey(connectionId)) {
            conections.get(connectionId).send(msg);
            return true;
        }
        return false;
    }

    @Override
    public void send(String channel, T msg) {
        ConcurrentLinkedQueue<Integer> queue=topics.get(channel);
        for (int con : queue) {
            send(con, msg);
        }

    }

    @Override
    public void disconnect(int connectionId) {
//        User us=conectionUser.get(connectionId);
//        for (String topic : topics.keySet()) {
//            topics.get(topic).remove(connectionId);
//        }

        try {
            conections.get(connectionId).close();
            conections.remove(connectionId);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void AddHandler(int connectionId, ConnectionHandler<T> handler)
    {
        conections.putIfAbsent(connectionId,handler);
    }

    public void addSubscription(String channel, int connectionId)
    {
        topics.putIfAbsent(channel,new ConcurrentLinkedQueue<>());
        topics.get(channel).add(connectionId);
    }

}
