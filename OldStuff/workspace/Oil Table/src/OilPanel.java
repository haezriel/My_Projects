import javax.swing.JPanel;
import javax.swing.JTextField;


public class OilPanel extends JPanel {
	private JTextField textField;

	/**
	 * Create the panel.
	 */
	public OilPanel() {
		
		textField = new JTextField();
		add(textField);
		textField.setColumns(10);

	}

}
