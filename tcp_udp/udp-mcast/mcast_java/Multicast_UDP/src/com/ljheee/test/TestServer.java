package com.ljheee.test;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.MulticastSocket;
import java.net.SocketException;

public class TestServer {
	
	public static void main(String[] args){
		//�����鲥�ͷ����鲥�����ݱ�����Ҫ���鲥��ַ��ӽ���
		String host = "225.0.0.1";//�ಥ��ַ
		int port = 9998;
		int length = 1024;
		byte[] buf = new byte[length];
		MulticastSocket ms = null;
		DatagramPacket dp = null;
		StringBuffer sbuf = new StringBuffer();
		try {			
			ms = new MulticastSocket(port);
			dp = new DatagramPacket(buf, length);
			
			//����ಥ��ַ
			InetAddress group = InetAddress.getByName(host);
			ms.joinGroup(group);
			
			System.out.println("�����ಥ�˿ڴ򿪣�");
			ms.receive(dp);
//			ms.close();
			int i;
			for(i=0;i<1024;i++){
				if(buf[i] == 0){
					break;
				}
				sbuf.append((char) buf[i]);
			}			
			System.out.println("�յ��ಥ��Ϣ��" + sbuf.toString());
			DatagramPacket dps = new DatagramPacket("ok".getBytes(), "ok".length(), dp.getAddress(), dp.getPort());
			ms.send(dps);
			ms.close();
			
			
		} catch (IOException e) {
			e.printStackTrace();
		} 
		
	}
}