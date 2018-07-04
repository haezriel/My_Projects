import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.util.Scanner;


public class StringTesting {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try{
		FileReader fr=new FileReader("/home/haezriel/test.txt");
		BufferedReader br=new BufferedReader(fr);
		int temp;
		while((temp=br.read())!= -1){
			System.out.println("<"+temp+">");
		}
		fr.close();
		}
		catch (Exception eee){
			System.out.println("oh no." + eee);
			
		}
	}

}
