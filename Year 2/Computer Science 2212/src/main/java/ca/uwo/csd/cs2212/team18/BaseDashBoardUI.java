package ca.uwo.csd.cs2212.team18;

//Import
import java.util.ArrayList;
import javax.swing.JFrame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.JLayeredPane;
import javax.swing.JPanel;
import javax.swing.JLabel;
import javax.swing.JTextField;
import javax.swing.SwingConstants;
import javax.swing.SwingUtilities;
import javax.swing.border.EmptyBorder;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.BorderFactory;
import javax.swing.DefaultComboBoxModel;

import javax.swing.JScrollPane;

import java.awt.Color;
import java.awt.Component;
import javax.swing.ImageIcon;
import java.awt.BorderLayout;
import javax.swing.JOptionPane;
import javax.swing.JDialog;

import javax.swing.ScrollPaneConstants;


/**
 * BaseDashBoardUI class.
 * This class creates an instance of the BaseDashBoard UI
 * @author Team18
 *
 */
public class BaseDashBoardUI extends JFrame{
    
    // Initialize Variables
    BaseDashBoard basedashboard = new BaseDashBoard();
    Font font = new Font("Arial", Font.PLAIN, 14);
    Font font2 = new Font("Arial", Font.BOLD, 48);
    Font font3 = new Font("Arial", Font.BOLD, 12);
    Font dateFont = new Font("Arial", Font.BOLD, 16);
    Font helloBeth =  new Font("Arial", Font.BOLD, 20);
    Color blueColour = Color.decode("#45C2C5");
    
    // Import images
    JLabel logoImage = new JLabel(new ImageIcon("src/main/resources/images/FitByte Logo.png"));
    JLabel awardA[] = new JLabel[20];
    JLabel awardD[] = new JLabel[20];
    
