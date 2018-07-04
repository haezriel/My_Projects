import java.net.Socket;

//FrameLaunch is just a sort of proxy between Main and the Frame.  I didn't really know what I wanted yet,
//So I created something like 8-9 classes just in the Server class to try and figure things out.
//This was probably the longest that I've worked on code, that was primarily writing and re-writing,
//Mostly because of my unfamiliarity with Swing.

public class FrameLaunch implements Runnable {				
	Socket socket;													

	FrameLaunch(Socket n){									//I inherit the socket from Main, and will pass it down again
		socket=n;											//to the Frame class.
	}
	@Override
	public void run() {			
		try {												//Again, nothing exciting, just initializing and setting visible
			ServerFrame frame = new ServerFrame(socket);	//This only exists in a separate class because I changed the frame
															//a LOT of different times, and this made it easier.
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	// TODO Auto-generated method stub

}

