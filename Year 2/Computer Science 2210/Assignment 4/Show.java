import java.util.*;
import java.lang.Thread.*;

public class Show {

    private static Figure[] figures;         // Data structure to store figures
    private static Gui window;
    private static final int MOBILE_FIGURE = 1;// Figure that can be moved by
                                               // user 
    private static final int FIGURE_KILLED = 4;// Figure destroyed
    private static final int SUCCESS = -2;     // Figure was successfully moved
    private static final int HIT_BORDER = -1;  // Figure could not move as it 
	                                       // hit the window's border

    /* ====================================== */
    public  static void main (String args[]) {
    /* ====================================== */

	int numberFigures;
	final int progType = 2;  // Type of figures crontrolled by the
                                 // computer
	final int left = 0;      // Movement directions
	final int right = 1;
	final int up = 2;
	final int down = 3;



	int ncomp;         // Number of figures controlled by the computer
	int[] progFig;     // Figures controlled by computer
	int[] dir;         // Direction in which computer figures move

	Random generator = new Random();
	int rand, code;
	int step = 4;      // Length in pixels of each movement of a figure
	Position p;
	MoveFigure mover; 

        window = new Gui(500,500,args[0]);  // Set up drawing environment
	mover = new MoveFigure(window);     // and read input figures
	figures = window.getFigures();      
	numberFigures = window.getNumFigures();
	progFig = new int[numberFigures];
	dir = new int[numberFigures];

	// Determine the figures controlled by the prorgam 
	ncomp = 0;
	for (int i = 0; i < numberFigures; ++i) {
	    if (figures[i].getType() == progType) {
		dir[ncomp] = generator.nextInt(3);// Choose random direction
		                                  // for movement of figure

		progFig[ncomp] = i;
		ncomp++;
	    }
	}

	//Move figures randomly
	while (true) {
	    for (int i = 0; i < ncomp; ++i) {
		if (dir[i] == left) {
		    if ((code = mover.moveLeft(figures,numberFigures,
					      progFig[i],step)) != SUCCESS)
			dir[i] = resolveCollision(code,dir[i]);
		}
		else if (dir[i] == right) {
		    if ((code = mover.moveRight(figures,numberFigures,
						progFig[i],step)) != SUCCESS)
			dir[i] = resolveCollision(code,dir[i]);
		}
		else if (dir[i] == up) {
		    if ((code = mover.moveUp(figures,numberFigures,
					     progFig[i],step)) != SUCCESS)
			dir[i] = resolveCollision(code,dir[i]);
		}
		else {
		    if ((code = mover.moveDown(figures,numberFigures,
					       progFig[i],step)) != SUCCESS)
			dir[i] = resolveCollision(code,dir[i]);
		}
	    }
	    if (window.Wait()) ++step;
	}

    }

    /* ======================================================= */
    private static int resolveCollision(int code, int dir) {
    /* ======================================================= */
    // Determine direction in which figure will next move. Delete
    // figures that have been destroyed.

	Random generator = new Random();

	if ((code != HIT_BORDER) && 
	    (figures[code].getType() == MOBILE_FIGURE)) {
	    /* Kill figure */
	    try {
                // Erase figure. Figure will blink 5 times
		for (int i = 0; i < 5; ++i) {
		    window.drawFigure(figures[code]);
		    Thread.sleep(200);
		    window.eraseFigure(figures[code]);
		    Thread.sleep(200);
		}

		figures[code].setOffset(new Position(-1000,-1000));
		figures[code].setType(FIGURE_KILLED);
	    }
	    catch (Exception e) {
		System.out.println(e.getMessage());
	    }
	}

	return (dir+generator.nextInt(3)) % 4;
    }
}