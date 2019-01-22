package src;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

/*** Created by jc259968 on 14/09/17.
 */
public class TestMulticastReader {
    public static void main(String[] args)throws Exception {

        InetAddress address = InetAddress.getByName("228.5.6.7");
        MulticastSocket socket = new MulticastSocket(49152);

        socket.joinGroup(address);

        byte[] messageBuffer = new byte[1024];
        DatagramPacket recv = new DatagramPacket(messageBuffer, 1024);

        //blocking statement until it receives then it will output it
        socket.receive(recv);

        String resultStr = new String(messageBuffer);
        System.out.println("recieved: "+ resultStr);


    }
}
