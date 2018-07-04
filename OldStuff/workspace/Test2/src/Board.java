//Header Comments in Frame.java


import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.Random;

import javax.swing.JPanel;

//Board class, holds most of my game info.
public class Board extends JPanel {
	Random random= new Random();		//Random number generator for Computer turns.
	int[][] box=new int[3][3];			//2d array representing the board
	int X=0,Y=0,x=0,y=0,turn=0, type=0;	//X and Y hold inputs from mouse location during mouseclicked, x and y hold quadrants in array.
										//turn and type are for distinguishing player's/computer's turn and marker type.
    boolean kill=true;					//boolean kill is toggled false when board is not full, and back to true when it fills up.
    boolean win=false;					//win is toggle false when win conditions are not met, and toggled true when conditions are satisfied.
    boolean compwin=false;				//compwin is set to false every new game, and set to true if win is toggled during comp's turn.
    private int wintype=0;				//wintype is a scale from 1-8 for different types of wins, used for drawing the line graphics.
	/**
	 * Create the panel.
	 */
    //Board holds no while loops, but simply responds to every mouseclick on the board with a sequence of events, depending on conditions.
	public Board() {

		addMouseListener(new MouseAdapter() {
			public void mouseClicked(MouseEvent arg0) {
				win();								//Immediately checks for win(). if win is true, will not let you modify the board.
				if(win==false){						//if false, enters loop, gets X/Y coords and (x,y) quadrant
				X=arg0.getX();
			    Y=arg0.getY();						
			    x=(int)(X/100);
			    y=(int)(Y/100);
			    if (turn==1){
			    	System.out.println("NOPE");  //This should never happen, but I've seen delays where it pops up, and now I'm paranoid.
			    }
			    else if (turn==2){				//This is the player's turn. sets the clicked box to 1 in the 2d array if player is X,
			    	if(box[x][y]==0){			//or sets it to 2 if player is O.
			    		if(type==1){
			    			box[x][y]=1;		//Then the marker type is switched for the computer's turn.
			    			type=2;
			    		}
			    		else if(type==2){
			    			box[x][y]=2;
			    			type=1;
			    		}
			    		turn=1;
			    		Frame.txtChooseFirstTurn.setText("COMPUTER'S TURN!");
			    	}
			    }
			    win();							//Again, checks win() for win conditions. if so, skips the rest of loop and goes to repaint.
			    if(win==false)					//if false, goes into compturn(), and after compturn, checks for a full array with kill.
			    	compturn();
				for(x=0;x<3;x++){
					for(y=0;y<3;y++){
						if(box[x][y]==0) kill=false;
					}
				}
				if (kill==true) win=true;		//if array is full, win is set to true, game is ended as a DRAW, repaints.
			    repaint();
			 }
			}
		});
	}
	
//paint method.  Actually the easiest part of the program, which is the opposite of what I expected.
public void paint(Graphics g) 
	{
		g.setColor(new Color(255,255,255));						//sets color to white
	    g.fillRect(0,0,getWidth(),getHeight());					//colors background white.
	    g.setColor(new Color(0,0,0));							//sets color to black.
	    g.drawLine(0,99,299,99); 								//Draws the board.
	    g.drawLine(99,0,99,299);
	    g.drawLine(199,0, 199, 299);
	    g.drawLine(0,199,299,199);
	    										
	    //This loop checks each quadrant of the 2d array 'box', and draws either an X, an O, or nothing, depending on the value in the array.
	    for( x = 0; x < 3; x++ ) {								
            for( y = 0; y < 3; y++ ) {
                if( box[x][y] == 1 ) {
                	g.setColor(new Color(255,0,0));    //sets color to Red for X's
                    g.drawLine( (x*100), (y*100), (x*100)+99, (y*100) + 99 );
                    g.drawLine( (x*100), (y*100) + 99, (x*100) + 99, (y*100) );
                } 
                else if( box[x][y] == 2 ){
                	g.setColor(new Color(0,0,255));		//sets color to Blue for O's
                    g.drawOval( (x*100) + 10, (y*100) + 10, 79, 79 );
                }
            }
	    
	   }
	    //If win conditional is met, this set of commands is executed as well.
	    if(win==true){
	    	g.setColor(new Color(255,0,255));			//Changes color to purple.
	    	Frame.rdbtnComputer.setEnabled(true);		//enables all of the external buttons again.
			Frame.rdbtnPlayer.setEnabled(true);
			Frame.rdbtnO.setEnabled(true);
			Frame.rdbtnX.setEnabled(true);
			Frame.btnNewGame.setEnabled(true);
														
	    	Graphics2D g2 = (Graphics2D) g;				//creates new Graphics2D variable
	    	g2.setStroke(new BasicStroke(4));			//increases line thickness
	    	if(kill==false){							//makes sure kill is toggled to false (this will only be true if kill toggled first,
	    	if(wintype==1)								//and then toggled win).
	    		g2.drawLine(49,49,49,249);   		
	    	if(wintype==2)
	    		g2.drawLine(249,49,249,249);
	    	if(wintype==3)
	    		g2.drawLine(149,49,149,249);
	    	if(wintype==4)							//Depending on which wintype occurred, different lines are drawn.
	    		g2.drawLine(49,49,249,49); 
	    	if(wintype==5)
	    		g2.drawLine(49,149,249,149); 
	    	if(wintype==6)
	    		g2.drawLine(49,249,249,249); 
	    	if(wintype==7)
	    		g2.drawLine(49,49,249,249); 
	    	if(wintype==8)
	    		g2.drawLine(49,249,249,49);
	    	}
	    	Frame.txtChooseFirstTurn.setText("");
	    }
}
//Compturn method, I wish I could have made the AI for this much more elaborate, but RNG will have to do.
public void compturn(){
	kill=true;								//This is to once again check for a full array before compturn begins.
	for(x=0;x<3;x++){
		for(y=0;y<3;y++){
			if(box[x][y]==0) kill=false;
		}									//if array is full, we return and end the game. otherwise, we enter the RNG loop.
	}
	if (kill==true) return;
	while(turn==1){
		x=random.nextInt(3);				//while turn is 1 (computer's), the RNG will continually pick new random numbers from 0-2,
		y=random.nextInt(3);				//and if the space is not occupied, it will place the appropriate marker in the array.
		if(box[x][y]==0){
			if(type==1){
    			box[x][y]=1;
    			type=2;
			}
			else if(type==2){
    			box[x][y]=2;
    			type=1;
    		}
    		turn=2;							//once a marker is allocated, turn is set to 2 (player), and the while loop is exited.
    		Frame.txtChooseFirstTurn.setText("PLAYER'S TURN!");
		}
		
	}
	win();									//checks for win conditional here, and if true, sets compwin to true as well.
	if(win==true) compwin=true;
	else kill=true;							//if not, sets kill to true. This is so that kill can be checked again in the main method,
}											//before proceeding to the player's turn.

//win method. checks for all the possible combinations necessary to win.  If a win is found, it assigns the appropriate integer value
//to the wintype variable so that we know what output to use.
public void win(){
	win=false;
	if((box[0][0]==1&&box[0][1]==1&&box[0][2]==1)||(box[0][0]==2&&box[0][1]==2&&box[0][2]==2)){
		win=true;
		wintype=1;									//8
		return;
	}
	if((box[2][0]==1&&box[2][1]==1&&box[2][2]==1)||(box[2][0]==2&&box[2][1]==2&&box[2][2]==2)){
		win=true;
		wintype=2;									//different
		return;
	}
	if((box[1][0]==1&&box[1][1]==1&&box[1][2]==1)||(box[1][0]==2&&box[1][1]==2&&box[1][2]==2)){
		win=true;
		wintype=3;									//possibilities
		return;
	}
	if((box[0][0]==1&&box[1][0]==1&&box[2][0]==1)||(box[0][0]==2&&box[1][0]==2&&box[2][0]==2)){
		win=true;
		wintype=4;									//to
		return;
	}
	if((box[0][1]==1&&box[1][1]==1&&box[2][1]==1)||(box[0][1]==2&&box[1][1]==2&&box[2][1]==2)){
		win=true;
		wintype=5;									//win.
		return;
	}
	if((box[0][2]==1&&box[1][2]==1&&box[2][2]==1)||(box[0][2]==2&&box[1][2]==2&&box[2][2]==2)){
		win=true;
		wintype=6;									//pretty
		return;										
	}
	if((box[0][0]==1&&box[1][1]==1&&box[2][2]==1)||(box[0][0]==2&&box[1][1]==2&&box[2][2]==2)){
		win=true;
		wintype=7;									//self
		return;
	}
	if((box[0][2]==1&&box[1][1]==1&&box[2][0]==1)||(box[0][2]==2&&box[1][1]==2&&box[2][0]==2)){
		win=true;
		wintype=8;									//explanatory.
		return;
	}
}
}
