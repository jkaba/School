package ca.uwo.csd.cs2212.team18;



import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import javax.swing.JLabel;

import java.awt.Font;

import javax.swing.JTextField;
import javax.swing.DropMode;
import javax.swing.SwingConstants;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;

import javax.swing.JTextArea;

import java.awt.Color;

import javax.swing.JTextPane;
/**
 * Creates the first window of the FitCalcUI
 * @author Team18
 *
 */

//UI for the first window that is part of the FitCalc
public class FitCalcUI extends JDialog {

	//Initialize some variables
	private final JPanel contentPanel = new JPanel();
	private JTextField textFieldInput;
	private final JLabel lblNewLabel = new JLabel("The average person with a slightly active life burns roughly 1850 calories");
	private final JPanel panel = new JPanel();
	private final JButton btnCalc = new JButton("Calculate");
	private final JButton btnExit = new JButton("    Exit    ");
	private final JTextArea txtrTheFitcalcWill = new JTextArea();
	Color blueColour = Color.decode("#45C2C5");

	//Method that returns the JDialog
	private JDialog getDialog() {
		return this;
	}
	
	private Data data;
	private boolean testOrNot;
	public FitCalcUI(Data datas, boolean test){
		data = datas;
		testOrNot = test;
		initFitCalcUI();
	}
	
	/**
	 * Create the dialog.
	 */
	public void initFitCalcUI() {
		
		//Visuals of FitCalcUI
		final FitCalc fitCalc = new FitCalc(data,testOrNot);
		
		//Modal
		getDialog().setModal(true);
		getDialog().setMinimumSize(new Dimension(450, 340));
		
		setTitle("FitCalc");
		setResizable(false);
		setBounds(100, 100, 450, 340);
		getContentPane().setBackground(blueColour);
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBackground(null);

		
		contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(new FlowLayout(FlowLayout.CENTER, 200, 30));
		
		{
			JLabel lblEnterHowMany = new JLabel("Enter how many calories you want to burn today:");
			lblEnterHowMany.setFont(new Font("Arial", Font.PLAIN, 18));
			contentPanel.add(lblEnterHowMany);
		}
		{
			lblNewLabel.setFont(new Font("Arial", Font.PLAIN, 10));
			contentPanel.add(lblNewLabel);
		}
		{
			textFieldInput = new JTextField();
			textFieldInput.setHorizontalAlignment(SwingConstants.CENTER);
			textFieldInput.setDropMode(DropMode.INSERT);
			textFieldInput.setFont(new Font("Arial", Font.PLAIN, 18));
			contentPanel.add(textFieldInput);
			textFieldInput.setColumns(15);
		}
		{
			FlowLayout flowLayout = (FlowLayout) panel.getLayout();
			flowLayout.setHgap(20);
			contentPanel.add(panel);
		}
		{
			btnCalc.addActionListener(new ActionListener() {
				public void actionPerformed(ActionEvent arg0) {
					
					//Method that determines if the user input is valid
					String userMessage = fitCalc.checkCaloriesInput(textFieldInput.getText()); 
					
					//If the user input is valid, calculate the according suggestions based off of the inputed calorie goal
					//and the 2nd fitcalc window is opened.
					if(userMessage.equals("")) {
						fitCalc.setCalorieGoal(Integer.parseInt(textFieldInput.getText()));
						getDialog().dispose();						
						fitCalc.calculate(true);						
						FitCalcUI2 fitCalcUI2 = new FitCalcUI2(fitCalc,data,testOrNot);
						fitCalcUI2.setVisible(true);
					}
					
					//Otherwise display an appropriate error message
					else {
	            		JOptionPane.showMessageDialog(getDialog(),userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
	            		textFieldInput.setText("");
	            	}
				}
			});
			panel.add(btnCalc);
		}
		
		//Exit Button
		btnExit.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				//Exit Dialog
				getDialog().dispose();
			}
		});
		panel.add(btnExit);
		
		//Label at the top of the Window
		{
			txtrTheFitcalcWill.setEditable(false);
			txtrTheFitcalcWill.setBackground(new Color(255, 255, 255));
			txtrTheFitcalcWill.setForeground(Color.BLACK);
			txtrTheFitcalcWill.setFont(new Font("Arial", Font.PLAIN, 14));
			getContentPane().add(txtrTheFitcalcWill, BorderLayout.NORTH);
			txtrTheFitcalcWill.setColumns(45);
			txtrTheFitcalcWill.setLineWrap(true);
			txtrTheFitcalcWill.setBackground(null);
			txtrTheFitcalcWill.setWrapStyleWord(true);
			txtrTheFitcalcWill.setText("The FitCalc will check whether you are meeting your inputted calorie goal and will provide suggestions if you are not meeting your goals");
		}
		panel.setBackground(null);
		
		//Display in the center
		getDialog().setLocationRelativeTo(null);
		getDialog().setVisible(false);
	}

}
