package src;

import java.net.DatagramPacket;
import java.net.InetAddress;
import java.net.MulticastSocket;

/*** Created by jc259968 on 14/09/17.
 */
public class TestUDPMulticast {
    public static void main(String[] args) throws Exception {
        String message = "Hello World";

        InetAddress address = InetAddress.getByName("228.5.6.7");
        MulticastSocket socket = new MulticastSocket(49152);

        socket.joinGroup(address);

        DatagramPacket packet = new DatagramPacket(message.getBytes(), message.length(), address, 49152);

        socket.send(packet);

        byte[] messageBuffer = new byte[1024];
        DatagramPacket recv = new DatagramPacket(messageBuffer, 1024);

        socket.receive(recv);

        String resultStr = new String(messageBuffer);
        System.out.println("recieved: "+ resultStr);

    }
}
