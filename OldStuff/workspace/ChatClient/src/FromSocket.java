import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

//Input (from server) thread.

public class FromSocket implements Runnable {
	Socket socket;									//class variable to hold socket input
	String read;									//class variable to hold string from input
	String quit="!!Quit";							//checks for !!Quit entry
	String empty="";
	FromSocket(Socket n){	
		socket=n;									//inherits socket from Main.
	}
	@Override
	public void run() {
		BufferedReader reader=null;
		try{
			reader = new BufferedReader(new InputStreamReader (socket.getInputStream()));
			while(null!=(read=reader.readLine())){			//read takes input from BufferedReader (from socket input)
				if (read.equals(quit)){						//if read equals quit,closes input/output
					socket.shutdownInput();					// shuts down socket and exits client.
					socket.shutdownOutput();
					socket.close();
					System.exit(0);

				}
				if ((read.equals(empty))!=true)
				System.out.println("Server: " + read);					//otherwise, it just prints output(as long as it's not empty)
			}
		}
		catch(Exception e){

		}
		// TODO Auto-generated method stub

	}

}
