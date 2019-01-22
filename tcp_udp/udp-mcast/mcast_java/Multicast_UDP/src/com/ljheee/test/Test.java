package com.ljheee.test;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;
import java.net.UnknownHostException;

public class Test {
	
	public static void main(String[] args){
		String host = "225.0.0.1";//�ಥ��ַ
		int port = 9998;
		String message = "test-multicastSocket";
		try {
			InetAddress group = InetAddress.getByName(host);
			MulticastSocket s = new MulticastSocket(port);
			//����ಥ��
			s.joinGroup(group);
			DatagramPacket dp = new DatagramPacket(message.getBytes(),message.length(),group,port);
			s.send(dp);
	//		s.close();
			byte[] buf = new byte[1024];
			DatagramPacket dpc = new DatagramPacket(buf, buf.length);
			s.receive(dpc);
			System.out.println("�յ��ಥ��Ϣ��"+buf.toString());
			
			
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}