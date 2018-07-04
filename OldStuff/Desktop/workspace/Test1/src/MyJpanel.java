import java.awt.Graphics;

import javax.swing.JPanel;


public class MyJpanel extends JPanel {
	public void paint (Graphics g)
	{
		super.paint(g);
		g.drawRect(0, 0, 100, 100);
	}

}
