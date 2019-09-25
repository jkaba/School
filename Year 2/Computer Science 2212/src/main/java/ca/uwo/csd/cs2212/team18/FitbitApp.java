package ca.uwo.csd.cs2212.team18;
import javax.swing.SwingUtilities;

/**
 * FitBitApp class, this is the main method to run the program
 * @author team 18
 */
public class FitbitApp {
	public static void main(final String[] args) {
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {

				if (args.length > 0) {
					if (args[0].equals("test")) {
					BaseDashBoardUI window = new BaseDashBoardUI(true);
					window.setVisible(true);
					}
				
				} else {
					BaseDashBoardUI window = new BaseDashBoardUI(false);
					window.setVisible(true);
				}
			}
		});
	}
}