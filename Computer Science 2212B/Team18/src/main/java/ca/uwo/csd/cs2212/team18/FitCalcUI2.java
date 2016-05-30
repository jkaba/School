package ca.uwo.csd.cs2212.team18;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.GridBagLayout;

import javax.swing.JLabel;

import java.awt.GridBagConstraints;
import java.awt.Component;

import javax.swing.Box;
import javax.swing.JTextPane;
import javax.swing.JTextField;

import java.awt.Insets;

import javax.swing.JLayeredPane;



import java.awt.Color;
import java.awt.CardLayout;
/**
 * Creates the UI for the second window of FitCalc
 * @author Team18
 *
 */

//UI class for the second window of the FitCalc
public class FitCalcUI2 extends JDialog {
    
    //Initialize some variables
    private final JPanel contentPanel = new JPanel();
    private static JPanel SuggestionsPanelContainer;
    
    Color blueColour = Color.decode("#45C2C5");
    
    JLabel defaultOrCustomActivities;
    JPanel FirstActivity;
    JPanel SecondActivity;
    JPanel ThirdActivity;
    JPanel CardLayoutPanel;
    
    FitCalc fitCalc;
    
    /**
     * Gets activities container
     * @return Gets the JPanel that has the Suggestions Panel
     */
    public static JPanel getActivitiesContainer() {
        return SuggestionsPanelContainer;
    }
    
    /**
     * Gets the 2nd window UI Dialog
     * @return JDialog
     */
    private JDialog getDialog() {
        return this;
    }
    
    /**
     * Constructor that gets the FitCalc object
     * @param fitCalculator	 *
     */
    private Data data;
    private boolean test;
    public FitCalcUI2(FitCalc fitCalculator, Data datas, boolean testOrNot) {
        fitCalc = fitCalculator;
        data = datas;
        test = testOrNot;
        initFitCalcUI2(false);
    }
    
    /**
     * The function that contains all the code to create the 2nd window of the fitCalc
     * @param defaultActivities
     */
    
