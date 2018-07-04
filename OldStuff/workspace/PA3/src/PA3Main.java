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

import java.awt.EventQueue;

//Main program, basically just a formality to launch the Frame.
public class PA3Main {

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

}