    {
        // Activate Awards and mouse hover
        awardA[0] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/burj.png"));
        awardA[0].setToolTipText("<html><body>Awesome, you climbed the Burj Khalifa (272 floors).</body></html>");
        awardA[1] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/10_days.png"));
        awardA[1].setToolTipText("<html><body>Congrats you've climbed 10 floors.</body></html>");
        awardA[2] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/heaven.png"));
        awardA[2].setToolTipText("<html><body>Amazing, you have conquered floors,<br> and have climbed to unimaginable heights.</body></html>");
        awardA[3] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/200_steps.png"));
        awardA[3].setToolTipText("<html><body>The first step in your journey outside of the house (200 steps).</body></html>");
        awardA[4] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/1000_floors.png"));
        awardA[4].setToolTipText("<html><body>Outstanding, you have climbed 1000 Floors.</body></html>");
        awardA[5] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/9000.png"));
        awardA[5].setToolTipText("<html><body>What does the fitbit say about your total step counter?<br> IT IS OVER 9000!!!!.</body></html>");
        awardA[6] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/back2back.png"));
        awardA[6].setToolTipText("<html><body>You have hit the big 10k, congrats on the milestone.</body></html>");
        awardA[7] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/burn_1000.png"));
        awardA[7].setToolTipText("<html><body>Your murderous intentions grow strong with every calorie burned (1000 calories).</body></html>");
        awardA[8] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/cake.png"));
        awardA[8].setToolTipText("<html><body>You have eaten the food of the devil,<br> how horrible you must feel (2420 calories).</body></html>");
        awardA[9] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/cereal.png"));
        awardA[9].setToolTipText("<html><body>You have killed a bowl of cereal,<br> I hope you are proud of that (379 calories).</body></html>");
        awardA[10] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/cold_heart.png"));
        awardA[10].setToolTipText("<html><body>You have murdered so much,<br> that your heart is as cold as ice (5200 calories).</body></html>");
        awardA[11] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/distance_earth.png"));
        awardA[11].setToolTipText("<html><body>You have travelled a lot,<br> only thing left is to travel to infinity and beyond (40075 km).</body></html>");
        awardA[12] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/earth.png"));
        awardA[12].setToolTipText("<html><body>Your adventures have taken you all around the earth<br> in only 131,480,184 steps.</body></html>");
        awardA[13] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/fat.png"));
        awardA[13].setToolTipText("<html><body>You are burning everything,<br> and do not seem to be ready to stop (3500 calories).</body></html>");
        awardA[14] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/mass.png"));
        awardA[14].setToolTipText("<html><body>You have destroyed everything in sight.<br> There is nothing else for you to murder (7500 calories).</body></html>");
        awardA[15] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/mile.png"));
        awardA[15].setToolTipText("<html><body>The song says I will walk 500 miles,<br> well you have walked 1 only 499 more to go (1.60934 km).</body></html>");
        awardA[16] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/moon.png"));
        awardA[16].setToolTipText("<html><body>I did not expect you to take the infinity and beyond part seriously (384400 km).</body></html>");
        awardA[17] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/shoe.png"));
        awardA[17].setToolTipText("<html><body>Those shoes must be getting pretty comfy (1000 steps).</body></html>");
        awardA[18] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/western.png"));
        awardA[18].setToolTipText("<html><body>You visited friends at Fanshawe<br> and then walked to Western for class (6.2 km).</body></html>");
        awardA[19] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Activate/whiteoaks.png"));
        awardA[19].setToolTipText("<html><body>Masonville was not good enough for you, <br>so you decided to walk 12 km to go to White Oaks(12.2 km).</body></html>");
        
        // Deactivate Awards and mouse hover
        awardD[0] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dburj.png"));
        awardD[0].setToolTipText("<html><body>Awesome, you climbed the Burj Khalifa.</body></html>");
        awardD[1] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/d10_days.png"));
        awardD[1].setToolTipText("<html><body>Congrats you've climbed 10 floors.</body></html>");
        awardD[2] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dheaven.png"));
        awardD[2].setToolTipText("<html><body>Amazing, you have conquered floors,<br> and have climbed to unimaginable heights.</body></html>");
        awardD[3] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/d200_steps.png"));
        awardD[3].setToolTipText("<html><body>The first step in your journey outside of the house (200 steps).</body></html>");
        awardD[4] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/d1000_floors.png"));
        awardD[4].setToolTipText("<html><body>Outstanding, you have climbed 1000 Floors.</body></html>");
        awardD[5] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/d9000.png"));
        awardD[5].setToolTipText("<html><body>What does the fitbit say about your total step counter?<br> IT IS OVER 9000!!!!.</body></html>");
        awardD[6] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dback2back.png"));
        awardD[6].setToolTipText("<html><body>You have hit the big 10k, congrats on the milestone.</body></html>");
        awardD[7] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dburn_1000.png"));
        awardD[7].setToolTipText("<html><body>You have murderous intentions grow strong with every calorie burned (1000 calories).</body></html>");
        awardD[8] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dcake.png"));
        awardD[8].setToolTipText("<html><body>You have eaten the food of the devil,<br> how horrible you must feel (2420 calories).</body></html>");
        awardD[9] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dcereal.png"));
        awardD[9].setToolTipText("<html><body>You have killed a bowl of cereal,<br> I hope you are proud of that (379 calories).</body></html>");
        awardD[10] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dcold_heart.png"));
        awardD[10].setToolTipText("<html><body>You have murdered so much,<br> that your heart is as cold as ice (5200 calories).</body></html>");
        awardD[11] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/ddistance_earth.png"));
        awardD[11].setToolTipText("<html><body>You have travelled a lot,<br> only thing left is to travel to infinity and beyond (40075 km).</body></html>");
        awardD[12] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dearth.png"));
        awardD[12].setToolTipText("<html><body>Your adventures have taken you all around the earth<br> in only 131,480,184 steps.</body></html>");
        awardD[13] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dfat.png"));
        awardD[13].setToolTipText("<html><body>You are burning everything,<br> and do not seem to be ready to stop (3500 calories).</body></html>");
        awardD[14] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dmass.png"));
        awardD[14].setToolTipText("<html><body>You have destroyed everything in sight.<br> There is nothing else for you to murder (7500 calories).</body></html>");
        awardD[15] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dmile.png"));
        awardD[15].setToolTipText("<html><body>The song says I will walk 500 miles,<br> well you have walked 1 only 499 more to go (1.60934 km).</body></html>");
        awardD[16] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dmoon.png"));
        awardD[16].setToolTipText("<html><body>I did not expect you to take the infinity and beyond part seriously (384400 km).</body></html>");
        awardD[17] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dshoe.png"));
        awardD[17].setToolTipText("<html><body>Those shoes must be getting pretty comfy (1000 steps).</body></html>");
        awardD[18] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dwestern.png"));
        awardD[18].setToolTipText("<html><body>You visited friends at Fanshawe<br> and then walked to Western for class (6.2 km).</body></html>");
        awardD[19] =  new JLabel(new ImageIcon("src/main/resources/images/awards/Deactivate/dwhiteoaks.png"));
        awardD[19].setToolTipText("<html><body>Masonville was not good enough for you,<br> so you decided to walk 12 km to go to White Oaks(12.2 km).</body></html>");
    }
    
