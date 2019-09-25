package ca.uwo.csd.cs2212.team18;

import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;
/**
 * Class that handles all the text that the FitCalcUI2 displays
 * @author Team18
 *
 */

public class FitCalcDisplayActivities {

	
	
	/**
	 * When given certain parameters, creates all the appropriate fields for the FitCalcUI2
	 * @param fitCalculator
	 * @param defaultActivities
	 * @param numberOfActivity
	 * @return Textfields and Labels that are on the FitCalcUi2
	 */
	public static JPanel createActivity(FitCalc fitCalculator, boolean defaultActivities, int numberOfActivity) {
		FitCalc fitCalc = fitCalculator;
		String[][] displayArray = fitCalc.getDisplayStrings(defaultActivities);
		JPanel Activity = new JPanel();
		Activity.setBackground(null);
		GridBagLayout gbl_Suggestions = new GridBagLayout();
		Activity.setLayout(gbl_Suggestions);
							
		JLabel lbl1 = new JLabel(displayArray[numberOfActivity][0]);
		lbl1.setBackground(null);
		GridBagConstraints gbc_lbl1 = new GridBagConstraints();
		gbc_lbl1.anchor = GridBagConstraints.LINE_END;
		gbc_lbl1.gridx = 0;
		gbc_lbl1.gridy = 0;
		Activity.add(lbl1, gbc_lbl1);
		
		JTextField txt1 = new JTextField(displayArray[numberOfActivity][1]);
		txt1.setEditable(false);
		GridBagConstraints gbc_txt1 = new GridBagConstraints();
		gbc_txt1.anchor = GridBagConstraints.LINE_START;
		gbc_txt1.gridx = 1;
		gbc_txt1.gridy = 0;
		Activity.add(txt1, gbc_txt1);
		txt1.setColumns(15);	
		
		JLabel lblSuggest1 = new JLabel(displayArray[numberOfActivity][2]);
		lblSuggest1.setBackground(null);
		GridBagConstraints gbc_lblSuggest1 = new GridBagConstraints();
		gbc_lblSuggest1.anchor = GridBagConstraints.LINE_END;
		gbc_lblSuggest1.gridx = 0;
		gbc_lblSuggest1.gridy = 1;
		Activity.add(lblSuggest1, gbc_lblSuggest1);
		
		JTextField txtSuggest1 = new JTextField(displayArray[numberOfActivity][3]);
		GridBagConstraints gbc_txtSuggest1 = new GridBagConstraints();
		gbc_txtSuggest1.anchor = GridBagConstraints.LINE_START;
		txtSuggest1.setEditable(false);
		gbc_txtSuggest1.gridx = 1;
		gbc_txtSuggest1.gridy = 1;
		Activity.add(txtSuggest1, gbc_txtSuggest1);
		txtSuggest1.setColumns(15);
		
		JLabel after1 = new JLabel(displayArray[numberOfActivity][4]);
		after1.setBackground(null);
		GridBagConstraints gbc_after1 = new GridBagConstraints();
		gbc_after1.anchor = GridBagConstraints.LINE_END;
		gbc_after1.gridx = 0;
		gbc_after1.gridy = 2;
		Activity.add(after1, gbc_after1);
	
		JTextField after = new JTextField(displayArray[numberOfActivity][5] + " Mins");
	
		GridBagConstraints gbc_after = new GridBagConstraints();
		gbc_after.anchor = GridBagConstraints.LINE_START;
		after.setEditable(false);
		gbc_after.gridx = 1;
		gbc_after.gridy = 2;
		Activity.add(after, gbc_after);
		after.setColumns(15);
		return Activity;
		
		
	}

}
