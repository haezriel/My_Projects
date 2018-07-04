import java.util.Scanner;

//Poll, simple thread that just watches System.in on Server for Exit input
public class Poll implements Runnable {
	@Override
	
	public void run() {									
		Scanner scan=new Scanner(System.in);			//scanner for system.in
		String exit="!!Exit";							//Exit match string
		String read=null;								
		while(scan.hasNext()){							//checks for input
			read=scan.next();
			if (read.equals(exit)){
				System.out.println("Closing Server.");	//if !!Exit, closes Server.
				System.exit(0);
			}
		}
		// TODO Auto-generated method stub

	}

}
