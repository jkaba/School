import java.io.*;
import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.lang.Thread;
import java.awt.image.*;
import javax.imageio.*;

/* Create the graphical user interface */
public class Gui extends JFrame implements ActionListener, KeyListener {

  private JPanel buttonPanel;
  private JButton buttons[];

  private Graphics display;    // Graphics object needed to draw
  private Board panel;         // Panel containing map
  private Container contentPane;

  private Color backgroundColor = new Color(205,200,205);

  private final int TRANSPARENT = 0xCDC8CD; // Background color with transparency
  private final int SOLID = 0xFFCDC8CD; // Background color

  private final int MENU_HEIGHT = 74;    // Height of buttons toolbar
  private final int BORDER = 9;         // Border width

    //private final int gridSize = 50;

  private int step = 3;               // Number of pixels by which the figure
                                      // moves every time that an arrow key
                                      //is pressed
  private int delay = 300;            // Time between figure movements
  private boolean toWait = true;      // Movement of figures is paused
  private MoveFigure mover;

  private Thread clock;               // Auxiliary variable to pause execution
                                      // of program

  private int windowWidth;            // Dimensions of playing window
  private int windowHeight;

  private final int MOBILE_FIGURE = 1;// Type of figure that user can move
  private final int TARGET = 3;       // Type of figure that can be destroyed
                                      // by the mobile figures
  private final int FIGURE_KILLED = 4;// Type of figure that has been killed
  private final int MAX_FIGURES = 50; // Maximum number of figures to display
  private final int THRESHOLD = 225;  // transparent pixels have RGB values 
                                      // >= threshold

  private boolean increaseStep = false; // Set to true to move computer figures
                                        // with longer steps
  private int numMobile = 0;          // Number of figures that user can move
  private int[] mobileFigs = new int[MAX_FIGURES];
  private int numFigures = 0;
  Figure[] figs = new Figure[MAX_FIGURES];  // Figures are stored in this array 
  BufferedImage[] imgs = new BufferedImage[MAX_FIGURES]; // Information needed
                                                        // to display the figures
  BufferedImage[] erased = new BufferedImage[MAX_FIGURES]; // Info needed to erase
                                                          // the figures 
 
  /* ============================================== */
    public Gui(int width, int height, String name) {
  /* ============================================== */

    try {

      windowWidth = width;
      windowHeight = height;

      panel = new Board();
      contentPane = getContentPane();
      contentPane.add(panel);
      setSize(width,height);
      setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
      setVisible(true);

      display = panel.getGraphics();

      contentPane.setBackground(backgroundColor);
      display.setColor(backgroundColor);

      /* Create buttons and mouse event handlers */

      buttonPanel = new JPanel();
      buttons = new JButton[6];

      buttons[0] = makeButton("Start",backgroundColor);
      buttons[1] = makeButton("Pause",backgroundColor);
      buttons[2] = makeButton("Slower",backgroundColor);
      buttons[3] = makeButton("Faster",backgroundColor);
      buttons[5] = makeButton("Exit",backgroundColor);
	  buttons[4] = makeButton("Re-paint",backgroundColor);
   
      for (int i = 0; i < buttons.length; i++)
        buttonPanel.add(buttons[i]);

      /* Place buttons at the bottom of the Window */
      contentPane.add(buttonPanel,BorderLayout.SOUTH);

      for (int i=0; i < buttons.length; ++i)
        buttons[i].addActionListener(this);

      contentPane.addKeyListener(this);
      contentPane.setFocusable(true);
      contentPane.requestFocusInWindow();

      System.out.println("Initializing ...");
      clock = new Thread();
      clock.sleep(2000);

      readFigures(name);
      mover = new MoveFigure(this);
      System.out.println("Ready.");
    }
    catch (Exception e) {
	System.out.println("Error starting program: "+e.getMessage());
    }
  }

