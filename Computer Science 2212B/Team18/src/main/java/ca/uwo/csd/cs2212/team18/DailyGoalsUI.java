package ca.uwo.csd.cs2212.team18;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dialog;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.border.EmptyBorder;
import javax.swing.JLayeredPane;
import javax.swing.JScrollBar;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JList;
import javax.swing.JOptionPane;
import javax.swing.JSlider;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JDialog;
import javax.swing.AbstractListModel;
import javax.swing.ButtonGroup;
import javax.swing.DefaultComboBoxModel;

import java.awt.ScrollPane;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.LinkedList;
import java.util.Stack;
import java.awt.Point;

import javax.swing.SwingConstants;
import javax.swing.ScrollPaneConstants;

/**
 * Class that displays the contents of daily goals component 
 * including creating a goal, switching the date, and removing a goal
 * @author Team 18
 *
 */
public class DailyGoalsUI extends JDialog {
	//Private variables 

	/**
	 * JPanel that contains the contents of the program
	 */
	private JPanel contentPane;

	/**
	 * JPanel that contains the contents of the window 
	 */
	private final JPanel contentPanel = new JPanel();

	/**
	 * JtextField that displays goals information
	 */
	private JTextField txtReps;

	/**
	 * String to change the date to user's preference 
	 */
	private String newDate;

	/**
	 * Year value of the date
	 */
	private String year;

	/**
	 * Month value of the date
	 */
	private String month;

	/**
	 * Day value of the date
	 */
	private String day;

	/**
	 * Fake year value of the date (Used for comparison)
	 */
	private String fYear;

	/**
	 * Fake month value of the date (Used for comparison)
	 */
	private String fMonth;

	/**
	 * Fake day value of the date (Used for comparison)
	 */
	private String fDay;


	//static Data apiData;
	static APIData notTest;
	
	private JDialog itself = this;

	/**
	 * Constructor to create the UI for Daily Goals
	 * @param dat Data to be used
	 * @param t Boolean to determine what type of data to use
	 */
	public DailyGoalsUI(Data data, Boolean t){
		initDailyGoalsUI(data, t);
	}

