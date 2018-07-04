import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.WindowConstants;

//Here we go, nightmare central. The biggest positive of this is that now that I know how irritating
//Swing can be to make changes in, I'll create a stronger outline before starting GUI work using Swing.

public class ServerFrame extends JFrame {

	private JPanel contentPane;				//Panel and Frame are just containers, I don't use them for much.
	String read,read1;						//My 2 reads, for 2 threads. one will read outgoing, one will read incoming.
	JTextArea textArea;						//textArea is nice, but I would have liked to use textPane, since it allows color editing
	//unfortunately I found that out when I'd already gotten everything fully working,
	//and switching to textPane requires a BUNCH of changes, which I wasn't down for.
	Socket socket;							//class socket variable, useful for stuff, as you'd imagine.
	BufferedReader reader=null;				//BufferedReader is nice for input, BufferedWriter SUCKS for output in my opinion,
	PrintWriter writer=null;				//I much preferred PrintWriter for output.  I really don't know the difference,
	private JTextField textField;			//but PrintWriter worked where BufferedWriter didn't.
	String quit="!!Quit";					//JTextField is my "entry" portion of the Jframe, where the server can type their input.
	JFrame frmChatWindow=null;				//quit String is for quitting via chat entry.
	String empty="";						//empty string


	//The ServerFrame inherits the socket aallll the way from ServerMain, and hands it to the class variable 'socket'.
	//And then madness commences.  Hope you like comments.

	public ServerFrame(Socket socket1) {
		socket=socket1;													//setting socket.
		JFrame.setDefaultLookAndFeelDecorated(true);					//calling Default settings JFrame static method
		frmChatWindow = new JFrame("Chat Window");						//instantiating JFrame to class variable
		frmChatWindow.setDefaultCloseOperation(WindowConstants.DO_NOTHING_ON_CLOSE);	//'x'ing out won't work, gotta type "!!Quit"
		frmChatWindow.setTitle("Chat Window");							//Sets the title of the Frame to "Chat Window"
		FlowLayout flowLayout = new FlowLayout();						//FlowLayout is just the kind of layout that I liked,
		flowLayout.setVgap(15);											//it "fits" the frame around my textArea.
		flowLayout.setHgap(15);
		frmChatWindow.getContentPane().setLayout(flowLayout);			
		String text = "Launching Chat: To Quit, type !!Quit \n";			//Intro text for chat.			
		textArea = new JTextArea(text, 30, 50);							//30 rows, 50 columns(of text/characters).
		textArea.setWrapStyleWord(true);
		textArea.setEditable(false);									//makes sure display window can't be edited.
		textArea.setPreferredSize(new Dimension(100, 5000));			//This is the "depth/breadth of the textArea, 
		JScrollPane scrollPane = new JScrollPane(textArea);				//it's at 5000 to retain more lines and allow for scroll down
		textArea.setLineWrap(true);										//LineWrap doesn't work great, but it works to wrap text.
		frmChatWindow.getContentPane().add(scrollPane);					//this adds scroll bars around the textArea.
		textField = new JTextField();
		scrollPane.setColumnHeaderView(textField);						//this puts the text Field at the top.
		textField.setColumns(10);										//Honestly, it defaulted to 10 and I saw no reason not to keep it that way.
		frmChatWindow.pack();									//No idea, something the design put in, don't know what'll happen if I remove it.
		frmChatWindow.setVisible(true);									//sets frame visible.

		//FromInput thread, takes in everything from client and displays it.

		Thread FromServer= new Thread() {
			@Override
			public void run() {
				try {
					reader = new BufferedReader(new InputStreamReader (socket.getInputStream())); //reads input from socket
					while(null!=(read=reader.readLine())){
						if (read.equals(quit)){						//if read is !!Quit, closes socket and chat window
							socket.shutdownInput();					//and closes input/output
							socket.shutdownOutput();
							socket.close();
							frmChatWindow.dispose();
						}
						if ((read.equals(empty))!=true){
							textArea.insert("Client: " + read+"\n",0);				//inserts text into textArea
							textArea.setCaretPosition(0);				//keeps the window focused on the uppermost text.
						}
					}
				} catch (IOException e) {
					// TODO Auto-generated catch block
				}
			}
		};

		//Output thread from server.

		Thread ToServer= new Thread() {
			@Override
			public void run() {

				try{
					writer = new PrintWriter(new OutputStreamWriter(socket.getOutputStream()),true);
					textField.addActionListener(new ActionListener() {		//This adds a listener to your text field, which responds to ENTER
						@Override
						public void actionPerformed(ActionEvent e) {		//when you press ENTER:
							read1=textField.getText();						//read1 takes all the text from your entry field
							if ((read1.equals(empty))!=true){
								textArea.insert("You: " + read1 + "\n",0);				//inserts it into textArea
								writer.println(read1);							//writes it out to the Output socket
								textField.selectAll();							//selects all in your input field so that you replace it next time
								textArea.setCaretPosition(0);					//keeps the window focused on uppermost text.
							}
							if(read1.equals(quit)){
								try {
									socket.shutdownInput();
									socket.shutdownOutput();
									socket.close();							//if you enter !!Quit, it will close the socket, shut down input/output,
									frmChatWindow.dispose();				//and close the chat frame
								} catch (IOException e1) {
									// TODO Auto-generated catch block
								}
							}

						}
					});
				}
				catch(Exception e){
					System.out.println("Oops.");
				}
			}
		};
		FromServer.start();				//Starts both threads.
		ToServer.start();

	}

}