    /* =======================================*/
    private  void readFigures (String name) {
    /* =======================================*/
    /* Read figures from the input file. Each line of the
       input file has the form: 
          x y type file
       where 
       - (x,y) is the coordinate of the upper left corner of where the 
         figure will be drawn, 
       - type = 0 : fixed figure
         type = 1 : figure moved by user
         type = 2 : figure moved by computer
         type = 3 : target figure
       - file is the name of an image file in .bmp, .jpeg, or .gif format                           */

      StringTokenizer tokenizer;
      int x, y, width, height, type;
      String imagefile;
      BufferedImage im;

      try {
          // Open the input file
          BufferedReader inputFig = new BufferedReader( new InputStreamReader( 
                         new FileInputStream(new File(name))));
          String buff = inputFig.readLine();

 	  numFigures = 0;

	  while (buff != null) {

	    /* Read (x,y) and name of image file */
	    tokenizer = new StringTokenizer(buff);
	    x = Integer.parseInt(tokenizer.nextToken());
	    y = Integer.parseInt(tokenizer.nextToken());
	    type = Integer.parseInt(tokenizer.nextToken());
	    imagefile = tokenizer.nextToken();

	    if (type == MOBILE_FIGURE) 
		mobileFigs[numMobile++] = numFigures;

	    im = ImageIO.read(new File(imagefile));

	    width = im.getWidth();
	    height = im.getHeight();

	    imgs[numFigures] = new BufferedImage
                              (width,height,BufferedImage.TYPE_4BYTE_ABGR);
	    erased[numFigures] = new BufferedImage
                              (width,height,BufferedImage.TYPE_4BYTE_ABGR);

	    figs[numFigures] = new Figure(numFigures,width,height,type,
					  new Position(x,y));

	    insertPoints(im,numFigures,0,0,width-1,height-1,width);

	    ++numFigures;
	    drawFigure(figs[numFigures-1]); // numFigures must be equal to
	                                    // the number of existing figures

	    if (numFigures > MAX_FIGURES) {
		System.out.println("Maximum number of figures is "
				   + MAX_FIGURES);
		break;
	    }

	    buff = inputFig.readLine();

	  }

	  inputFig.close();
        }
        catch (IOException e) {
	  System.out.println("Error opening file. "+e.getMessage());
        }
        catch (BSTException e) {
	  System.out.println("Error while creating figures. "+e.getMessage());
        }
        catch (Exception e) {
	  System.out.println(e.getMessage());
      }
      
    }          

    /* ======================================================================== */
    private void insertPoints(BufferedImage im, int nfig, int xf, 
                          int yf, int xl, int yl, int width) throws BSTException{
    /* ======================================================================== */
    /* Insert the pixels into the data structure to represent the figure */
        int m, xm, ym, rgb;
        int xm1, xm2, ym1, ym2;


	/* Perform a binary splitting of the pixels and insert them in that
           order in the offset binary search tree                           */
	if ((yf < yl) || ((yf == yl) && (xf <= xl))) {
	    m = (yf*width+xf+yl*width+xl)/2;   // Pixel in the middle of figure
	    xm = m % width;           // Coordinates of the middle pixel
	    ym = m / width;
	    rgb = im.getRGB(xm,ym);   // Color of middle pixel
	    if (((rgb & 0xff) >= THRESHOLD) && 
                (((rgb & 0xff00) >> 8) >= THRESHOLD) &&
		(((rgb & 0xff0000) >> 16) >= THRESHOLD))
		rgb = rgb & 0x00ffffff;  // Transparent pixels are not inserted
                                         // in the tree
	    else figs[nfig].addPixel(xm,ym,rgb);
	    imgs[nfig].setRGB(xm,ym,rgb);

	    if ((rgb & 0xff000000) == 0) // Figure of same color as background
                                         // used to erase the current figure
		erased[nfig].setRGB(xm,ym,TRANSPARENT);
	    else erased[nfig].setRGB(xm,ym,SOLID);

	    // Split the figure around the middle pixel
	    if (xm > 0) {
		xm1 = xm -1;
		ym1 = ym;
	    }
	    else {
		xm1 = width -1;
		ym1 = ym -1;
	    }
	    if (xm < width -1) {
		xm2 = xm+1;
		ym2 = ym;
	    }
	    else {
		xm2 = 0;
		ym2 = ym+1;
	    }

	    // Insert the pixels in each half of the figure
	    insertPoints(im,nfig,xf,yf,xm1,ym1,width);
	    insertPoints(im,nfig,xm2,ym2,xl,yl,width);

	}
    }


    /* ==================== */
    public int displayWidth() {
    /* ==================== */
	return windowWidth - BORDER;
    }


    /* ==================== */
    public int displayHeight() {
    /* ==================== */
	return windowHeight - MENU_HEIGHT;
    }


    /* =================================================== */
    public Graphics getDisplay() {
    /* =================================================== */
	return display;
    }


