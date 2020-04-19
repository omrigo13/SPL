package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessageEncoderDecoder;
import bgu.spl.net.api.StompMesssagingProtocolImpl;
import bgu.spl.net.impl.rci.ObjectEncoderDecoder;
import bgu.spl.net.impl.rci.RemoteCommandInvocationProtocol;
import bgu.spl.net.srv.Server;

public class StompServer {

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("you must supply two arguments: host, type of server- reactor or tpc");
            System.exit(1);
        }
        int port=Integer.parseInt(args[0]);
        String serverType=args[1];



        if(serverType.equals("reactor"))
        {
                Server.reactor(
                Runtime.getRuntime().availableProcessors(),
                port, //port
                StompMesssagingProtocolImpl::new, //protocol factory
                StompMessageEncoderDecoder::new//message encoder decoder factory
        ).serve();
        }
        else if(serverType.equals("tpc"))
        {
            Server.threadPerClient(
                port, //port
                    StompMesssagingProtocolImpl::new, //protocol factory
                    StompMessageEncoderDecoder::new//message encoder decoder factory
        ).serve();
        }


}
}
