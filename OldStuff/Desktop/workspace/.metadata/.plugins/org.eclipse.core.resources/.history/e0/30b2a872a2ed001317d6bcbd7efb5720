//Main Header Comments are located in ServerMain


import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;


public class ClientMain {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		String quit="!!Quit";								//checks for !!Quit entry in main
		int correctport=0;									//checks for correct port
		Socket sock=null;												//new socket
		String port=null;
		Scanner read=new Scanner(System.in);				//asks for IP address
		while (correctport==0){
		System.out.print("Enter IP Address: ");
		port=read.nextLine();
		System.out.println(port);
		if(port.equals(quit)==true)
			System.exit(0);
		try {
			sock=new Socket(port,1201);					//attempts to contact server
			correctport=1;
		} catch (UnknownHostException e1) {
			// TODO Auto-generated catch block
			System.out.println("Socket-related exception: " + e1);
		} catch (IOException e1) {
			// TODO Auto-generated catch block
			System.out.println("Socket-related exception: " + e1);
		}						
		}
		try{
			System.out.println("Connected to " + sock);				
			(new Thread(new FromSocket(sock))).start();				//launches FromSocket (input),
			(new Thread(new ToSocket(sock))).start();			//and ToSocket(output).  This was also how the server was set up at first.

		} catch (Exception e){
			System.out.println("Socket-related exception: " + e);
			System.exit(0);
		}

	}

}