    // Scroll for awards
    JScrollPane scrollPane = new JScrollPane();
    JPanel scrollPanelBorder = new JPanel();
    
    // Side Panel with Logo, user info and awards
    JPanel sidePanelLogo = new JPanel();
    JPanel sidePanelUser = new JPanel();
    JLabel sidePanelUserText = new JLabel("Hello User");
    JLabel sidePanelUserTextRefresh = new JLabel("Last Updated:");
    JLabel updateString = new JLabel();
    JPanel sidePanelAward = new JPanel();
    JLabel sidePanelAwardText = new JLabel("Awards");
    JPanel sidePanelAwardBox = new JPanel(new GridLayout());
    JLabel currentDate = new JLabel();
    JLabel currentDatetxt = new JLabel();
    
    JButton fitCalcButton = new JButton("FitCalc");
    JButton dailyGoalsButton = new JButton("Daily Goals");
    JButton heartRateButton = new JButton("Heart Rate");
    JButton dateButton = new JButton("Date");
    JButton refreshButton = new JButton("Refresh");
    JPanel buttonPanel = new JPanel();
    JPanel datePanel = new JPanel();
    
    // Create info Boxes
    static JLayeredPane boxes = new JLayeredPane();
    SingleBox singleFirstBox = new SingleBox();
    SingleBox singleSecondBox = new SingleBox();
    SingleBox singleThirdBox = new SingleBox();
    SingleBox singleFourthBox = new SingleBox();
    SingleBox singleFifthBox = new SingleBox();
    JPanel firstBox = singleFirstBox.createCaloriesBox();
    JPanel secondBox = singleSecondBox.createActiveSedentaryBox();
    JPanel thirdBox = singleThirdBox.createDistanceBox();
    JPanel fourthBox = singleFourthBox.createFloorBox();
    JPanel fifthBox = singleFifthBox.createStepBox();
    
    // Create empty box
    JPanel emptyBox = new JPanel();
    JButton plusSign = new JButton("+");
    
    private boolean startUp = true;
    private JFrame itself = this;
    private Data data;
    private boolean testOrNot;
    private APIData api;
    
