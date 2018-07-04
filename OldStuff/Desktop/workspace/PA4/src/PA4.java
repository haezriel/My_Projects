//Main Header Comment Block
//Michael Allen-Bond
//CSE 223
//Programming Assignment 4: Good Luck Finding a Group, Social Anxiety Guy.
//I'm a little disappointed that I didn't find a group to do this assignment with,
//since that would have given me the time and resources to embellish and make something fancy,
//but on the other hand, doing it on my own also gave me a better understanding
//of how to use classes effectively.
//To use this program, update the Database variable with your list of questions,
//And then start. The program will instruct you from there.

import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.UnsupportedEncodingException;

//The main class, or as I now know it, the voice in the sky.
//This class yells orders at my Tree, and my Tree delegates and performs all the tasks,
//like a true middle manager.
public class PA4 {
		
	public static void main(String[] args) {
		String database= new String("/home/haezriel/QList.txt");  //Database variable,
									//change to appropriate text file.
		
		Tree List=null;				//List is a Tree, set to null.
		List=new Tree(database);	//List gets initialized, this actually performs
									//the ingest() function as well in Tree.java.
		
		int togglint=0;				//I don't know why I don't use booleans, I just
									//prefer ints because they can be used to switch between
									//more than 2 states.
		
		//Intro instructions, and then calls playgame method in the List Tree.
		//togglint calls inherit, which picks up a corresponding int from inside Tree.java.
		
		while (togglint!=2){		//togglint is used to determine whether we keep playing, or quit.
			System.out.println("New Game: You think of something, I'll ask Yes/No questions,");
			System.out.println("Respond with y or Y for yes, n or N for no, q or Q for quit.");
			System.out.println("Once you quit, the game will update the database file.");
			List.playgame(List.root,List.root);
			togglint=List.inherit(togglint);
		}
		//creates writer for rewriting file.
		System.out.println("Exiting game, updating Database");
		PrintWriter writer=null;
		//try/catch blocks for if the file is not found, or if UTF-8 encoding isn't accepted.
		try {
			writer = new PrintWriter(database, "UTF-8");
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (UnsupportedEncodingException e) {
			e.printStackTrace();
		}
		List.update(List.root,writer);  //calls update function, which traverses the tree and updates the file.
										
		writer.close();					//closes writer.
	}

}
