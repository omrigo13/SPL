package bgu.spl.net.api;
import java.nio.charset.StandardCharsets;
import java.util.*;
import java.nio.*;
public class StompMessageEncoderDecoder implements MessageEncoderDecoder<String> {

    private byte[] bytes=new byte[1<<10];
    private int len=0;
    /**
     * add the next byte to the decoding process
     *
     * @param nextByte the next byte to consider for the currently decoded
     *                 message
     * @return a message if this byte completes one or null if it doesnt.
     */


    @Override
    public String decodeNextByte(byte nextByte) {
        if(nextByte== '\u0000')
            return popString();
        pushBite(nextByte);

        return null;
    }
    private String popString()
    {
        String result=new String(bytes,0,len, StandardCharsets.UTF_8); // convert message to string of utf-8
        len=0;
        return result;
    }
    private void pushBite(byte nextByte)
    {
        if(len>=bytes.length) // there is no space for messege- we will double the length
            bytes=Arrays.copyOf(bytes,len*2);

        bytes[len++]=nextByte;
    }
    /**
     * encodes the given message to bytes array
     *
     * @param message the message to encode
     * @return the encoded bytes
     */
    @Override
    public byte[] encode(String message) {
        return (message+'\u0000').getBytes();
    }
}