    /**
     * Checks when to use default values or API
     * @param testorNot
     */
    public BaseDashBoardUI(boolean testorNot) {
        testOrNot = testorNot;
        singleFirstBox.setTestOrNot(testorNot);
        if (testorNot == true) {
            data = new TestData();
        } else {
            data = new APIData(basedashboard.getCurrentDate());
        }
        this.initUI();
        try {
            this.loadCustomConfiguration();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    /**
     * Gets the frames with info
     * @return JLayeredFrame of boxes
     */
    public static JLayeredPane getFrame() {
        return boxes;
    }
    
    // Method to create the main UI screen
    private void initUI() {
        
        // Set JFrame
        setTitle("Dashboard");
        setSize((500*16)/9, 500);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        getContentPane().setBackground(blueColour);
        setResizable(false);
        
        getContentPane().setLayout(null);
        singleFirstBox.passAPI(data,testOrNot);
        singleFirstBox.updateTilesVars();
        singleFirstBox.modifyString(0);
        singleFirstBox.modifyString(1);
        singleFirstBox.modifyString(2);
        singleFirstBox.modifyString(3);
        singleFirstBox.modifyString(4);
        
        
        /*
         * When user exits the app, app will try to create a new files that saves the configuration that was set by the user
         * at the time they exit the app
         */
        this.addWindowListener(new java.awt.event.WindowAdapter() {
            @Override
            public void windowClosing(java.awt.event.WindowEvent wind) {
                try {
                    basedashboard.storeClosedTileList();
                }
                catch (Exception e) {
                }
                wind.getWindow().dispose();
            }
        });
        
        // Setup how logo looks like
        logoImage.setVisible(true);
        sidePanelLogo.setBounds(this.getWidth()-250, 0, 250, 75);
        sidePanelLogo.setBackground(Color.WHITE);
        sidePanelLogo.add(logoImage, SwingConstants.CENTER);
        sidePanelLogo.setVisible(true);
        
        // Setup how side panel looks like
        sidePanelUserText.setFont(helloBeth);
        sidePanelUserText.setForeground(blueColour);
        sidePanelUserText.setBounds(80,0,250,40);
        sidePanelUserTextRefresh.setFont(font3);
        sidePanelUserTextRefresh.setForeground(blueColour);
        sidePanelUserTextRefresh.setBounds(30,120,250,40);
        sidePanelUserTextRefresh.setText("Last Updated: " + basedashboard.getCurrentTimeAndDate());
        
        currentDatetxt.setFont(font);
        currentDatetxt.setForeground(blueColour);
        currentDatetxt.setBounds(50,50,250,40);
        currentDatetxt.setText("Currently selected date: ");
        
        currentDate.setFont(dateFont);
        currentDate.setForeground(blueColour);
        currentDate.setBounds(85,70,250,40);
        currentDate.setText(basedashboard.getCurrentDate());
        
        sidePanelUser.add(currentDatetxt);
        sidePanelUser.add(currentDate);
        
        sidePanelUser.setLayout(null);
        sidePanelUser.add(sidePanelUserText);
        sidePanelUser.add(sidePanelUserTextRefresh);
        sidePanelUser.setBounds(this.getWidth()-250, 81, 250, 150);
        sidePanelUser.setBackground(Color.WHITE);
        sidePanelUser.setVisible(true);
        
        // Set up award panel
        sidePanelAward.setLayout(null);
        sidePanelAwardText.setHorizontalAlignment(SwingConstants.CENTER);
        sidePanelAwardText.setVerticalAlignment(SwingConstants.TOP);
        sidePanelAwardText.setFont(font);
        sidePanelAwardText.setForeground(blueColour);
        sidePanelAwardText.setBounds(75, 4, 100, 100);
        sidePanelAward.setBounds(this.getWidth()-250, 240, 250, 238);
        sidePanelAward.setBackground(Color.WHITE);
        sidePanelAward.setVisible(true);
        
        scrollPanelBorder.setBackground(Color.WHITE);
        scrollPanelBorder.setLayout(new GridLayout(0, 3, 5, 5));
        
        // Add the awards to the scroll pane
        for(int i=0;i<20;i++) {
            scrollPanelBorder.add(awardD[i]);
        }
        
        Boolean a[] = new Boolean[20];
        
        // Checks if the award have been given or not
        a = Accolades.complete(data, testOrNot);
        
        for(int i = 0; i < 20; i++){
            if(a[i] != false){
                scrollPanelBorder.remove(awardD[i]);
                scrollPanelBorder.add(awardA[i], i);
                sidePanelAward.repaint();
            }
        }
        
        // Setup the scroll pane
        scrollPane.setBounds(0, 30, 250, 200);
        scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        scrollPane.setViewportView(scrollPanelBorder);
        scrollPane.setBorder(null);
        
        sidePanelAward.add(sidePanelAwardText);
        sidePanelAward.add(scrollPane);
        
        
        // Setup how the buttons look like
        fitCalcButton.setFont(font);
        fitCalcButton.setForeground(blueColour);
        fitCalcButton.setVisible(true);
        fitCalcButton.addActionListener(new ActionListener(){
            // Checks if the button has been pressed and the actions it will do if pressed
            public void actionPerformed(ActionEvent event){
                try {
                    FitCalcUI fitCalc = new FitCalcUI(data, testOrNot);
                    fitCalc.setVisible(true);
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        
        // Setup how the daily goal button
        dailyGoalsButton.setFont(font);
        dailyGoalsButton.setForeground(blueColour);
        dailyGoalsButton.setVisible(true);
        dailyGoalsButton.addActionListener(new ActionListener(){
            // Checks if the button has been pressed and the actions it will do if pressed
            public void actionPerformed(ActionEvent event){
                try {
                    DailyGoalsUI daily = new DailyGoalsUI(data, testOrNot);
                    
                    daily.setVisible(true);
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        
        
        // Setup how the heartRate button looks like
        heartRateButton.setFont(font);
        heartRateButton.setForeground(blueColour);
        heartRateButton.setVisible(true);
        heartRateButton.addActionListener(new ActionListener(){
            // Checks if the button has been pressed and the actions it will do if pressed
            public void actionPerformed(ActionEvent event){
                try {
                    if (testOrNot == false && startUp == false) {
                        HeartRateUI HRUI = new HeartRateUI(singleFirstBox.returnAPI(), testOrNot);
                        HRUI.setVisible(true);
                    }
                    else {
                        HeartRateUI HRUI = new HeartRateUI(data, testOrNot);
                        HRUI.setVisible(true);
                    }
                } catch (Exception e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }
        });
        
        // Panel that holds heartRate, fitCalc and dailyGoals
        buttonPanel.setVisible(true);
        buttonPanel.setBounds(0,0,this.getWidth()-250,40);
        buttonPanel.setBackground(blueColour);
        buttonPanel.add(fitCalcButton);
        buttonPanel.add(dailyGoalsButton);
        buttonPanel.add(heartRateButton);
        
        // Setup how the date and refresh button looks like
        dateButton.setFont(font);
        dateButton.setForeground(blueColour);
        dateButton.setVisible(true);
        refreshButton.setFont(font);
        refreshButton.setForeground(blueColour);
        refreshButton.setVisible(true);
        
        refreshButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                if (testOrNot == false) {
                    api = (APIData) data;
                    if (api.isErrorConnection() == true) {
                        JOptionPane.showMessageDialog(itself,"Could not establish connection with FitBit Server! Try again later","Connection warning",JOptionPane.WARNING_MESSAGE);
                    }
                    else {
                        if (startUp == true) {
                            singleFirstBox.updateAPI(basedashboard.getCurrentDate());
                        }
                        else {
                            singleFirstBox.updateAPI(basedashboard.getSelectedDate());
                        }
                        
                        singleFirstBox.updateTilesVars();
                        singleFirstBox.modifyString(0);
                        singleFirstBox.modifyString(1);
                        singleFirstBox.modifyString(2);
                        singleFirstBox.modifyString(3);
                        singleFirstBox.modifyString(4);
                        
                        //Startup app, get current date, otherwise get the selected Date
                        if (startUp == true) {
                            currentDate.setText(basedashboard.getCurrentDate());
                        }
                        else {
                            currentDate.setText(basedashboard.getSelectedDate());
                        }
                        sidePanelUserTextRefresh.setText("Last Updated: " + basedashboard.getCurrentTimeAndDate());
                    }
                }
                sidePanelUserTextRefresh.setText("Last Updated: " + basedashboard.getCurrentTimeAndDate());
            }
        });
        datePanel.setVisible(true);
        datePanel.setBounds(-20,30,this.getWidth()-250,40);
        datePanel.setBackground(blueColour);
        datePanel.add(dateButton);
        datePanel.add(refreshButton);
        
        // Check what happens when date button is pressed
        dateButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent event) {
                
                // Declare variables
                final JDialog dateDialog = new JDialog();
                //Modal
                dateDialog.setModal(true);
                dateDialog.setMinimumSize(new Dimension(442,237));
                dateDialog.setResizable(false);
                
                JPanel contentPane = new JPanel();
                JLayeredPane layeredPane = new JLayeredPane();
                Component layeredPane_1 = new JLayeredPane();
                JLayeredPane layeredPane1 = new JLayeredPane();
                JLabel lblNewLabel = new JLabel("Please enter the date in the format YYYY/MM/DD");
                JLayeredPane layeredPane_11 = new JLayeredPane();
                JLabel lblNewLabelYear = new JLabel("Year");
                JLabel lblNewLabelMonth = new JLabel("Month");
                JLabel lblNewLabelDay = new JLabel("Day");
                JLayeredPane layeredPane_2 = new JLayeredPane();
                final JTextField textField = new JTextField();
                final JTextField textField_1 = new JTextField();
                final JTextField textField_2 = new JTextField();
                JLayeredPane layeredPane_3 = new JLayeredPane();
                JButton btnOk = new JButton("OK");
                
                // Create new date UI
                //dateDialog.setVisible(true);
                dateDialog.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
                dateDialog.setBounds(100, 100, 442, 237);
                contentPane.setBackground(new Color(69, 194, 197));
                contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
                dateDialog.getContentPane().add(contentPane);
                
                layeredPane.setLayer(layeredPane_1, 1);
                contentPane.setLayout(null);
                
                layeredPane1.setBounds(0, 11, 444, 32);
                contentPane.add(layeredPane1);
                layeredPane1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
                
                layeredPane1.add(lblNewLabel);
                
                layeredPane_11.setBounds(0, 72, 444, 32);
                contentPane.add(layeredPane_11);
                layeredPane_11.setLayout(new FlowLayout(FlowLayout.CENTER, 90, 5));
                
                layeredPane_11.add(lblNewLabelYear);
                layeredPane_11.add(lblNewLabelMonth);
                layeredPane_11.add(lblNewLabelDay);
                
                layeredPane_2.setBounds(0, 99, 444, 32);
                contentPane.add(layeredPane_2);
                layeredPane_2.setLayout(new FlowLayout(FlowLayout.CENTER, 35, 5));
                
                layeredPane_2.add(textField);
                textField.setColumns(7);
                
                layeredPane_2.add(textField_1);
                textField_1.setColumns(7);
                
                layeredPane_2.add(textField_2);
                textField_2.setColumns(7);
                
                layeredPane_3.setBounds(0, 160, 444, 39);
                contentPane.add(layeredPane_3);
                layeredPane_3.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
                layeredPane_3.add(btnOk);
                
                JButton exitDate = new JButton("Exit");
                exitDate.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent event) {
                        dateDialog.dispose();
                    }
                });
                layeredPane_3.add(exitDate);
                
                // Checks when the button is pressed and the actions
                btnOk.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent event) {
                        String userMessage = basedashboard.checkDateInput(textField.getText(),textField_1.getText(),textField_2.getText());
                        if (userMessage == "") {
                            startUp = false;
                            if (testOrNot == false) {
                                api = (APIData) data;
                                if (api.isErrorConnection() == true) {
                                    JOptionPane.showMessageDialog(itself,"Could not establish connection with FitBit Server! Try again later","Connection warning",JOptionPane.WARNING_MESSAGE);
                                }
                                else {
                                    singleFirstBox.updateAPI(basedashboard.getSelectedDate());
                                    singleFirstBox.updateTilesVars();
                                    singleFirstBox.modifyString(0);
                                    singleFirstBox.modifyString(1);
                                    singleFirstBox.modifyString(2);
                                    singleFirstBox.modifyString(3);
                                    singleFirstBox.modifyString(4);
                                }
                            }
                            
                            dateDialog.dispose();
                            currentDate.setText(basedashboard.getSelectedDate());
                            sidePanelUserTextRefresh.setText("Last Updated: " + basedashboard.getCurrentTimeAndDate());
                        }
                        else {
                            JOptionPane.showMessageDialog(dateDialog,userMessage,"Input warning",JOptionPane.WARNING_MESSAGE);
                        }
                    }
                });
                
                //Display
                dateDialog.setLocationRelativeTo(null);
                dateDialog.setVisible(true);
            }});
        
