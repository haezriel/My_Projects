//Michael Allen-Bond
//CSE 223
//Header comments in PA2Main

import java.io.File;
import java.util.Scanner;

//wordIndex class, sets variable List as an empty wList, sets mystatus to false

public class wordIndex {
	private boolean mystatus=false;
		wList List=new wList();

//Brings in File pointer, points to string argument brought in from PA2Main,
//try begins with a Scanner that reads fp, converts all to uppercase,
//and then sends them into a second scanner that rereads the strings,
//and parses/indexes them into the list, while also entering in the count,
//which is the word's position in the file.
//once indexing is complete, the scanners are closed, status set to true.
		
	public wordIndex(String file){
		File fp=new File(file);
		try{
			Scanner reader=new Scanner(fp);
			String str=new String();
			String word=new String();
			int count=0;
			while(reader.hasNext()){
				str=reader.next();
				str=str.toUpperCase();
				str=str.replaceAll("[^A-Za-z ]", " ");
				Scanner parser=new Scanner(str);
				while(parser.hasNext()){
					word=parser.next();
					count=count+1;
					List.add(word, count);
				}
				parser.close();
			}
			reader.close();
			mystatus=true;
			}
			catch (Exception eee){
				System.out.println("Invalid file entry, please enter text file.");
			}

	}
	
//Simple status, basically the one that we discussed in class, returns value
//of private boolean mystatus.
	
	public boolean status(){
		return mystatus;
	}
	
//Print function, just calls the print function from wList.
	
	void print(){
		System.out.println("Indexed in Alphabetical Order, With Word Locations:");
		List.print();
	}
}
