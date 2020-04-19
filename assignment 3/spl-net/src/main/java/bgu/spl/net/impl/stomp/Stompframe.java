package bgu.spl.net.impl.stomp;

import java.util.HashMap;
import java.util.Map;

public class Stompframe {
    public static enum Commend{CONNECT,CONNECTED,MESSAGE,RECEIPT,ERROR,SEND,SUBSCRIBE,UNSUBSCRIBE,DISCONNECT}
    private Commend commend;
    private HashMap<String,String> headers;
    private String msgBody;

    public Stompframe()
    {
        headers=new HashMap<>();
        msgBody="";
    }

    public static Stompframe parse(String msg) // create new StompMsg
    {
        Stompframe f=new Stompframe();
        String[] msgSplit=msg.split("\n");
        f.commend=Commend.valueOf(msgSplit[0]); // set type of message
        for(int i=1;i<msgSplit.length;i++)
        {
            if(msgSplit[i].length()==0) // empty line indicates end of headers
            {
                if(msgSplit.length>i+1) // if there are more lines then there is a body of a msg
                {
                    f.msgBody=msgSplit[i+1];

                }
                break;
            }
            else
            {
                String[] header=msgSplit[i].split(":");
                f.headers.put(header[0],header[1]);
            }
        }
        return f;
    }

    public Commend getCommend() {
        return commend;
    }

    public void setCommend(String commend) {
        this.commend = Commend.valueOf(commend);
    }
    public void addHeader(String headerName,String headeVal)
    {
        this.headers.put(headerName,headeVal);
    }

    public HashMap<String, String> getHeaders() {
        return headers;
    }

    public void setHeaders(HashMap<String, String> headers) {
        this.headers = headers;
    }

    public String getMsgBody() {
        return msgBody;
    }

    public void setMsgBody(String msgBody) {
        this.msgBody = msgBody;
    }

    public String toString()
    {
        String outMsg=commend.toString()+"\n";
        for(Map.Entry<String,String> entry:headers.entrySet())
        {
            outMsg+=entry.getKey()+":"+entry.getValue()+"\n";
        }
        outMsg+="\n"+msgBody;
        return outMsg;
    }


}