        // Create empty Box
        emptyBox.setBorder(BorderFactory.createDashedBorder(Color.WHITE, 2, 1, 1, false));
        emptyBox.setVisible(true);
        emptyBox.setBackground(null);
        
        // Create plus sign
        plusSign.setFont(font2);
        plusSign.setLayout(null);
        plusSign.setForeground(Color.WHITE);
        plusSign.setBorder(null);
        
        // Creates an action when the plus button is pressed
        plusSign.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                
                // Declare variables
                JPanel contentPane;
                final JDialog plusButton = new JDialog();
                JButton btnNewButton = new JButton("OK");
                JLayeredPane layeredPane = new JLayeredPane();
                JLabel lblSelectTheFeatures = new JLabel("Select the feature(s) you wish to view");
                final JComboBox<String[]> comboBox = new JComboBox<String[]>();
                
                //Modal
                plusButton.setModal(true);
                plusButton.setResizable(false);
                
                plusButton.setTitle("Adding Back Features that were Removed");
                plusButton.setBounds(100, 100, 276, 180);
                plusButton.setMinimumSize(new Dimension(276,180));
                contentPane = new JPanel();
                contentPane.setToolTipText("hello");
                contentPane.setBackground(new Color(69, 194, 197));
                contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
                plusButton.setContentPane(contentPane);
                contentPane.setLayout(new BorderLayout(0,0));
                
