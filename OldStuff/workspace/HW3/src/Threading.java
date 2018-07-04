import java.util.Scanner;

//Threading makes 3 doubles, 4 threads,and a Scanner.
public class Threading {
	double n1, n2,n3;
	
	Threading(){
	Scanner c= new Scanner (System.in);
	while (c.hasNext()){
		n1=c.nextDouble();
		n2=c.nextDouble();
		Thread addThread = new Thread() {
			public void run() {
				n3=n1+n2;
				System.out.println(n1+"+"+n2+"="+n3);
			}
		};
		Thread subThread = new Thread() {
			public void run() {

				n3=n1-n2;
				System.out.println(n1+"-"+n2+"="+n3);
			}
		};
		Thread mulThread = new Thread(){
			public void run() {
				n3=n1*n2;
				System.out.println(n1+"*"+n2+"="+n3);
			}
		};
		Thread divThread = new Thread(){
			public void run(){
				n3=n1/n2;
				System.out.println(n1+"/"+n2+"="+n3);
			
			}
		};
 //Starts the Threads, Joins them, prints happy little message.
		addThread.start();
		subThread.start();
		mulThread.start();
		divThread.start();
		try {
			addThread.join();
			subThread.join();
			mulThread.join();
			divThread.join();
			System.out.println("Threads Finished.");
		}
			catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		
	}
}
}