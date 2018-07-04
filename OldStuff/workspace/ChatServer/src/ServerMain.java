//Main Header Comment Block
//Michael Allen-Bond
//CSE 223
//Programming Assignment 5: The Apocalypse.
//Oh Swing, unloving and hateful demon that you are,
//with your wretched, buggy methods and labrynthine manuals,
//would that I could recover the time you have stolen from me, I would,
//but those hours and days are gone now,
//turned from ticking seconds into sad, terrible code. Oh Swing,
//You have cost me so.
//This program runs the Server, it should created a new chat window for
//every new client.  To use it, just run ServerMain.
//You should then be able to ClientMain multiple times, creating a new server chat.

import java.net.ServerSocket;
import java.net.Socket;


public class ServerMain {
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Socket sock=null;																
		
		try{				
			ServerSocket ss=new ServerSocket(1201);									//This is all stuff we've seen in class.
			System.out.println("Server Online: type '!!Exit' to close Server.");	
			(new Thread (new Poll())).start();										//This "Poll" thread checks for !!Exit input
			while (true){		
				sock=ss.accept();			//accepts client request
				(new Thread(new FrameLaunch(sock))).start();						//This thread will launch my JFrame, which carries
				System.out.println("Received a connection from " + sock);			//the meat of the Server code.
				System.out.println("Server Online: type '!!Exit' to close Server.");
			}
		}
		catch (Exception e){
			System.out.println("Socket-related exception: " + e);
		}
	}
}

