//Header comments in PA2Main
//wList Class and subclasses, also known as the portion of this assignment
//that took me 40 hours to finish.
public class wList {
		Node header;
	
	wList() {
			header=new Node();
			header.next=null;
	}
	
//Add function.  Takes in word and count from wordIndex,
//creates a temp node and wordnode, traverses the links until either null is reached,
//a matching word is found, or compareTo places the word in front of the next one,
//alphabetically. The word is then placed accordingly, using temp to assist in linking.

	void add(String word,int num){
			Node wordnode=new Node();
			Node temp=new Node();
			temp.next=header;
			wordnode.next=header.next;
			if (wordnode.next==null){
				wordnode.data=word;
				header.next=wordnode;
				wordnode.link.addnum(num);
				return;
			}
			while(wordnode.next!=null){
				if(0==word.compareTo(wordnode.next.data)){
					wordnode.next.link.addnum(num);
					return;
				}
				if(0>word.compareTo(wordnode.next.data)){
					wordnode.data=word;
					temp.next.next=wordnode;
					wordnode.link.addnum(num);
					return;
				}
				else{
					temp.next=wordnode.next;
					wordnode.next=wordnode.next.next;
				}
			}
			wordnode.data=word;
			wordnode.link.addnum(num);
			temp.next.next=wordnode;
			return;
	}
	
//Print function, if list is null, returns error message(if file is empty).
//otherwise, traverses list, and for every node, prints the word, and then calls printnum(),
//a subroutine to print the reference numbers.
	
	void print(){
		Node temp=new Node();
		temp.next=header.next;
		if (temp.next==null){
			System.out.println("This file contains no words.");
			return;
		}
		while (temp.next!=null){
			System.out.print(temp.next.data+" : ");
			temp.next.link.printnum();
			System.out.println();
			temp.next=temp.next.next;
		}
	}

//Node class holds String, Node, rList, initializes with empty rList.
	
class Node {
	String data;
	Node next;
	rList link;
	
	Node(){
		link=new rList();
	}

//rList class, holds header node "top", initializes with rNode.next set to null.
	
private class rList{
	rNode top;
	
	rList(){
		top=new rNode();
		top.next=null;
	}
	
//addnum function, takes in num, traverses down rList until null is reached,
//then adds num to the end of the list, using temp and numnode in the same way
//as the add() function.
	
	void addnum(int num){
		rNode numnode=new rNode();
		rNode temp=new rNode();
		numnode.count=num;
		numnode.next=top.next;
		temp.next=top;
		if (numnode.next==null){
			temp.next.next=numnode;
			return;
		}
		while(numnode.next!=null){
			temp.next=numnode.next;
			numnode.next=numnode.next.next;
		}
		temp.next.next=numnode;
		return;
	}
	
//printnum function, traverses rList and prints out count values in order,
//similar to print() function.

	void printnum(){
		rNode temp=new rNode();
		
		temp=top.next;
		if (temp==null){
			return;
		}
		while (temp.next!=null){
			System.out.print(temp.count+", ");
			temp=temp.next;
		}
		System.out.print(temp.count+" ");
	}
}

//rNode class, just a simple count and node pointer.

private class rNode {
	int count;
	rNode next;
}
}
}