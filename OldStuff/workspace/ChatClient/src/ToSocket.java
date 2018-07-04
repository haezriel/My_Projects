import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;

//Output thread (from client)

public class ToSocket implements Runnable {
	Socket socket;								//Holds Socket
	String read=null;							//Holds output from System.in
	String quit="!!Quit";						//checks for !!Quit string
	String empty="";							//checks for empty strings
	
	ToSocket(Socket n){
		socket=n;								//inherits socket
	}

	@Override
	public void run() {
		Scanner reader=new Scanner(System.in);	//I used Scanner because I like it more than BufferedReader.
		PrintWriter writer=null;				//and I like PrintWriter more than BufferedWriter.
		
		try {
			writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()),true);
			while(reader.hasNext()){
														//if string is empty, skip outputting it to socket
				read=reader.nextLine();				
				if ((read.equals(empty))!=true){		//if not, outputs it to socket
					writer.println(read);
				}
				if (read.equals(quit)){					//if read is !!Quit, shuts down input/output,
					socket.shutdownInput();				//closes socket, exits Client.
					socket.shutdownOutput();
					socket.close();
					System.exit(0);
				}

			}
			writer.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
		}
	}

}


