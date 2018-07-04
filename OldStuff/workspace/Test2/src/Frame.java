//Michael Allen-Bond
//CSE 223
//Programming Assignment 3: The Great Calamity of Our Age.
//Herein Lies the last Will and Testament of Michael The Brave and Incompetent,
//Who had no idea how to use Swing,
//And spent 7 million hours spent googling things that he thought would help, but did not help at all.
//Finally, in memory of the previous 5 days spent getting 4 hours of sleep,
//brute-forcing my dumb, angry way through this code,  I will now have a 22 hour moment of silence,
//followed immediately by brain-death.
//To use this program, you just launch it, select who goes first, select which marker you want to be,
//and then press New Game.  Once you win, lose, or Tie, you can start a new game, or change the options.


import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JRadioButton;
import javax.swing.JTextField;
import javax.swing.ButtonGroup;
import java.awt.Font;
import javax.swing.SwingConstants;

//The main JFrame class. includes my main program as well, I didn't want to mess with that stuff,
//being unfamiliar with Swing.
public class Frame extends JFrame {
	JPanel contentPane;
	int i=0,j=0;				//Counters
	Board panel = new Board();		//extended Jpanel for my board.
	
	//These are my buttons. I made them static so that I could use them in Board.java when I finish the game.
	static JRadioButton rdbtnComputer = new JRadioButton("Computer Goes First");  
	static JRadioButton rdbtnPlayer = new JRadioButton("Player Goes First");
	static JRadioButton rdbtnO = new JRadioButton("Player is O");
	static JRadioButton rdbtnX = new JRadioButton("Player is X");
	static JButton btnNewGame = new JButton("Start Game");
	
	//Text fields and Button Groups, 1 group for the Player or Comp going first,
	//Second group for X or O.
	static JTextField txtChooseFirstTurn;
	private final ButtonGroup buttonGroup = new ButtonGroup();
	private final ButtonGroup buttonGroup_1 = new ButtonGroup();
	/**
	 * Launch the application.
	 */
	
