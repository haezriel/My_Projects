//Michael Allen-Bond
//CSE 223
//4/28/2014
//Main Program Block
//This program will take in a file and index all the words in the file in alphabetical order,
//I wanted to implement Swing to make an interface for selecting the file to index,
//But I apparently had the wrong IDE.
//The print function can be called from here, or from inside wordIndex using List.print();
//The status updates automatically to true once the indexing is complete.


public class PA2Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		String r=new String("/home/haezriel/test.txt");
		wordIndex wordlist=new wordIndex(r);
		if(wordlist.status()==true){
			wordlist.print();
		}
	}



}