    /* =================================================== */
    private JButton makeButton(String label, Color color)
    /* =================================================== */
    {
      JButton b = new JButton(label);
      b.setBackground(color);
      return b;
    }

    /* ======================================= */
    public void actionPerformed(ActionEvent e)
    /* ======================================= */
    {
      String s = (String)e.getActionCommand();
    
      if (s.equals("Start")) Start();
      else if (s.equals("Pause")) toWait = true;
      else if (s.equals("Slower")) delay += 100;
      else if (s.equals("Faster")) {
	  if (delay >= 100) delay -= 100;
	  else increaseStep = true;
      }
	  else if (s.equals("Re-paint")) {
		 for (int i = 0; i < numFigures; ++i)
	         drawFigure(figs[i]);
	  }
      else if (s.equals("Exit")) {
	  dispose();
	  System.exit(0);
      }

      contentPane.requestFocusInWindow();
    }


    /* ====================== */
    private void Start() {
    /* ====================== */
    /* Start game */
	toWait = false;

    }


    /* ================== */
    public boolean Wait() {
    /* ================== */
    /* Returns true if user clicked on the "Faster" button */
	try {
	    if (toWait) {
	    /* Game is in pause mode */
		while (toWait) clock.sleep(1000);
	    }
	    else if (delay > 0) clock.sleep(delay);
	}
	catch(Exception e) {
	    System.out.println(e.getMessage());
	}
	if (increaseStep) {
	    increaseStep = false;
	    return true;
	}
	else return false;
    }


  /* ======================================= */
  public void keyPressed (KeyEvent e) {
  /* ======================================= */
        int b, i;
        int c = e.getKeyCode ();

	/* Move user figures depending on which key was pressed */
	for (i = 0; i < numMobile; ++i) {
	    b = -1;
	    if (figs[mobileFigs[i]].getType() != FIGURE_KILLED) {
		if (c == KeyEvent.VK_UP) 
		    b = mover.moveUp(figs,numFigures,mobileFigs[i],step);  
	        else if(c==KeyEvent.VK_DOWN)                
		    b = mover.moveDown(figs,numFigures,mobileFigs[i],step);   
		else if(c==KeyEvent.VK_LEFT)                
		    b = mover.moveLeft(figs,numFigures,mobileFigs[i],step);   
		else if(c==KeyEvent.VK_RIGHT)             
		    b = mover.moveRight(figs,numFigures,mobileFigs[i],step); 
		else if (c == KeyEvent.VK_B) Start();
		else if (c == KeyEvent.VK_X) {
		         dispose();
		         System.exit(0);
		}
		else if (c == KeyEvent.VK_F) {
		         if (delay >= 100) delay -= 100;
			 else increaseStep = true;
		}
		else if (c == KeyEvent.VK_S) delay+=100;
	    }
	    if (b >= 0) { // There was a collision
		if (figs[b].getType() == TARGET) {
		    eraseFigure(figs[b]);
		    figs[b].setType(FIGURE_KILLED);
		    figs[b].setOffset(new Position(-1000,-1000));
		}
	    }
	}
    }

  /* ======================================= */
    public void keyTyped(KeyEvent ke) {
  /* ======================================= */
    }

  /* ======================================= */
    public void keyReleased(KeyEvent ke) {}
  /* ======================================= */
  

  /* ======================================= */
    public void drawFigure (Figure f) {
  /* ======================================= */
  /* Draw the given figure at its current position */

	Position pos;
	try {
	    for (int i = 0; i < numFigures; ++i) {
		if (figs[i].getId() == (f.getId())) {
		    pos = figs[i].getOffset();
		    display.drawImage(imgs[i],pos.getX(),pos.getY(),null);
		    clock.sleep(10);
		    return;
		}
	    }
	}
	catch (Exception e) {
	    System.out.println(e.getMessage());
	}

    }

  /* ======================================= */
    public void eraseFigure (Figure f) {
  /* ======================================= */
  /* Erase the given figure */

	Position pos;

	for (int i = 0; i < numFigures; ++i) {
	    if (figs[i].getId() == (f.getId())) {
		pos = figs[i].getOffset();
		display.drawImage(erased[i],pos.getX(),pos.getY(),null);
		return;
	    }
	}

    }


    /* =========================== */
    public Figure[] getFigures() {
    /* =========================== */
	return figs;
    }


    /* =========================== */
    public int getNumFigures() {
    /* =========================== */
	return numFigures;
    }

}