                //modal
                plusButton.setLocationRelativeTo (btnNewButton);
                //plusButton.setModal(true);
                
                layeredPane.setBounds(0, 0, 276, 195);
                layeredPane.setToolTipText("");
                contentPane.add(BorderLayout.CENTER, layeredPane);
                layeredPane.setLayout(new FlowLayout(FlowLayout.CENTER, 450, 17));
                
                lblSelectTheFeatures.setAlignmentX(0.5f);
                layeredPane.add(lblSelectTheFeatures);
                
                //set the size of combobox
                comboBox.setPreferredSize(new Dimension(110, 20));
                comboBox.setModel(new DefaultComboBoxModel(basedashboard.getStringArrayList()));
                
                // Creates an action when OK is pressed
                btnNewButton.addActionListener(new ActionListener() {
                    public void actionPerformed(ActionEvent e) {
                        if (basedashboard.getStringArrayList().length == 0) {
                            // When the box is full
                            JOptionPane.showMessageDialog(plusSign,"Whoa! There are no more features to add so nothing is going to happen.\n Nothing else to see around here.","Input warning",JOptionPane.WARNING_MESSAGE);
                        }
                        else if (comboBox.getSelectedItem().toString().equals("Calories")) {
                            
                            // Declare variables
                            SingleBox singleFirstBox = new SingleBox();
                            JPanel firstBox = singleFirstBox.createCaloriesBox();
                            // Add calories box
                            BaseDashBoardUI.getFrame().remove(emptyBox);
                            BaseDashBoardUI.getFrame().add(firstBox);
                            BaseDashBoardUI.getFrame().add(emptyBox);
                            boxes.repaint();
                            SwingUtilities.updateComponentTreeUI(boxes);
                            basedashboard.readdedSelectedTile("Calories");
                        }
                        else if (comboBox.getSelectedItem().toString().equals("Active Minutes")) {
                            
                            // Declare variables
                            SingleBox singleSecondBox = new SingleBox();
                            JPanel secondBox = singleSecondBox.createActiveSedentaryBox(); 
                            // Add Minute box
                            BaseDashBoardUI.getFrame().remove(emptyBox);
                            BaseDashBoardUI.getFrame().add(secondBox);
                            BaseDashBoardUI.getFrame().add(emptyBox);
                            boxes.repaint();
                            SwingUtilities.updateComponentTreeUI(boxes);
                            basedashboard.readdedSelectedTile("Active Minutes");
                        }
                        else if (comboBox.getSelectedItem().toString().equals("Distance")) {
                            
                            // Declare variables
                            SingleBox singleThirdBox = new SingleBox();
                            JPanel thirdBox = singleThirdBox.createDistanceBox();
                            // Add Distance box
                            BaseDashBoardUI.getFrame().remove(emptyBox);
                            BaseDashBoardUI.getFrame().add(thirdBox);
                            BaseDashBoardUI.getFrame().add(emptyBox);
                            boxes.repaint();
                            SwingUtilities.updateComponentTreeUI(boxes);
                            basedashboard.readdedSelectedTile("Distance");
                        }
                        else if (comboBox.getSelectedItem().toString().equals("Floors")) {
                            
                            // Declare variables
                            SingleBox singleFourthBox = new SingleBox();
                            JPanel fourthBox = singleFourthBox.createFloorBox();
                            // Add Floors box
                            BaseDashBoardUI.getFrame().remove(emptyBox);
                            BaseDashBoardUI.getFrame().add(fourthBox);
                            BaseDashBoardUI.getFrame().add(emptyBox);
                            boxes.repaint();
                            SwingUtilities.updateComponentTreeUI(boxes);
                            basedashboard.readdedSelectedTile("Floors");
                        }
                        else if (comboBox.getSelectedItem().toString().equals("Steps")) {
                            
                            // Declare variables
                            SingleBox singleFifthBox = new SingleBox();
                            JPanel fifthBox = singleFifthBox.createStepBox();
                            // Add steps box
                            BaseDashBoardUI.getFrame().remove(emptyBox);
                            BaseDashBoardUI.getFrame().add(fifthBox);
                            BaseDashBoardUI.getFrame().add(emptyBox);
                            boxes.repaint();
                            SwingUtilities.updateComponentTreeUI(boxes);
                            basedashboard.readdedSelectedTile("Steps");
                        }
                        plusButton.dispose();
                        plusSign.setFont(font2);
                        plusSign.setLayout(null);
                        plusSign.setForeground(Color.WHITE);
                        plusSign.setBorder(null);
                    }
                });
                // Add button and combo to Pane
                btnNewButton.setAlignmentX(0.5f);
                layeredPane.add(comboBox);
                layeredPane.add(btnNewButton);
                plusButton.setVisible(true);
                plusButton.pack();
            }
        });
        // Setup how empty box looks like
        emptyBox.setLayout(new BorderLayout());
        emptyBox.add(plusSign);
        
        // Setup how boxes looks like
        boxes.setBounds(45,75,550,350);
        boxes.setVisible(true);
        boxes.setLayout(new GridLayout(2,3,20,15));
        
        // Add the tiles to boxes
        boxes.add(firstBox);
        boxes.add(secondBox);
        boxes.add(thirdBox);
        boxes.add(fourthBox);
        boxes.add(fifthBox);
        boxes.add(emptyBox);
        
        
        // Add everything to main UI screen
        getContentPane().add(buttonPanel);
        getContentPane().add(datePanel);
        getContentPane().add(sidePanelLogo);
        getContentPane().add(sidePanelUser);
        getContentPane().add(sidePanelAward);
        getContentPane().add(boxes);
    }
    
    // Loads default values
    private void loadCustomConfiguration() throws Exception{
        try {
            ArrayList<String> tileList = BaseDashBoard.loadClosedTileList();
            
            for (int i = 0; i < tileList.size(); i++) {
                if (tileList.get(i).toString().equals("Calories")) {
                    BaseDashBoardUI.getFrame().remove(firstBox);
                }
                if (tileList.get(i).toString().equals("Active Minutes")){
                    BaseDashBoardUI.getFrame().remove(secondBox);
                }
                if (tileList.get(i).toString().equals("Distance")) {
                    BaseDashBoardUI.getFrame().remove(thirdBox);
                }
                if (tileList.get(i).toString().equals("Floors")){
                    BaseDashBoardUI.getFrame().remove(fourthBox);
                }
                if (tileList.get(i).toString().equals("Steps")) {
                    BaseDashBoardUI.getFrame().remove(fifthBox);
                }
            }
        }
        catch (IOException e) {
        }
        catch (Exception e) {
        }
    }
    
} //End of class
