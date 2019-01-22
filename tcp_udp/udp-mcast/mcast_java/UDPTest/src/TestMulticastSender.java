package src;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

/*** Created by jc259968 on 14/09/17.
 */
public class TestMulticastSender {
    public static void main(String[] args) throws Exception{

        String message = "Hello world, again!";

        InetAddress address = InetAddress.getByName("228.5.6.7");
        MulticastSocket socket = new MulticastSocket(49152);

        socket.joinGroup(address);

        DatagramPacket packet = new DatagramPacket(message.getBytes(), message.length(), address, 49152);

        socket.send(packet);
        socket.leaveGroup(address);
        socket.close();

    }
}
