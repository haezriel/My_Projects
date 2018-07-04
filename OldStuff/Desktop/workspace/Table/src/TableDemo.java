/*
 * TableDemo.java is a 1.4 application that requires no other files.
 */

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;

import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;

/** 
 * TableDemo is just like SimpleTableDemo, except that it
 * uses a custom TableModel.
 */
public class TableDemo extends JPanel {
    private boolean DEBUG = false;

    public TableDemo() {
        super(new GridLayout(1,0));
        VehiclesObject v=new VehiclesObject(5,"potat","pwer","234","jj24j24",25);
        MyTableModel display=new MyTableModel();
        String S1=v.make;
        String S2=v.model;
        String S3=v.color;
        String S4=v.licensePlate;
        int i1=v.idvehicle;
        int i2=v.mileage;
        	
        JTable table = new JTable(display);
        display.setValueAt(i1,0,0);
    	display.setValueAt(S1, 0, 1);
    	display.setValueAt(S2,0,2);
    	display.setValueAt(S3, 0, 3);
    	display.setValueAt(S4,0,4);
    	display.setValueAt(i2,0,5);
        
        
        table.setPreferredScrollableViewportSize(new Dimension(500, 70));

        //Create the scroll pane and add the table to it.
        JScrollPane scrollPane = new JScrollPane(table);

        //Add the scroll pane to this panel.
        add(scrollPane);
    }

    class MyTableModel extends AbstractTableModel {

    	
        private String[] columnNames = {"First Name",
                                        "Last Name",
                                        "Sport",
                                        "# of Years",
                                        "Vegetarian"};
        private Object[][] data = {
                {"Mary", "Campione",
                 "Snowboarding", new Integer(5), new Boolean(false), new Boolean(true)},
                {"Alison", "Huml",
                 "Rowing", new Integer(3), new Boolean(true),new Boolean(true)},
                {"Kathy", "Walrath",
                 "Knitting", new Integer(2), new Boolean(false),new Boolean(true)},
                {"Sharon", "Zakhour",
                 "Speed reading", new Integer(20), new Boolean(true),new Boolean(true)},
                {"Philip", "Milne",
                 "Pool", new Integer(10), new Boolean(false),new Boolean(true)}
            };
        
        

        
    
        public int getColumnCount() {
            return columnNames.length;
        }

        public int getRowCount() {
            return data.length;
        }

        public String getColumnName(int col) {
            return columnNames[col];
        }

        public Object getValueAt(int row, int col) {
            return data[row][col];
        }

        /*
         * JTable uses this method to determine the default renderer/
         * editor for each cell.  If we didn't implement this method,
         * then the last column would contain text ("true"/"false"),
         * rather than a check box.
         */
        public Class getColumnClass(int c) {
            return getValueAt(0, c).getClass();
        }

        /*
         * Don't need to implement this method unless your table's
         * editable.
         */
        public boolean isCellEditable(int row, int col) {
            //Note that the data/cell address is constant,
            //no matter where the cell appears onscreen.
            if (col < 2) {
                return false;
            } else {
                return true;
            }
        }

        /*
         * Don't need to implement this method unless your table's
         * data can change.
         */
        public void setValueAt(Object value, int row, int col) {
            if (DEBUG) {
                System.out.println("Setting value at " + row + "," + col
                                   + " to " + value
                                   + " (an instance of "
                                   + value.getClass() + ")");
            }

            data[row][col] = value;
            fireTableCellUpdated(row, col);

            if (DEBUG) {
                System.out.println("New value of data:");
                printDebugData();
            }
        }

        private void printDebugData() {
            int numRows = getRowCount();
            int numCols = getColumnCount();

            for (int i=0; i < numRows; i++) {
                System.out.print("    row " + i + ":");
                for (int j=0; j < numCols; j++) {
                    System.out.print("  " + data[i][j]);
                }
                System.out.println();
            }
            System.out.println("--------------------------");
        }
    }

    /**
     * Create the GUI and show it.  For thread safety,
     * this method should be invoked from the
     * event-dispatching thread.
     */
    private static void createAndShowGUI() {
        //Make sure we have nice window decorations.
        JFrame.setDefaultLookAndFeelDecorated(true);

        //Create and set up the window.
        JFrame frame = new JFrame("TableDemo");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        //Create and set up the content pane.
        TableDemo newContentPane = new TableDemo();
        newContentPane.setOpaque(true); //content panes must be opaque
        frame.setContentPane(newContentPane);

        //Display the window.
        frame.pack();
        frame.setVisible(true);
    }
}