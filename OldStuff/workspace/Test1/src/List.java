
public class List {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Link mainList=new Link();
		mainList.add("goodbye");
		mainList.add("there");
		mainList.add("potato");
		mainList.print();
	}

}
	class Link{
		Node header;
		
		Link(){
			header=new Node();
			header.next=null;
		}
		
		void add(String word){
			Node newnode=new Node();
			newnode.data=word;
			newnode.next=header.next;
			header.next=newnode;
		}
		void print(){
			Node temp=header;
			while (temp.next != null){
				temp=temp.next;
				System.out.print(temp.data+" ");
			}
			System.out.println("");
		}
	}
	class Node{
		String data;
		Node next;
	}