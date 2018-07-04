import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.Scanner;
//Header Comments in Main block

//Tree Class, middle manager, calls all the methods and uses Node for manual labor.
public class Tree {
	Node root;				//root Node, self-explanatory
	File fp;				//file pointer to assign to Database
	Scanner reader;			//Scanner to read from file.
	String a=new String("A:");		//Strings with static values for comparison
	String q=new String("Q:");
	Scanner read;					//Scanner for System.in
	String answer;					//holds user input.
	String y=new String("Y");		//More static comparison strings.
	String n=new String("N");
	String Q=new String("Q");
	int key=0;						//This toggles how the tree is modified.
	int togglenum;					//This toggles whether the game exits or continues on return
	
	Tree(String data){
		read=new Scanner(System.in);		//scanner for user input
		root=null;				
		try {						//tries to open file using data string(Database)
			File flip = new File(data);
		fp=flip;					//sets global File variable to local file
			Scanner flop=new Scanner(fp);
			reader=flop;			//sets global Scanner to local Scanner(of file)
		} 
		catch (FileNotFoundException e) {
			//Error block, exits program if something is wrong.
			System.out.println("Please make sure your file exists.");
			System.exit(0);
		}
		root=ingest();				//Calls ingest method, which reads file into a binary tree.
	}
	
	Node ingest(){
		
		Node Set=new Node();		//initializes empty Node.
		String Toggle=new String();	//initializes toggle String (for A: or Q:)
		Toggle=reader.nextLine();	//Sets Toggle to first line (Q: or A:)
		Set.text=reader.nextLine();	//Sets node.text to second line
		if(Toggle.equals(a)==true){
			Set.yes=Set.no=null;	//if toggle is an answer, sets yes and no to null.
			return Set;
		}
		else if(Toggle.equals(q)==true){
			try{
				Set.yes=ingest();		//if toggle is a question, recursively calls ingest
				Set.no=ingest();		//on node.yes and node.no
			}
			catch(Exception f){			//catches if Q: is followed by nothing.
				System.out.println("Formatting error in file.");
				System.exit(0);
			}
			return Set;
		}
		else{						//if there's a formatting error in file, this happens.
			System.out.println("Text file formatted incorrectly.");
			System.exit(0);			
		}
		return Set;					
		
	}
	
	//playgame method, takes in previous node and current node (both root at beginning),
	//and then progresses through tree from there, asking questions
	void playgame(Node prev,Node core){
									
		Node Travel=new Node();				//Travel node is current node	
		Node Previous=new Node();			//Previous is self-explanatory.
		Previous=prev;													
		Travel=core;	
		System.out.println(core.text);		//prints out question or answer text
		while(read.hasNext()){				//loop continuously checks for input
			answer=read.next();				//user reply
			answer=answer.toUpperCase();	//converts to uppercase
			if(answer.equals(y)==true){
				if(Travel.yes!=null){		//if yes, checks for null, and then
					key=1;					//travels to yes node, calls playgame with travel and .yes nodes
					playgame(Travel,Travel.yes); //toggles key
					return;
				}
				else
					System.out.println("Too easy.");//if travel.yes is null, then the game is over.
					return;
				}
			else if(answer.equals(n)==true){
				if(Travel.no!=null){		//checks for null,
					key=2;					//calls playgame, hands in travel and .no nodes
					playgame(Travel,Travel.no); //toggles key
					return;
				}
				else {
					System.out.println("Alright, smart guy, you stumped me.");
					add(Previous);		//if this is the final node and user says no,
					return;				//our guess was wrong, and we go to add method.
				}
			}
			else{
				if(answer.equals(Q)==true){
					togglenum=2;		//if user enter Q, we change togglenum, and return.
					return;
				}
				//if user has  invalid input, they get an error message.
				System.out.println("Invalid response.");
				System.out.println("Let's try that again:");
				System.out.println(core.text);
				
			}
		}
	}
	
	void add(Node addit){
		Node added=new Node();		//creates two nodes, one for new question,
		Node addend=new Node();		//and one for new answer.
		System.out.println("So, what was the answer?");
		read.nextLine();			//reads answer
		answer=read.nextLine();		
		addend.text=answer;			//assigns to node.
		System.out.println("Ok, good, now give me a Yes/No question to help me guess that answer.");
		answer=read.nextLine();
		added.text=answer;			//reads question, assigns to node
		System.out.println("Updating Tree.");
		if (key==1){
			added.no=addit.yes;		//if key is 1, then we answered the final question with yes,
			addit.yes=added;		//so we attach our new question to that question's .yes node,
			added.yes=addend;		//and then set the wrong answer to our .no node,
		}							//and the right answer to our .yes node.
		else if (key==2){			
			added.no=addit.no;		//Same thing, but if the key is 2, then we attach the new question
			addit.no=added;			//onto the .no node of our previous question.
			added.yes=addend;
		}
	}
	
	//inherit. a tiny function that simply takes our togglenum (which toggles if we enter "q")
	//and sets num equal to it, which is returned to our while loop in PA4
	int inherit(int num){
		num=togglenum;
		return num;
	}
	
	//update method, once we're done playing, this will traverse our whole tree,
	//and write it back into the file.
	public void update(Node root,PrintWriter writer){
		if (root==null) return;				//the writer is initialized in PA4, and then passed into this method.
		if (root.yes!=null && root.no!=null){
		writer.println("Q:");				//if root is null, we just return, else, we traverse.
		writer.println(root.text);			//if .no and .yes aren't null, it must be a question,
		}									//so we write accordingly.
		else{
			writer.println("A:");			//if they are null, then it must be an answer,
			writer.println(root.text);		//and again, we write accordingly.
		}
		update(root.yes,writer);			//we then traverse the rest of the tree recursively,
		update(root.no,writer);				//using pre-order (NLR)traversal.
		return;
		
	}
}