    public void initFitCalcUI2(boolean defaultActivities) {
        setTitle("FitCalc Results");
        setResizable(false);
        setBounds(100, 100, 984, 450);
        
        //Modal
        getDialog().setModal(true);
        getDialog().setMinimumSize(new Dimension(984, 425));
        
        getContentPane().setLayout(new FlowLayout(FlowLayout.CENTER, 450, 20));
        getContentPane().setBackground(blueColour);
        
        //Label at the top
        JLabel lblExplanation = new JLabel("Mouseover here to know how our App calculates the suggestions");
        lblExplanation.setToolTipText("<html><body> First, if possible, the app gets your three most recent activities from fitbit.com <br>"
                                      + "and gets your corresponding METS (Metabolic Equivalent of Tasks) for a particular activity<br>"
                                      + "Our app then uses the formula (Calories = METS * weight (kg) * time (hours)) to calculate suggestions</body></html>");
        getContentPane().add(lblExplanation);
        contentPanel.setBorder(new EmptyBorder(5, 5, 5, 5));
        contentPanel.setBackground(blueColour);
        getContentPane().add(contentPanel);
        
        //First half of the Window
        GridBagLayout gbl_contentPanel = new GridBagLayout();
        contentPanel.setLayout(gbl_contentPanel);
        
        JLabel lblInput = new JLabel("Inputed Calorie Goal:     ");
        GridBagConstraints gbc_lblInput = new GridBagConstraints();
        gbc_lblInput.anchor = GridBagConstraints.LINE_END;
        gbc_lblInput.gridx = 0;
        gbc_lblInput.gridy = 0;
        contentPanel.add(lblInput, gbc_lblInput);
        
        JTextField txtInput = new JTextField();
        txtInput.setEditable(false);
        GridBagConstraints gbc_txtInput = new GridBagConstraints();
        gbc_txtInput.anchor = GridBagConstraints.LINE_START;
        gbc_txtInput.gridx = 1;
        gbc_txtInput.gridy = 0;
        contentPanel.add(txtInput, gbc_txtInput);
        txtInput.setColumns(10);
        txtInput.setText(Integer.toString(fitCalc.getCalorieGoal()));
        
        JLabel lblBurned = new JLabel("Calories Burned Today:     ");
        GridBagConstraints gbc_lblBurned = new GridBagConstraints();
        gbc_lblBurned.anchor = GridBagConstraints.LINE_END;
        gbc_lblBurned.gridx = 0;
        gbc_lblBurned.gridy = 1;
        contentPanel.add(lblBurned,gbc_lblBurned);
        
        JTextField txtBurned = new JTextField();
        txtBurned.setEditable(false);
        GridBagConstraints gbc_txtBurned = new GridBagConstraints();
        gbc_txtBurned.anchor = GridBagConstraints.LINE_START;
        gbc_txtBurned.gridx = 1;
        gbc_txtBurned.gridy = 1;
        contentPanel.add(txtBurned, gbc_txtBurned);
        txtBurned.setColumns(10);
        txtBurned.setText(Integer.toString(fitCalc.getCaloriesBurned()));
        
        JLabel lblDiff = new JLabel("Difference in Calories:     ");
        lblDiff.setToolTipText("Difference between Calories Burned and Calorie Goal");
        GridBagConstraints gbc_lblDiff = new GridBagConstraints();
        gbc_lblDiff.anchor = GridBagConstraints.LINE_END;
        gbc_lblDiff.gridx = 0;
        gbc_lblDiff.gridy = 2;
        contentPanel.add(lblDiff, gbc_lblDiff);
        
        JTextField txtDiff = new JTextField();
        txtDiff.setEditable(false);
        GridBagConstraints gbc_txtDiff = new GridBagConstraints();
        gbc_txtDiff.anchor = GridBagConstraints.LINE_START;
        gbc_txtDiff.gridx = 1;
        gbc_txtDiff.gridy = 2;
        contentPanel.add(txtDiff, gbc_txtDiff);
        txtDiff.setColumns(10);
        txtDiff.setText(Integer.toString(fitCalc.getCalorieDifference()));
        
        ////////////////////////////////////////////////////
        
        
        //Button Pane for the first Half of the Window
        JPanel buttonPane1 = new JPanel();
        getContentPane().add(buttonPane1);
        buttonPane1.setBackground(null);
        
        //Code when user presses the Default Activities button
        JButton btnNewButton = new JButton("Suggestions with Default Activities");
        btnNewButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                //If the calorie difference is negative, then provide No Suggestions Card
                if (fitCalc.getNegativeDifference() == true) {
                    CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
                    cardLayout.show(CardLayoutPanel, "NOSUGGESTIONS");
                    defaultOrCustomActivities.setText("No Activities to show");
                }
                //Else display the default suggestions
                else {
                    defaultOrCustomActivities.setText("Activities listed are default activities");
                    
                    SuggestionsPanelContainer.remove(FirstActivity);
                    SuggestionsPanelContainer.remove(SecondActivity);
                    SuggestionsPanelContainer.remove(ThirdActivity);
                    
                    FirstActivity = FitCalcDisplayActivities.createActivity(fitCalc, true, 0);
                    SecondActivity = FitCalcDisplayActivities.createActivity(fitCalc, true, 1);
                    ThirdActivity = FitCalcDisplayActivities.createActivity(fitCalc, true, 2);
                    
                    SuggestionsPanelContainer.add(FirstActivity);
                    SuggestionsPanelContainer.add(SecondActivity);
                    SuggestionsPanelContainer.add(ThirdActivity);
                    
                    CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
                    cardLayout.show(CardLayoutPanel, "SUGGESTIONS");
                    
                    CardLayoutPanel.repaint();
                    SwingUtilities.updateComponentTreeUI(CardLayoutPanel);
                }
            }
        });
        
        
        btnNewButton.setToolTipText("App will use default activities and values to generate suggestions");
        buttonPane1.add(btnNewButton);
        
        JButton btnNewButton_1 = new JButton("Suggestion with your three most recent Activities");
        btnNewButton_1.setToolTipText("App will use your three most recent activities your fitbit has recorded to generate suggestions");
        btnNewButton_1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                //If the calorie difference is negative, then provide No Suggestions Card
                String success = fitCalc.calculate(false);
                if (fitCalc.getNegativeDifference() == true) {
                    CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
                    cardLayout.show(CardLayoutPanel, "NOSUGGESTIONS");
                    defaultOrCustomActivities.setText("No Activities to show");
                    
                    //If Unable to get fitbit data, provide an error message
                } else if (!success.equals("")) {
                    JOptionPane.showMessageDialog(getDialog(),success,"Unable To Access",JOptionPane.WARNING_MESSAGE);
                }
                
                //Else display the custom suggestions
                else {
                    defaultOrCustomActivities.setText("Activities listed are from Fitbit");
                    
                    SuggestionsPanelContainer.remove(FirstActivity);
                    SuggestionsPanelContainer.remove(SecondActivity);
                    SuggestionsPanelContainer.remove(ThirdActivity);
                    
                    FirstActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 0);
                    SecondActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 1);
                    ThirdActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 2);
                    
                    SuggestionsPanelContainer.add(FirstActivity);
                    SuggestionsPanelContainer.add(SecondActivity);
                    SuggestionsPanelContainer.add(ThirdActivity);
                    
                    CardLayoutPanel.repaint();
                    SwingUtilities.updateComponentTreeUI(CardLayoutPanel);
                }
            }
        });
        buttonPane1.add(btnNewButton_1);
        
        //////////////////////////////////////////////////////////////////////////////
        
        defaultOrCustomActivities = new JLabel("Activities listed are from Fitbit");
        getContentPane().add(defaultOrCustomActivities);
        
        //CardLayout for the second Half of the Window
        //Create the First Card with 6*3 = 18 components
        CardLayoutPanel = new JPanel();
        getContentPane().add(CardLayoutPanel);
        CardLayoutPanel.setLayout(new CardLayout(0, 0));
        CardLayoutPanel.setBackground(blueColour);
        
        SuggestionsPanelContainer = new JPanel();
        SuggestionsPanelContainer.setBackground(null);
        CardLayoutPanel.add(SuggestionsPanelContainer, "SUGGESTIONS");
        SuggestionsPanelContainer.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
        
        //Creates the JPanels that are to be put into the SuggestionsPanelContainer
        FirstActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 0);
        SecondActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 1);
        ThirdActivity = FitCalcDisplayActivities.createActivity(fitCalc, false, 2);
        
        //Second Card for when user burned more calories than the goal
        JPanel NoSuggestionsPanel = new JPanel();
        NoSuggestionsPanel.setBackground(blueColour);
        CardLayoutPanel.add(NoSuggestionsPanel, "NOSUGGESTIONS");
        
        JLabel NoSuggestionslbl = new JLabel("<html><body>There are no suggestions to give because you have met your calorie goal!<br> "
                                             + "Give yourself a pat on the back!</body></html>");
        NoSuggestionsPanel.add(NoSuggestionslbl);
        
        //Third Card for when app cannot access the fitbit API
        JPanel NoAccess = new JPanel();
        NoAccess.setBackground(blueColour);
        CardLayoutPanel.add(NoAccess, "NOACCESS");
        
        JLabel NoAccesslbl = new JLabel("<html><body>The app is unable to get your Fitbit activities.<br> "
                                        + "Either reload the fitCalc or press the the default activities button</body></html>");
        NoAccess.add(NoAccesslbl);
        
        ///////////////////////////////////////////////////////////////////////////////////////
        
        String success = fitCalc.calculate(false);
        //If Calorie Difference is negative, only show the NOSUGGESTIONS card 
        if (fitCalc.getNegativeDifference() == true) {
            CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
            cardLayout.show(CardLayoutPanel, "NOSUGGESTIONS");
            defaultOrCustomActivities.setText("No Activities to show");
        } 			
        else if (!success.equals("")) {
            CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
            cardLayout.show(CardLayoutPanel, "NOACCESS");
            defaultOrCustomActivities.setText("No Activities to show since app cannot access fitbit activities");
        }
        
        else {
            SuggestionsPanelContainer.add(FirstActivity);
            SuggestionsPanelContainer.add(SecondActivity);
            SuggestionsPanelContainer.add(ThirdActivity);
            CardLayout cardLayout = (CardLayout) CardLayoutPanel.getLayout();
            cardLayout.show(CardLayoutPanel, "SUGGESTIONS");
        }
        
        ////////////////////////////////////////////////
        
        //Button Pane that is at the bottom		
        JPanel buttonPane2 = new JPanel();
        buttonPane2.setBackground(null);
        FlowLayout fl_buttonPane2 = new FlowLayout(FlowLayout.CENTER);
        fl_buttonPane2.setHgap(50);
        buttonPane2.setLayout(fl_buttonPane2);
        getContentPane().add(buttonPane2);
        
        //Back Button
        JButton Back = new JButton("Go Back");
        Back.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                getDialog().dispose();
                FitCalcUI fitCalcUI = new FitCalcUI(data, test);
                fitCalcUI.setVisible(true);
            }
        });
        buttonPane2.add(Back);		
        
        //Exit Button
        JButton Exit = new JButton("Exit");
        Exit.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                getDialog().dispose();
            }
        });				
        buttonPane2.add(Exit);		
        
        //Display in the center
        getDialog().setLocationRelativeTo(null);
        getDialog().setVisible(false);
    }
}
