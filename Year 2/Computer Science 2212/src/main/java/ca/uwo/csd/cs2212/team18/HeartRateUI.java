package ca.uwo.csd.cs2212.team18;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLayeredPane;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagLayout;
import java.awt.GridBagConstraints;

import javax.swing.JLabel;
import javax.swing.JTextPane;

import java.awt.Insets;

import javax.swing.JTextField;

import java.awt.Color;

import javax.swing.SwingConstants;

/**
 * Creates the HeartRateUI
 * @author Team18
 *
 */

public class HeartRateUI extends JDialog {
	Color blueColour = Color.decode("#45C2C5");
	private final JPanel contentPanel = new JPanel();
	private JTextField textField;
	private JTextField textField_1;
	private JTextField textField_2;
	private JTextField textField_3;
	private JTextField textField_4;

	/** 
	 * Launch the application.
	 */
	
	private Data data;
	private APIData api;
	private Boolean test;
	private BaseDashBoard basedashboard;
	
	/**
	 * Public constructor of HeartRateUI
	 * @param data1
	 * @param testOrNot
	 */
	public HeartRateUI(Data data1, boolean testOrNot) {
		data = data1;
		test = testOrNot;
		initHeartRateUI();
	}

	/**
	 * Method enables the JDialog to be referenced inside ActionListeners
	 * @return the JDialog
	 */
	private JDialog getDialog() {
		return this;
	}
	/**
	 * Create the dialog.
	 */
	public void initHeartRateUI() {
		setTitle("Heart Rate Zone");
		setBounds(100, 100, 450, 355);
		
		//Modal
		getDialog().setModal(true);
		getDialog().setMinimumSize(new Dimension(450, 355));
		getDialog().setResizable(false);
		
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(blueColour);
		
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(new BorderLayout(0, 0));
		
		JLayeredPane layeredPane = new JLayeredPane();
		contentPanel.add(layeredPane);
		layeredPane.setLayout(new FlowLayout(FlowLayout.CENTER, 500, 20));

		JLabel jl = new JLabel("Mouseover the heart rate zones names' to view descriptions");  
		layeredPane.add(jl);

		JLayeredPane layeredPane_2 = new JLayeredPane();
		layeredPane.add(layeredPane_2);
		GridBagLayout gbl_layeredPane_2 = new GridBagLayout();
		gbl_layeredPane_2.columnWidths = new int[] {80, 80};
		gbl_layeredPane_2.rowHeights = new int[] {20};
		gbl_layeredPane_2.columnWeights = new double[]{1.0, 0.0};
		gbl_layeredPane_2.rowWeights = new double[]{0.0};
		layeredPane_2.setLayout(gbl_layeredPane_2);
		
		JLabel lblNewLabel_3 = new JLabel("Resting Heart Rate");
		lblNewLabel_3.setToolTipText("");
		GridBagConstraints gbc_lblNewLabel_3 = new GridBagConstraints();
		gbc_lblNewLabel_3.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_3.gridx = 0;
		gbc_lblNewLabel_3.gridy = 0;
		layeredPane_2.add(lblNewLabel_3, gbc_lblNewLabel_3);
		
		textField = new JTextField();
		textField.setToolTipText("Beats per Minutes");
		textField.setBackground(Color.WHITE);
		textField.setEditable(false);
		GridBagConstraints gbc_textField = new GridBagConstraints();
		gbc_textField.insets = new Insets(0, 0, 5, 0);
		gbc_textField.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField.gridx = 1;
		gbc_textField.gridy = 0;
		layeredPane_2.add(textField, gbc_textField);
		textField.setColumns(10);
		
		JLabel lblNewLabel_4 = new JLabel("Minutes in Heart Rate Zone");
		layeredPane.add(lblNewLabel_4);
		
		JLayeredPane layeredPane_1 = new JLayeredPane();
		layeredPane.add(layeredPane_1);
		GridBagLayout gbl_layeredPane_1 = new GridBagLayout();
		gbl_layeredPane_1.columnWidths = new int[] {0, 80, 80};
		gbl_layeredPane_1.rowHeights = new int[] {20, 20, 20, 20};
		gbl_layeredPane_1.columnWeights = new double[]{0.0, 0.0, 1.0};
		gbl_layeredPane_1.rowWeights = new double[]{0.0, 0.0, 0.0, 0.0};
		layeredPane_1.setLayout(gbl_layeredPane_1);
		
		JLabel lblNewLabel = new JLabel("Out of Range");
		lblNewLabel.setToolTipText("<html><body>When you're out of zone, which means your heart rate <br>"
				+ "is below 50% of maximum, your heart rate may still be <br> elevated but not "
				+ "enough to be considered exercise.</body></html>");
		GridBagConstraints gbc_lblNewLabel = new GridBagConstraints();
		gbc_lblNewLabel.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel.gridx = 1;
		gbc_lblNewLabel.gridy = 0;
		layeredPane_1.add(lblNewLabel, gbc_lblNewLabel);
		
		textField_1 = new JTextField();
		textField_1.setBackground(Color.WHITE);
		textField_1.setEditable(false);

		GridBagConstraints gbc_textField_1 = new GridBagConstraints();
		gbc_textField_1.insets = new Insets(0, 0, 5, 0);
		gbc_textField_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_1.gridx = 2;
		gbc_textField_1.gridy = 0;
		layeredPane_1.add(textField_1, gbc_textField_1);
		textField_1.setColumns(10);
		
		JLabel lblNewLabel_1 = new JLabel("Fat Burn Zone");
		lblNewLabel_1.setToolTipText("<html><body>Fat burn zone, which means your heart rate is 50 to 69% "
				+ "of maximum, <br> is the low-to-medium intensity exercise zone and may be a good <br>"
				+ " place to start for those new to exercise. It's called the fat burn zone <br>"
				+ "because a higher percentage of calories are burned from fat, <br>but the total "
				+ "calorie burn rate is lower.</body></html>");
		GridBagConstraints gbc_lblNewLabel_1 = new GridBagConstraints();
		gbc_lblNewLabel_1.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel_1.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_1.gridx = 1;
		gbc_lblNewLabel_1.gridy = 1;
		layeredPane_1.add(lblNewLabel_1, gbc_lblNewLabel_1);
		
		textField_2 = new JTextField();
		textField_2.setBackground(Color.WHITE);
		textField_2.setEditable(false);
		GridBagConstraints gbc_textField_2 = new GridBagConstraints();
		gbc_textField_2.insets = new Insets(0, 0, 5, 0);
		gbc_textField_2.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_2.gridx = 2;
		gbc_textField_2.gridy = 1;
		layeredPane_1.add(textField_2, gbc_textField_2);
		textField_2.setColumns(10);
		
		JLabel lblNewLabel_2 = new JLabel("Cardio Zone");
		lblNewLabel_2.setToolTipText("<html><body>Cardio zone, which means your heart rate is 70 to 84% of maximum, "
				+ "is the <br>medium-to-high intensity exercise zone. In this zone, you're pushing"
				+ " yourself <br>but not straining. For most people, this is the exercise zone to target. </body></html>");
		GridBagConstraints gbc_lblNewLabel_2 = new GridBagConstraints();
		gbc_lblNewLabel_2.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel_2.insets = new Insets(0, 0, 5, 5);
		gbc_lblNewLabel_2.gridx = 1;
		gbc_lblNewLabel_2.gridy = 2;
		layeredPane_1.add(lblNewLabel_2, gbc_lblNewLabel_2);
		
		textField_3 = new JTextField();
		textField_3.setBackground(Color.WHITE);
		textField_3.setEditable(false);
		GridBagConstraints gbc_textField_3 = new GridBagConstraints();
		gbc_textField_3.insets = new Insets(0, 0, 5, 0);
		gbc_textField_3.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_3.gridx = 2;
		gbc_textField_3.gridy = 2;
		layeredPane_1.add(textField_3, gbc_textField_3);
		textField_3.setColumns(10);
		
		JLabel lblNewLabel_5 = new JLabel("Peak Zone");
		lblNewLabel_5.setToolTipText("<html><body>Peak zone, which means your heart rate is greater than 85% of <br>"
				+ "maximum, is the high-intensity exercise zone. The peak zone is <br>for short "
				+ "intense sessions that improve performance and speed. </body></html>");
		GridBagConstraints gbc_lblNewLabel_5 = new GridBagConstraints();
		gbc_lblNewLabel_5.fill = GridBagConstraints.HORIZONTAL;
		gbc_lblNewLabel_5.insets = new Insets(0, 0, 0, 5);
		gbc_lblNewLabel_5.gridx = 1;
		gbc_lblNewLabel_5.gridy = 3;
		layeredPane_1.add(lblNewLabel_5, gbc_lblNewLabel_5);
		
		textField_4 = new JTextField();
		textField_4.setBackground(Color.WHITE);
		textField_4.setEditable(false);
		GridBagConstraints gbc_textField_4 = new GridBagConstraints();
		gbc_textField_4.fill = GridBagConstraints.HORIZONTAL;
		gbc_textField_4.gridx = 2;
		gbc_textField_4.gridy = 3;
		layeredPane_1.add(textField_4, gbc_textField_4);
		textField_4.setColumns(10);
		
		
		//Sets the text based on whether or not in test mode
		if (test == true) {
			textField.setText(Integer.toString(data.getRestingHeartRate().getValue()));
			textField_1.setText(Integer.toString(data.getOutOfRange().getValue()) + " mins");
			textField_2.setText(Integer.toString(data.getFatBurn().getValue()) + " mins");
			textField_3.setText(Integer.toString(data.getCardio().getValue()) + " mins");
			textField_4.setText(Integer.toString(data.getPeak().getValue()) + " mins");
		}
		else {
			api = (APIData) data; 			
			if (api.isErrorConnection() == true) {
				JOptionPane.showMessageDialog(getDialog(),"Could not establish connection with FitBit Server! Try again later","Connection warning",JOptionPane.WARNING_MESSAGE);
			}
			else {
				textField.setText(Integer.toString(api.getRestingHeartRate().getValue()));
				textField_1.setText(Integer.toString(api.getOutOfRange().getValue()) + " mins");
				textField_2.setText(Integer.toString(api.getFatBurn().getValue()) + " mins");
				textField_3.setText(Integer.toString(api.getCardio().getValue()) + " mins");
				textField_4.setText(Integer.toString(api.getPeak().getValue()) + " mins");
			}
		}
		
		JButton btnNewButton = new JButton("Exit");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				getDialog().dispose();
			}
		});
		layeredPane.add(btnNewButton);
		
		//Display in the center
		getDialog().setLocationRelativeTo(null);
		getDialog().setVisible(false);
	}
}
