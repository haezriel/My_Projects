/*   Car-L-Marx
 *
 *   Oct 19, 2014  
 *   CS 320 Fall 2014
 *
 *		Michael Allen-Bond
 *		Lise Driggers
 *		Jesse Pomerenk
 *
 *		Components
 *
 *   TabbedMenu.java
*/
package Components;

import javax.swing.JPanel;
import javax.swing.JTabbedPane;
import javax.swing.ImageIcon;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFrame;
import javax.swing.JComponent;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.UIManager;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.event.KeyEvent;
import java.awt.Color;
import org.eclipse.wb.swing.FocusTraversalOnArray;
import java.awt.Component;
import javax.swing.JComboBox;
import javax.swing.JButton;

public class TabbedMenu extends JPanel
{
	private JPanel panel_1;
	private JLabel lblSummary;
	private JLabel lblToDoList;
	private JLabel lblOptional;
	private JPanel panel_2;
	private JPanel panel;
	private JLabel filler;
	private JTextField txtMileage;
	private JTextField txtOilChange;
	/**
	 * Create the panel.
	 */
	public TabbedMenu()
	{
        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.setBounds(0, 0, 640, 800);
       ImageIcon icon = createImageIcon("Hat.png");
        setLayout(null);
        
        JComponent panel1 = makeTextPanelSummary("");
        tabbedPane.addTab("Summary", new ImageIcon("/Users/Lise/Documents/workspace/Java/TabbedPanes/Hat.png"), panel1,
                "");
        tabbedPane.setMnemonicAt(0, KeyEvent.VK_1);
        
        JComponent panel2 = makeTextPanelEditCar("Panel #2");
        tabbedPane.addTab("Edit Car", new ImageIcon("/Users/Lise/Documents/workspace/Java/TabbedPanes/Boiler.png"), panel2,
                "Does twice as much nothing");
        
        JButton btnSubmit = new JButton("Submit");
        btnSubmit.setBounds(301, 223, 117, 29);
        panel_2.add(btnSubmit);
        
        tabbedPane.setMnemonicAt(1, KeyEvent.VK_2);
        
        JComponent panel3 = makeTextPanelEdit("Panel #3");
        tabbedPane.addTab("New Car", icon, panel3,
                "Still does nothing");
        tabbedPane.setIconAt(2, new ImageIcon("/Users/Lise/Documents/workspace/Java/TabbedPanes/Pumpkin.png"));
        tabbedPane.setMnemonicAt(2, KeyEvent.VK_3);
        
        JComponent panel4 = makeTextPanelDelete( "");
        panel4.setPreferredSize(new Dimension(600, 600));
        tabbedPane.addTab("Delete Car", new ImageIcon("/Users/Lise/Documents/workspace/Java/TabbedPanes/Bats.png"), panel4,
                "Does nothing at all");
        tabbedPane.setMnemonicAt(3, KeyEvent.VK_4);
        
        //Add the tabbed pane to this panel.
        add(tabbedPane);
        
        //The following line enables to use scrolling tabs.
        tabbedPane.setTabLayoutPolicy(JTabbedPane.SCROLL_TAB_LAYOUT);
   
	}
    protected JComponent makeTextPanelEdit(String text) {
        panel = new JPanel(false);
        panel.setBackground(new Color(255, 255, 240));
        panel.setLayout(null);
        filler = new JLabel(text);
        filler.setBounds(0, 0, 579, 754);
        filler.setHorizontalAlignment(JLabel.CENTER);
        panel.add(filler);
        return panel;
    }
    
    protected JComponent makeTextPanelDelete(String text) {
    	panel = new JPanel(false);
    	panel.setBackground(new Color(255, 255, 240));
    	panel.setLayout(null);
    	filler = new JLabel(text);
    	filler.setBackground(new Color(255, 255, 240));
    	filler.setBounds(0, 0, 579, 754);
    	filler.setHorizontalAlignment(JLabel.CENTER);
    	panel.add(filler);
    	return panel;
    }
    
