package bgu.spl.net.api;

import bgu.spl.net.impl.stomp.Stompframe;
import bgu.spl.net.srv.Connections;
import bgu.spl.net.srv.ConnectionsImpl;
import bgu.spl.net.srv.User;
import bgu.spl.net.srv.UserData;

import java.util.HashMap;
import java.util.Map;

public class StompMesssagingProtocolImpl implements StompMessagingProtocol<String> {

    private int connectionId;
    private Connections<String> connections;
    private boolean shouldTerminate=false;
    private UserData userData;
    /**
     * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
     *
     * @param connectionId
     * @param connections
     */
    @Override
    public void start(int connectionId, Connections<String> connections) {
        this.connectionId=connectionId;
        this.connections=connections;
        this.userData=UserData.getInstance();
    }

    @Override
    public void process(String message) {

        if(message=="")
            return;
        Stompframe msg=Stompframe.parse(message);
        System.out.println(msg.getCommend().toString()+" received");
        switch (msg.getCommend())
        {
            case CONNECT:
                connectUser(msg.getHeaders());
                break;
            case SEND:
                sendMessage(msg.getHeaders(),msg.getMsgBody());
                break;
            case SUBSCRIBE:
                subUser(msg.getHeaders(),msg.getMsgBody());
                break;
            case UNSUBSCRIBE:
                unsubUser(msg.getHeaders(),msg.getMsgBody());
                break;
            case DISCONNECT:
                disconectUser(msg.getHeaders(),msg.getMsgBody());
                break;

        }
    }

    /**
     * @return true if the connection should be terminated
     */
    @Override
    public boolean shouldTerminate() {
        return this.shouldTerminate;
    }

    public void connectUser(HashMap<String,String> h) // protocol for connect frame
    {
        System.out.println("connect received");
        // to add accepect version ????
        String name=h.get("login");
        String password=h.get("passcode");
        if(userData.getUser(name)==null)
        {
            User user=new User(name,password,connectionId);
            userData.addUser(user,connectionId);
            Stompframe connected=new Stompframe();
            connected.setCommend("CONNECTED");
            connected.addHeader("version",h.get("accept-version"));

//            connected.addHeader("message","Login successful");
            connections.send(connectionId,connected.toString());
        }
        else
        {
            if(userData.getUser(name).getPassword().compareTo(password)!=0)
            {
                Stompframe error=new Stompframe();
                error.setCommend("ERROR");
                error.addHeader("message","Wrong password");
                System.out.println(error.toString());
                connections.send(connectionId,error.toString());
//                connections.disconnect(connectionId);
                shouldTerminate=true;

            }
            else if(userData.getUser(name).isConnected()==true)
            {
                Stompframe error=new Stompframe();
                error.setCommend("ERROR");
                error.addHeader("message","User already logged in");
                System.out.println(error.toString());
                connections.send(connectionId,error.toString());
//                connections.disconnect(connectionId);
                shouldTerminate=true;

            }
            else
            {
                User u=userData.getUser(name);
                u.logIn();
                u.setConnectionId(connectionId);
                userData.addUser(u,connectionId);
                Stompframe connected=new Stompframe();
                connected.setCommend("CONNECTED");
                connected.addHeader("version",h.get("accept-version"));
//                connected.addHeader("message","Login successful");
                System.out.println(connected.toString());
                connections.send(connectionId,connected.toString());
            }
        }
    }

    public void sendMessage(HashMap<String,String> h, String b) //protocol for send frame
    {
        String dest=h.get("destination");
        Stompframe message=new Stompframe();
        for (int conId : userData.getconId(dest)) {
            message.setCommend("MESSAGE");
            message.addHeader("subscription", Integer.toString(userData.getSubId(dest, conId)));
            message.addHeader("Message-id", Integer.toString(userData.getAndIncrement()));
            message.addHeader("destination", dest);
            message.setMsgBody(b);
            connections.send(conId, message.toString());
        }
    }

    public void subUser(HashMap<String,String> h, String b) // protocol for sub user
    {
        userData.subscribeUser(h.get("destination"),Integer.parseInt(h.get("id")),connectionId);
        if(h.get("receipt")!=null)
        {
            Stompframe receipt=new Stompframe();
            receipt.setCommend("RECEIPT");
            receipt.addHeader("receipt-id",h.get("receipt"));
            receipt.setMsgBody(b);
            connections.send(connectionId,receipt.toString());
        }
    }
    public void unsubUser(HashMap<String,String> h, String b) { // protocol for unsub user
        userData.unsubscribe(Integer.parseInt(h.get("id")), connectionId);
        Stompframe receipt = new Stompframe();
        if (h.get("receipt") != null)
        {
            receipt.setCommend("RECEIPT");
            receipt.addHeader("receipt-id", h.get("receipt"));
            receipt.setMsgBody(b);
            connections.send(connectionId, receipt.toString());
        }

    }
    public void disconectUser(HashMap<String,String> h, String b) // protocol for disconnect frame
    {
        userData.userDiscon(connectionId);
        Stompframe discon=new Stompframe();
        if (h.get("receipt") != null)
        {
            discon.setCommend("RECEIPT");
            discon.addHeader("receipt-id",h.get("receipt"));
            discon.setMsgBody(b);
            connections.send(connectionId,discon.toString());
        }
        shouldTerminate=true;

    }



}