	/**
	 * init method that creates the window 
	 * User has access to several features 
	 * Creating a goal, switching the date, and removing a goal 
	 * the user is also able to view the goals they set on a particular day
	 * @param data The Data to be used 
	 * @param test Boolean used to determine whether to use test data
	 */
	public void initDailyGoalsUI(final Data data, final Boolean test){
		final Data dat = this.test(data, test);
		setTitle("Daily Goals");
		if(test == false){
			notTest = (APIData) dat;
		}

		final GoalList goalll = DailyGoals.load();

		this.addWindowListener(new java.awt.event.WindowAdapter() {

			public void windowClosing(java.awt.event.WindowEvent wind) {
				DailyGoals.save(goalll);
				if(!goalll.valid(year, month, day)){
					JOptionPane.showMessageDialog(wind.getWindow(),"You need at least 4 goals","Input warning",JOptionPane.WARNING_MESSAGE);
					setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
				}
				else{
					setDefaultCloseOperation(DISPOSE_ON_CLOSE);
				}
			}
		});
		this.setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
		
		//Modal
		getDialog().setModal(true);
		getDialog().setMinimumSize(new Dimension(419,235));
		getDialog().setResizable(false);
		

		setBounds(100, 100, 419, 235);
		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		contentPane.setBackground(new Color(69, 194, 197));
		contentPane.setLayout(new BorderLayout(0, 0));
		setContentPane(contentPane);

		JLayeredPane layeredPane = new JLayeredPane();
		contentPane.add(layeredPane, BorderLayout.CENTER);
		layeredPane.setLayout(null);

		JLabel label = new JLabel();
		label.setBounds(0, 0, 403, 203);
		layeredPane.add(label);
		String date = new SimpleDateFormat("yyyy-MM-dd").format(new Date());

		year = new SimpleDateFormat("yyyy").format(new Date());
		month = new SimpleDateFormat("MM").format(new Date());
		day = new SimpleDateFormat("dd").format(new Date());
		final JLabel l = new JLabel(date);
		l.setBounds(200, 10, 146, 16);

		final JTextArea text = new JTextArea();
		text.setBounds(2, 2, 342, 96);
		text.setWrapStyleWord(true);
		text.enable(false); 
		layeredPane.add(text);

		if(test == true){
			text.setText(goalll.toString(year, month, day,dat));
		}

		else{
			text.setText(goalll.toString(year, month, day, notTest));
		}

		text.repaint();
		JLabel lblGoalsFor = new JLabel("Goal(s) for: ");
		lblGoalsFor.setBounds(124, 10, 87, 16);
		layeredPane.add(lblGoalsFor);
		layeredPane.add(l);

		JButton btnCreateAGoal = new JButton("Create a goal");
		btnCreateAGoal.setBounds(25, 155, 117, 29);
		layeredPane.add(btnCreateAGoal);
		btnCreateAGoal.setVisible(true);
		
		JButton btnExit = new JButton("Exit");
		btnExit.setBounds(145,180,117,29);
		layeredPane.add(btnExit);
		btnCreateAGoal.setVisible(true);
		btnExit.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent evt){
                DailyGoals.save(goalll);
                if(!goalll.valid(year, month, day)){
                    JOptionPane.showMessageDialog(itself,"You need at least 4 goals","Input warning",JOptionPane.WARNING_MESSAGE);
                    
                }
                else{
                    itself.dispose();
                }
			}
		});
		
		//Display in the center
		getDialog().setLocationRelativeTo(null);

		btnCreateAGoal.addActionListener(new ActionListener(){
	
			public void actionPerformed(ActionEvent evt){

				final JDialog goals = new JDialog();
				
				//Modal
				goals.setModal(true);
				goals.setMinimumSize(new Dimension(350, 286));
				
				
				//goals.setVisible(true);
				goals.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
				goals.setBounds(100, 100, 350, 286);

				JPanel contentPanel = new JPanel();
				getContentPane().setLayout(new BorderLayout());
				contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
				contentPanel.setBackground(new Color(69, 194, 197));
				contentPanel.setVisible(true);

				goals.getContentPane().add(contentPanel, BorderLayout.CENTER);
				contentPanel.setLayout(null);

				{
					JLabel lblSetTheGoals = new JLabel("Select a goal you hope to achieve");
					lblSetTheGoals.setBounds(70, 24, 214, 16);
					contentPanel.add(lblSetTheGoals);
					lblSetTheGoals.setAlignmentY(20);
				}

				JLayeredPane layeredPane_1 = new JLayeredPane();
				layeredPane_1.setBounds(6, 52, 152, 180);
				contentPanel.add(layeredPane_1);

				{
					ButtonGroup group = new ButtonGroup();
					layeredPane_1.setLayout(new FlowLayout(FlowLayout.LEFT, 5, 8));
					final JRadioButton btn1 = new JRadioButton("Steps");
					layeredPane_1.add(btn1);
					group.add(btn1);

					final JRadioButton btn3 = new JRadioButton("Distance");
					layeredPane_1.add(btn3);
					group.add(btn3);

					final JRadioButton btn4 = new JRadioButton("Calories");
					layeredPane_1.add(btn4);
					group.add(btn4);

					final JRadioButton btn5 = new JRadioButton("Active minutes");
					layeredPane_1.add(btn5);
					group.add(btn5);

					final JRadioButton btn2 = new JRadioButton("Floors");
					layeredPane_1.add(btn2);
					group.add(btn2);

					{
						JLayeredPane layeredPane = new JLayeredPane();
						layeredPane.setBounds(153, 52, 201, 180);
						contentPanel.add(layeredPane);
						layeredPane.setLayout(null);

						txtReps = new JTextField(20);
						txtReps.setHorizontalAlignment(SwingConstants.LEFT);
						txtReps.setBounds(35, 70, 130, 26);
						layeredPane.add(txtReps);

						JLabel lblNewLabel = new JLabel("Enter a value");
						lblNewLabel.setBounds(59, 42, 90, 16);
						layeredPane.add(lblNewLabel);
						DailyGoals.checkMeasureInput(txtReps.getText());
					}

					{
						JLayeredPane layeredPane = new JLayeredPane();
						goals.getContentPane().add(layeredPane, BorderLayout.NORTH);
					}

					{
						JPanel buttonPane = new JPanel();
						buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
						goals.getContentPane().add(buttonPane, BorderLayout.SOUTH);
						buttonPane.setBackground((new Color(69, 194, 197)));
						buttonPane.setVisible(true);

						{
							JButton okButton = new JButton("OK");
							okButton.setBounds(62, 112, 68, 29);
							okButton.setActionCommand("OK");
							buttonPane.add(okButton);

							okButton.setVisible(true);
							okButton.addActionListener(new ActionListener(){
								final Goal goal = new Goal("", 0, year, month, day);

								public void actionPerformed(ActionEvent evt){
									String userMessage = DailyGoals.checkMeasureInput(txtReps.getText());

									if(!btn1.isSelected() && !btn2.isSelected() && !btn3.isSelected() && !btn4.isSelected() && !btn5.isSelected()){
										JOptionPane.showMessageDialog(goals,"Please select a type of goal","Input warning",JOptionPane.WARNING_MESSAGE);
									}

									else{

										if(btn1.isSelected()){
											goal.setType("Steps");
										}

										if(btn2.isSelected()){
											goal.setType("Floors");
										}

										if(btn3.isSelected()){
											goal.setType("Distance");
										}

										if(btn4.isSelected()){
											goal.setType("Calories");
										}

										if(btn5.isSelected()){
											goal.setType("Active minutes");
										}

										if(!userMessage.equals("")){
											JOptionPane.showMessageDialog(goals, userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
										}

										else{
											if(txtReps.getText().length() > 9){
												JOptionPane.showMessageDialog(goals, "Enter a smaller measure","Input warning",JOptionPane.WARNING_MESSAGE);
											}
											else{
												int m = Integer.parseInt(txtReps.getText());
												goal.setMeasure(m);
												userMessage = goalll.add(goal);


												if(test == true){
													text.setText(goalll.toString(year,month,day, dat));
												}

												else{
													text.setText(goalll.toString(year, month, day, notTest));
												}

												text.revalidate();
												text.repaint();

												if (userMessage.equals("")) {

													if(goalll.valid(year, month, day)){
														setDefaultCloseOperation(DISPOSE_ON_CLOSE);
													}

													else{
														setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
													}

													goals.dispose();
												}

												else {
													JOptionPane.showMessageDialog(goals,userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
												}
											}
										}
									}
								}
							});
						}

						{
							JButton cancelButton = new JButton("Cancel");
							cancelButton.setActionCommand("Cancel");
							buttonPane.add(cancelButton);
							cancelButton.setVisible(true);

							cancelButton.addActionListener(new ActionListener(){


								public void actionPerformed(ActionEvent evt){

									if(goalll.valid(year, month, day)){
										setDefaultCloseOperation(DISPOSE_ON_CLOSE);
									}

									else{
										setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
									}

									goals.dispose();
								}
							});

						}
					}
				}
				
				//Display in the center
				goals.setLocationRelativeTo(null);
				goals.setVisible(true);
			}

			private Object dispose() {
				return null;
			}});

		JButton btnSwitchDate = new JButton("Switch Date");
		btnSwitchDate.setBounds(145, 155, 117, 29);
		layeredPane.add(btnSwitchDate);
		btnSwitchDate.addActionListener(new ActionListener(){

			public void actionPerformed(ActionEvent evt){
				final JDialog goals2 = new JDialog();
				//goals2.setVisible(true);
				setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
				goals2.setBounds(100, 100, 442, 237);
				
				//Modal
				goals2.setModal(true);
				goals2.setMinimumSize(new Dimension(442, 237));
				goals2.setResizable(false);
				
				//Display in the center
				goals2.setLocationRelativeTo(null);

				JPanel contentPanel = new JPanel();
				getContentPane().setLayout(new BorderLayout());
				contentPanel.setVisible(true);
				contentPanel.setBackground(new Color(69, 194, 197));
				contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));

				goals2.getContentPane().add(contentPanel, BorderLayout.CENTER);
				contentPanel.setLayout(null);
				JLayeredPane layeredPane1 = new JLayeredPane();
				layeredPane1.setBounds(0, 11, 444, 32);
				contentPanel.add(layeredPane1);
				layeredPane1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

				JLabel lblNewLabel = new JLabel("Please enter the date in the format YYYY/MM/DD");
				layeredPane1.add(lblNewLabel);
				lblNewLabel.setVisible(true);

				JLayeredPane layeredPane_11 = new JLayeredPane();
				layeredPane_11.setBounds(0, 72, 444, 32);
				contentPanel.add(layeredPane_11);
				layeredPane_11.setLayout(new FlowLayout(FlowLayout.CENTER, 90, 5));

				JLabel lblNewLabel_1 = new JLabel("Year");
				layeredPane_11.add(lblNewLabel_1);

				JLabel lblNewLabel_2 = new JLabel("Month");
				layeredPane_11.add(lblNewLabel_2);

				JLabel lblNewLabel_3 = new JLabel("Day");
				layeredPane_11.add(lblNewLabel_3);

				JLayeredPane layeredPane_2 = new JLayeredPane();
				layeredPane_2.setBounds(0, 99, 444, 32);
				contentPanel.add(layeredPane_2);
				layeredPane_2.setLayout(new FlowLayout(FlowLayout.CENTER, 35, 5));

				final JTextField textField = new JTextField();
				layeredPane_2.add(textField);
				textField.setColumns(7);

				final JTextField textField_1 = new JTextField();
				layeredPane_2.add(textField_1);
				textField_1.setColumns(7);

				final JTextField textField_2 = new JTextField();
				layeredPane_2.add(textField_2);
				textField_2.setColumns(7);

				final JLayeredPane layeredPane_3 = new JLayeredPane();
				layeredPane_3.setBounds(0, 160, 444, 39);
				contentPanel.add(layeredPane_3);
				layeredPane_3.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));

				JButton btnOk = new JButton("OK");
				layeredPane_3.add(btnOk);
				
				JButton exitDate = new JButton("Exit");
				exitDate.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent event) {
						goals2.dispose();
					}
				});
				layeredPane_3.add(exitDate);

				btnOk.setVisible(true);
				btnOk.addActionListener(new ActionListener(){


					public void actionPerformed(ActionEvent event) {

						fYear = textField.getText();
						fMonth = textField_1.getText();
						fDay = textField_2.getText();
						newDate = fYear + "-" + fMonth + "-" + fDay;

						if(newDate.contentEquals("--")){

						}

						else{
							year = fYear;
							month = fMonth;
							day = fDay;
							l.setText(newDate);
							l.repaint();
							if(test == false){

								notTest.refresh(newDate);

								if(notTest.isErrorConnection() == true){
									JOptionPane.showMessageDialog(goals2,"Could not establish connection with FitBit Server. Try again later.","Connection warning",JOptionPane.WARNING_MESSAGE);
								}

							}
						}

						String userMessage = DailyGoals.checkDateInput(textField.getText(),textField_1.getText(),textField_2.getText());

						if (userMessage == "") {

							if(goalll.valid(year, month, day)){
								setDefaultCloseOperation(DISPOSE_ON_CLOSE);
							}

							else{
								setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
							}

							goals2.dispose();
						}

						else {

							JOptionPane.showMessageDialog(goals2,userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
						}

						if(test == true){
							text.setText(goalll.toString(year,month,day,dat));
						}

						else{
							text.setText(goalll.toString(year,month,day,notTest));
						}

						text.revalidate();
						text.repaint();
					}
				});
				
				//set visible
				goals2.setVisible(true);
			}
		});

		JButton btnRemoveGoal = new JButton("Remove Goal");
		btnRemoveGoal.setBounds(266, 155, 117, 29);
		layeredPane.add(btnRemoveGoal);

		btnRemoveGoal.addActionListener(new ActionListener(){


			public void actionPerformed(ActionEvent evt){
				final JDialog goals3 = new JDialog();
				//goals3.setVisible(true);
				goals3.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
				goals3.setBounds(100, 100, 199, 179);
				
				//Modal
				goals3.setModal(true);
				goals3.setMinimumSize(new Dimension(199, 179));
				goals3.setResizable(false);
				
				//Display in the center
				goals3.setLocationRelativeTo(null);

				JPanel contentPanel = new JPanel();
				getContentPane().setLayout(new BorderLayout());
				contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
				contentPanel.setBackground(new Color(69, 194, 197));
				contentPanel.setVisible(true);

				goals3.getContentPane().add(contentPanel, BorderLayout.CENTER);
				contentPanel.setLayout(null);

				JLabel lblSelectAGoal = new JLabel("Select a goal to remove");
				lblSelectAGoal.setVerticalAlignment(SwingConstants.TOP);
				lblSelectAGoal.setHorizontalAlignment(SwingConstants.RIGHT);
				lblSelectAGoal.setBounds(18, 18, 154, 16);
				contentPanel.add(lblSelectAGoal);
				final JComboBox comboBox = new JComboBox();
				comboBox.setModel(new DefaultComboBoxModel(new String[] {"Total distance", "Floors", "Steps", "Calories burned", "Active Minutes"}));
				comboBox.setBounds(18, 62, 154, 27);
				contentPanel.add(comboBox);
				{
					JPanel buttonPane = new JPanel();
					buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
					goals3.getContentPane().add(buttonPane, BorderLayout.SOUTH);
					buttonPane.setBackground(new Color(69, 194, 197));
					buttonPane.setVisible(true);
					buttonPane.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
					{
						JButton okButton = new JButton("OK");
						okButton.setActionCommand("OK");

						buttonPane.add(okButton);
						okButton.setVisible(true);
						okButton.addActionListener(new ActionListener(){

							public void actionPerformed(ActionEvent evt){


								String userMessage = "";
								if(comboBox.getSelectedItem().equals("Steps")){
									userMessage = goalll.remove("Steps",year,month,day);
								}

								else if(comboBox.getSelectedItem().equals("Floors")){
									userMessage = goalll.remove("Floors",year,month,day);
								}

								else if(comboBox.getSelectedItem().equals("Calories burned")){
									userMessage = goalll.remove("Calories",year,month,day);
								}

								else if(comboBox.getSelectedItem().equals("Active Minutes")){
									userMessage = goalll.remove("Active minutes",year,month,day);
								}

								else if(comboBox.getSelectedItem().equals("Total distance")){
									userMessage = goalll.remove("Distance",year,month,day);
								}

								if(!userMessage.equals("")){
									JOptionPane.showMessageDialog(goals3,userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
								}

								if(test == true){
									text.setText(goalll.toString(year,month,day,dat));
								}

								else{
									text.setText(goalll.toString(year, month, day, notTest));
								}
								text.revalidate();
								text.repaint();

								if(goalll.valid(year, month, day)){
									setDefaultCloseOperation(DISPOSE_ON_CLOSE);
								}

								else{
									setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);
								}

								goals3.dispose();
							}
						});
					}

					{
						JButton cancelButton = new JButton("Cancel");
						cancelButton.setActionCommand("Cancel");
						buttonPane.add(cancelButton);
						cancelButton.setVisible(true);
						cancelButton.addActionListener(new ActionListener(){


							public void actionPerformed(ActionEvent evt){

								if(goalll.valid(year, month, day)){
									setDefaultCloseOperation(DISPOSE_ON_CLOSE);
								}

								else{
									setDefaultCloseOperation(DO_NOTHING_ON_CLOSE);		
								}

								goals3.dispose();
							}
						});
					}
				}
				
				//set visible
				goals3.setVisible(true);
			}});
		JScrollPane jScroll = new JScrollPane(text);
		jScroll.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_NEVER);
		jScroll.setBounds(10, 40, 388, 97);
		layeredPane.add(jScroll);
		jScroll.setPreferredSize(new Dimension(60,60));

	}

	private Dialog getDialog() {
		// TODO Auto-generated method stub
		return this;
	}

	/**
	 * Test method, used to determine if the data is API Data or Test Data
	 * @param dat The Data
	 * @param test Boolean value to determine what type of data to use
	 * @return If test is true, then TestData; otherwise, APIData
	 */

	private Data test(Data dat, Boolean test){

		// If test is true then use TestData
		if(test == true){
			dat = new TestData();
		}

		// Else use API Data
		else{
			dat = (APIData) dat;
		}

		return dat;
	}
}