	//I don't know what EventQueue does, so I didn't mess with this portion,
	//since it's irrelevant to my actual classes and essentially just launches the Frame.
	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Frame frame = new Frame();
					frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the frame.
	 */
	//See, I think the biggest problem with making this assignment due in 9 days,
	//Is that it took me about 5-6 of those days to download the right version of Eclipse,
	//Get Swing working properly, figure out the various frames and GUI options,
	//and then actually learn the interface to make things do what I wanted in the Frame/Panel.
	//This is most likely why so many students are feeling rushed on this assignment.
	//Now that we all definitely have Swing, and have some idea of how to operate within it,
	//It would be more feasible to have an assignment with a shorter completion time.
	//As for this assignment, it works and does everything it's supposed to,
	//but I didn't have time to "make it pretty", or really flesh it out at all, which I would have liked to do.
	public Frame() {
		addMouseMotionListener(new MouseMotionAdapter() {
			@Override
			//This is just an updater that changes the message at the top depending on various states,
			//to indicate a Draw, a win, or a loss.  It will update every time the mouse is moved.
			public void mouseMoved(MouseEvent arg0) {
			    if (panel.win==true){			//win is a boolean inside Board.java, that toggles on if the game is over
			    	
			    	panel.win=false;			//once we're inside the if statement, win is set back to false.
			    	if (panel.kill==true)		//kill is another boolean that toggles when the array is full, also toggles win.
			    		txtChooseFirstTurn.setText("DRAW.");	//if kill is toggled on, the array is full with no win, and it's a draw.
			    	else if (panel.compwin==false)		//this is another boolean that distinguishes computer wins from player wins.
			    		txtChooseFirstTurn.setText("You Won, How Exhilarating.");
			    	else txtChooseFirstTurn.setText("You Lost, How Horridly Shameful.");
			    }
			}
		});
		
		//Initialization of JFrame. Sets dimensions, sets to exit the program when you close the window
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setBounds(100, 100, 652, 504);
		contentPane = new JPanel();			//This Jpanel holds everything inside the frame, and is the main variable for interacting with
											//objects inside the panel. However, I chose to make my variables outside of Frame(), so that
											//they can be interacted with more easily.
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(null);
		
		//panel is my variable for my board, which is the extended Jpanel. I set the bounds to be 300 sq. units,
		//since that seemed to be the desired size for this assignment.
		panel.setBounds(250, 150, 299, 299);
		contentPane.add(panel);
		

		btnNewGame.addMouseListener(new MouseAdapter() {
			@Override
			//This is a mouse listener on my New Game button, designed to reset variables and launch a new game
			//when appropriate options are selected.  Also disables everything during games so that people don't mess with options,
			//or alter them accidentally.
			public void mouseClicked(MouseEvent e) {
				if(btnNewGame.isEnabled()==true){		//if the button is disabled, skips everything, disables functionality.
				if((rdbtnComputer.isSelected()==true||rdbtnPlayer.isSelected()==true)&&(rdbtnO.isSelected()==true||rdbtnX.isSelected()==true)){
					if(rdbtnComputer.isSelected()==true){ 				//These are all toggle checks to determine the parameters of the game.
						panel.turn=1;									//If Computer is first, it will set the marker types accordingly,
						if(rdbtnO.isSelected()==true) panel.type=1;		//and set turn to 1
						if(rdbtnX.isSelected()==true) panel.type=2;
					}
					if(rdbtnPlayer.isSelected()==true){					//If player is selected, turn is set to 2,
						panel.turn=2;									//marker types are set accordingly.
						if(rdbtnO.isSelected()==true) panel.type=2;
						if(rdbtnX.isSelected()==true) panel.type=1;
					}
					
					//This will disable all the buttons, to prevent tampering ingame.
					rdbtnComputer.setEnabled(false);
					rdbtnPlayer.setEnabled(false);
					rdbtnO.setEnabled(false);
					rdbtnX.setEnabled(false);
					btnNewGame.setEnabled(false);
					
					//Text box update.
					txtChooseFirstTurn.setText("SEIZE YOUR DESTINY YOUNG ONE!!");
					for(i=0;i<3;i++){					//This loop sets all the boxes in the 2d array to 0, creating a blank board.
						for(j=0;j<3;j++){				//then repaint is called.
							panel.box[i][j]=0;
							panel.repaint();
						}
					}
					if(panel.turn==1){			//This checks if turn is 1(comp goes first), and if so, immediately calls computer's turn.
						panel.compturn();
					}
					panel.compwin=false;		//This sets the boolean compwin to false. if comp wins, it will be set to true inside
				}								//board.java alongside the boolean win, and is reset with every new game.
				}
			}
		});
		btnNewGame.setBounds(55, 124, 117, 25);
		contentPane.add(btnNewGame);			//Sets button bounds, adds into contentPane Jpanel.
		
		buttonGroup.add(rdbtnComputer);			//This adds the computer radio button to buttonGroup
		//Computer Radio Button Listener		
		rdbtnComputer.addMouseListener(new MouseAdapter() {
			@Override
			//These listeners used to have a LOT more going on in them, but i was finding them unreliable,
			//so now they're all just set to refresh the text message.
			public void mouseClicked(MouseEvent e) {
				txtChooseFirstTurn.setText("Choose X or O, and Choose Who Goes First.");
			}
		});
		rdbtnComputer.setBounds(55, 225, 170, 23);	//button bounds, adds to contentPane
		contentPane.add(rdbtnComputer);
		
		buttonGroup.add(rdbtnPlayer);		// adds Player radio button to buttonGroup, creates toggle between player and comp
		//Player Radio Button Listener
		rdbtnPlayer.addMouseListener(new MouseAdapter() {
			@Override
			//Same deal, used to be more here, but I found more reliable methods for toggling options.
			public void mouseClicked(MouseEvent e) {
				txtChooseFirstTurn.setText("Choose X or O, and Choose Who Goes First.");
			}
		});
		rdbtnPlayer.setBounds(55, 273, 149, 23); //button bounds, adds to contentPane
		contentPane.add(rdbtnPlayer);
		
		buttonGroup_1.add(rdbtnO);				//adds rdbtnO to buttonGroup_1, creates toggle between O and X
		//Radio Button for O
		rdbtnO.addMouseListener(new MouseAdapter() {
			@Override
			//Updates text box, nothing more.
			public void mouseClicked(MouseEvent e) {
				txtChooseFirstTurn.setText("Choose X or O, and Choose Who Goes First.");
			}
		});
		rdbtnO.setBounds(55, 314, 149, 23);		//redundant commenting..
		contentPane.add(rdbtnO);
		
		buttonGroup_1.add(rdbtnX);
		//Radio Button for X
		rdbtnX.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				txtChooseFirstTurn.setText("Choose X or O, and Choose Who Goes First.");
			}
		});
		rdbtnX.setBounds(55, 353, 149, 23);
		contentPane.add(rdbtnX);
		
		//Creates text field, everything is self-explanatory except for setColumns, I couldn't figure out what that does.
		txtChooseFirstTurn = new JTextField();
		txtChooseFirstTurn.setEditable(false);
		txtChooseFirstTurn.setHorizontalAlignment(SwingConstants.CENTER);
		txtChooseFirstTurn.setFont(new Font("Dialog", Font.PLAIN, 16));
		txtChooseFirstTurn.setText("Choose X or O, and Choose Who Goes First.");
		txtChooseFirstTurn.setBounds(56, 42, 458, 50);
		contentPane.add(txtChooseFirstTurn);
		txtChooseFirstTurn.setColumns(10);
	}
}