    protected JComponent makeTextPanelEditCar(String text) {
    	panel_2 = new JPanel(false);
    	panel_2.setBackground(new Color(255, 255, 240));
    	panel_2.setLayout(null);
    	
    	{
    		JLabel lblMake = new JLabel("Make");
    		lblMake.setBounds(36, 30, 61, 16);
    		panel_2.add(lblMake);
    	}
    	{
            JComboBox cbxMake = new JComboBox();
            cbxMake.setBounds(36, 50, 178, 27);
            panel_2.add(cbxMake);
    	}
    	{
    		JLabel lblModel = new JLabel("Model");
    		lblModel.setBounds(36, 80, 61, 16);
    		panel_2.add(lblModel);
    	}
    	{
    		JComboBox cbxModel = new JComboBox();
    		cbxModel.setBounds(36, 100, 178, 27);
    		panel_2.add(cbxModel);
    	}
    	{
    		JLabel lblModel = new JLabel("Mileage");
    		lblModel.setBounds(36, 130, 61, 16);
    		panel_2.add(lblModel);
    	}
    	{
            txtMileage = new JTextField();
            txtMileage.setBounds(36, 150, 134, 28);
            panel_2.add(txtMileage);
            txtMileage.setColumns(10);
    	}
    	{
    		JLabel lblOilChange = new JLabel("Last Oil Change");
    		lblOilChange.setBounds(36, 180, 134, 16);
    		panel_2.add(lblOilChange);
    	}
    	{
    		txtOilChange = new JTextField();
    		txtOilChange.setBounds(36, 200, 134, 28);
    		panel_2.add(txtOilChange);
    		txtOilChange.setColumns(10);
    	}
    	
    	
    	return panel_2;
    }
    
    protected JComponent makeTextPanelSummary(String text) {
    	panel_1 = new JPanel(false);
    	panel_1.setBackground(new Color(255, 255, 240));
    	
    	panel_1.setLayout(null);
    	{
    		lblSummary= new JLabel("Vehicle Name, Info Summary");
    		lblSummary.setBounds(21, 21, 225, 19);
    		lblSummary.setFont(new Font("Lucida Grande", Font.BOLD, 15));
    		lblSummary.setBackground(new Color(255, 255, 240));
    		panel_1.add(lblSummary);
    	}
    	{
    		lblToDoList = new JLabel("To-Do List");
    		lblToDoList.setBounds(21, 94, 225, 19);
    		lblToDoList.setFont(new Font("Lucida Grande", Font.BOLD, 15));
    		lblToDoList.setBackground(new Color(255, 255, 240));
    		panel_1.add(lblToDoList);
    	}
    	{
    		lblOptional = new JLabel("Optional Information");
    		lblOptional.setBounds(21, 159, 225, 19);
    		lblOptional.setFont(new Font("Lucida Grande", Font.BOLD, 15));
    		lblOptional.setBackground(new Color(255, 255, 240));
    		panel_1.add(lblOptional);
    	}
 
    	return panel_1;
    }
    
    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from
     * the event dispatch thread.
     */
    private static void createAndShowGUI() {
        //Create and set up the window.
        JFrame frame = new JFrame("TabbedPaneDemo");
        frame.setBounds(100, 100, 650, 800);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        //Add content to the window.
        frame.getContentPane().add(new TabbedMenu(), BorderLayout.CENTER);
        
        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
    
    /** Returns an ImageIcon, or null if the path was invalid. */
    protected static ImageIcon createImageIcon(String path) {
        java.net.URL imgURL = TabbedMenu.class.getResource(path);
        if (imgURL != null) {
            return new ImageIcon(imgURL);
        } else {
            System.err.println("Couldn't find file: " + path);
            return null;
        }
    }
    
    public static void main(String[] args) {
        //Schedule a job for the event dispatch thread:
        //creating and showing this application's GUI.
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                //Turn off metal's use of bold fonts
		UIManager.put("swing.boldMetal", Boolean.FALSE);
		createAndShowGUI();
            }
        });
    }
}
