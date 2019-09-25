// ******************************************************
// Do not change this code. We will make changes to this
// file for testing your submissions. Hence, if you rely
// on changes that you have made yourself, your  program
// might fail some of our tests.
// ******************************************************

import java.io.*;
import java.awt.*;
import java.awt.image.*;
import javax.swing.*;
import javax.imageio.*;
import java.util.*;
import java.lang.Thread;

public class DrawMap extends JFrame {
  private Graphics display;    // Graphics object needed to draw
  private Board panel;         // Panel containing map

  private int numNodes;        // Number of nodes in the graph
  private int busChanges;    // Number of bus changes allowed in solution
  private int mapWidth;        // Width of the map (number of nodes across)
  private int mapLength;       // Length of the map (number of nodes in a
                               // column of the graph)

  private int gridSize;        // Size of each square in the grid 
                               // representation of the graph

  private char[][] map;
  private BufferedImage[] imgs; // Image files used to display hosue blocks
  private int numImages = 4;
  private int numLines = 11;    // Max number of bus lines
  private boolean imageFiles = true;
  private int lx = -1, ly, lwidth, lheight; // Last edge of the path

  private Color pathColor = new Color(255,0,0);
  private Color entranceColor = new Color(100,100,160);
  private Color exitColor = new Color(0,200,0);
  private Color backColor = new Color(140,200,160);
  private Color streetColor = new Color(200,200,200);
  private Color white = new Color(255,255,255);
  private Color black = new Color(0,0,0);
  private Color brown2 = new Color(188,120,120);  
  private Color brown = new Color(168,100,100);
  private Color toll = new Color(255,0,155);

  private Color[] lineColors = {Color.blue, Color.cyan, Color.darkGray,
				Color.magenta, Color.orange, 
				Color.green, brown, Color.lightGray,
				Color.pink, Color.gray, streetColor};
  private char[] charColors = new char[numLines];
  private int assignedColors = 0;
 
  /* ============================= */
  public DrawMap(String mapFile) {
  /* ============================= */
    BufferedReader input;

    try {
      numNodes = 0;
      panel = new Board();
      getContentPane().add(panel);
 
      input = new BufferedReader(new FileReader(mapFile));

      // Process first four lines of the file
      gridSize = Integer.parseInt(input.readLine());
      mapWidth = Integer.parseInt(input.readLine());
      mapLength = Integer.parseInt(input.readLine());
      busChanges = Integer.parseInt(input.readLine());

      numNodes = mapWidth * mapLength;
      
      if (mapLength > 15) setSize((2*mapWidth-1)*gridSize+10,(2*mapLength+2)*gridSize);
      else if (mapLength >= 10) setSize((2*mapWidth-1)*gridSize+10,(2*mapLength+1)*gridSize);
      else setSize((2*mapWidth-1)*gridSize+10,(2*mapLength)*gridSize);

      setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
      setVisible(true);
      display = panel.getGraphics();

	  // Draw window
      Thread clock = new Thread();
      clock.sleep(1000);

      readImages();
      drawRoadMap(input);
    }
    catch (InterruptedException e) {
      System.out.println("Error starting program");
    }
    catch (Exception e) {
      System.out.println("Error opening file "+mapFile);
      mapWidth = 1;
      mapLength = 1;
      gridSize = 1;
    }
  }


 /* ================================================================= */
  private void readImages() {
  /* ================================================================= */
      imgs = new BufferedImage[numImages];

      try {
	  for (int i = 1; i <= numImages; ++i) 
	      imgs[i-1] = ImageIO.read(new File("house"+i+".jpg"));
      } catch (IOException e) {
	  imageFiles = false;
      }
  }

 /* ================================================================= */
    private Color roadColor(char c) {
 /* ================================================================= */
	// Assign a color to this bus line
	int i;

	i = 0;
	while ((i < assignedColors) && (charColors[i] != c)) ++i;
	if (i == assignedColors) {
	    if (assignedColors == numLines) return lineColors[0];
	    charColors[assignedColors] = c;
	    ++assignedColors;
	    return lineColors[assignedColors-1];
	}
	return lineColors[i];
    }


 /* ================================================================= */
  public void drawRoadMap(BufferedReader input) {
  /* ================================================================= */
  // Draw streets
     int  i, row = 0;
     String line;
     Color color;

     try {
       map = new char[2*mapLength-1][2*mapWidth-1];
       // Read the map from the file
       for (;;) {
           line = input.readLine();
           if (line == null) {             // End of file
               input.close();
               break;
           }
           for (i = 0; i < line.length(); ++i) 
	       map[row][i] = line.charAt(i);
           ++row;
       }
     }
     catch (Exception e) {
        System.out.println("Error reading input file "+e.getMessage());
        return;
     }

     drawRoads();
  }

 /* ================================================================= */
  public void drawRoads() {
 /* ================================================================= */
     int i, row;
     Color color;

     display.setColor(backColor);
     display.fillRect(0,0,(2*mapWidth-1)*gridSize,(2*mapLength-1)*gridSize);
     display.setColor(backColor);
     display.drawRect(0,0,(2*mapWidth-1)*gridSize,(2*mapLength-1)*gridSize);
     display.drawRect(1,1,(2*mapWidth-1)*gridSize-2,(2*mapLength-1)*gridSize-2);
     display.drawRect(2,2,(2*mapWidth-1)*gridSize-4,(2*mapLength-1)*gridSize-4);
     display.drawRect(3,3,(2*mapWidth-1)*gridSize-6,(2*mapLength-1)*gridSize-6);

     for (row = 0; row < (2*mapLength-1); ++row)
	 if ((row % 2) == 0) { // Horizontal street
           for (i = 0; i < (2*mapWidth-1); ++i)
           /* Draw a row of the map */
	         switch (map[row][i]) {
                  case '0': drawStart(i,row,true); 
		            break;
                  case '1': drawExit(i,row); 
		            break;
                  case ' ': drawBlock(i,row); break;
		  case '+': drawIntersection(i,row); break;
		 default:   color = roadColor(map[row][i]);
		            drawHorRoad(i,row,color);break;
                 }
	 }
	 else { // Vertical street
           for (i = 0; i < (2*mapWidth-1); ++i)
           /* Draw a row of the map */
	         switch (map[row][i]) {
                  case ' ': drawBlock(i,row); break;
		 default:   color = roadColor(map[row][i]);
		            drawVerRoad(i,row,color);break;
                 }
	 }
   }


 /* ================================================================= */
  private void dashedLine(int x1, int y1, int x2, int y2, Color c, int dashSize) {
  /* ================================================================= */
      int i;

      display.setColor(c);
      if (gridSize <= 2*dashSize) display.drawLine(x1,y1,x2,y2);
      else {
	 i = 0; 
         while (((y1 == y2) && ((x1+i) < x2)) ||
		((x1 == x2) && ((y1+i) < y2))) {

             if (y1 == y2) // Horizontal line  
		 if (x1+i+dashSize < x2)
	            display.drawLine(x1+i,y1,x1+i+dashSize,y2);
                 else display.drawLine(x1+i,y1,x2,y2);
             else 
                 if (y1+i+dashSize < y2)
		    display.drawLine(x1,y1+i,x2,y1+i+dashSize);
	         else display.drawLine(x1,y1+i,x2,y2);
             i = i + 2*dashSize;
	 }
      }
  }


 /* Draw a horizontal road */
 /* ================================================================= */
    private void drawHorRoad(int x, int y, Color c) {
  /* ================================================================= */
      display.setColor(c);
      display.fillRect(x*gridSize-gridSize/5,y*gridSize+gridSize/5,
			gridSize+2*gridSize/5,gridSize-2*gridSize/5);
      dashedLine(x*gridSize-gridSize/5,y*gridSize+gridSize/2,
		       x*gridSize+gridSize+gridSize/5,y*gridSize+gridSize/2,white,5);
  }


 /* Draw a vertical road */
 /* ================================================================= */
    private void drawVerRoad(int x, int y, Color c) {
  /* ================================================================= */
      display.setColor(c);
      display.fillRect(x*gridSize+gridSize/5,y*gridSize-gridSize/5,
		       gridSize-2*gridSize/5,gridSize+2*gridSize/5);
      dashedLine(x*gridSize+gridSize/2,y*gridSize-gridSize/5,
		       x*gridSize+gridSize/2,y*gridSize+gridSize+gridSize/5,white,5);
  }


 /* ================================================================= */
  private void drawBlock(int x, int y) {
  /* ================================================================= */
  // Draw a block of houses
      boolean t = true;
      int i;
      if (imageFiles) {
	  i = (int)(Math.floor(Math.random() * numImages));
	  display.drawImage(imgs[i],x*gridSize,y*gridSize,
      			x*gridSize+gridSize,
			y*gridSize+gridSize,1,1,
			imgs[i].getWidth(),imgs[i].getHeight(),null);
      }
      else {
	  display.setColor(backColor);
	  display.fillRect(x*gridSize,y*gridSize,
			   gridSize,gridSize);
      }
  }


/* ================================================================= */
  private void drawIntersection(int x, int y) {
  /* ================================================================= */
  // Draw intersection of two streets
      int x1, x2, y1, y2;
      int basex = x * gridSize;
      int basey = y * gridSize;
	  Color c;


      if ((x > 0) && (map[y][x-1] != ' ')) x1 = basex+gridSize/5;
      else x1 = basex+gridSize/2;
      if ((x < (2*mapWidth-2)) && (map[y][x+1] != ' ')) x2 = basex+4*gridSize/5;
      else x2 = basex+gridSize/2;
      if ((y > 0) && (map[y-1][x] != ' ')) y1 = basey+gridSize/5;
      else y1 = basey+gridSize/2;
      if ((y < (2*mapLength-2)) && (map[y+1][x] != ' ')) y2 = basey+4*gridSize/5;
      else y2 = basey+gridSize/2;
	  
	  if ((y > 0) && (y < (2*mapLength-2)) && (map[y-1][x] == map[y+1][x]) && (map[y-1][x] != ' ')) 
		  c = roadColor(map[y-1][x]);
	  else if ((x > 0) && (x < (2*mapWidth-2)) && (map[y][x-1] == map[y][x+1]) && (map[y][x-1] != ' '))
		  c = roadColor(map[y][x-1]);
	  else if ((y > 0) && (map[y-1][x] != ' ') && (((x>0) && (map[y][x-1] == map[y-1][x]))||
	           ((x < (2*mapWidth-2)) && (map[y][x+1] == map[y-1][x]))))
	      c = roadColor(map[y-1][x]);
	   else if ((y < (2*mapLength-2)) &&(map[y+1][x] != ' ') && (((x > 0) && (map[y][x-1] == map[y+1][x]))||
	           ((x < (2*mapWidth-2)) && (map[y][x+1] == map[y+1][x]))))
		   c = roadColor(map[y+1][x]);
	else if ((y > 0) && (map[y-1][x] != ' ')) c = roadColor(map[y-1][x]);
	else if ((y < (2*mapLength-2)) && (map[y+1][x] != ' ')) c = roadColor(map[y+1][x]);
	else if ((x > 0) && (map[y][x-1] != ' ')) c = roadColor(map[y][x-1]);
	else if ((x < (2*mapWidth-2)) && (map[y][x+1] != ' ')) c = roadColor(map[y][x+1]);
	else c = streetColor;
	  
      display.setColor(c);
      display.fillRect(x*gridSize+gridSize/5,y*gridSize+gridSize/5,
           	       gridSize-2*gridSize/5,gridSize-2*gridSize/5);
	  
      dashedLine(x1,basey+gridSize/2,x2,basey+gridSize/2,white,5);
      dashedLine(basex+gridSize/2,y1,basex+gridSize/2,y2,white,5);
  }

  /* ================================================================= */
  private void drawBus(int x, int y) {
  /* ================================================================= */
  // Draw bus
      int basey = y*gridSize+3*gridSize/8;
      int basex = x*gridSize+gridSize/4;
	  int windowsize = gridSize/15;

      display.setColor(Color.yellow);
      display.fillRoundRect(basex,basey,gridSize/2,gridSize/4,3,3);
      display.setColor(Color.darkGray);
      display.fillRoundRect(basex+7*gridSize/16,basey+1,gridSize/16,gridSize/4-2,2,2);

	  dashedLine(basex+2,basey,basex+7*gridSize/16-2,basey,Color.gray,windowsize);
	  dashedLine(basex+2,basey+gridSize/4-2,basex+7*gridSize/16-2,basey+gridSize/4-2,Color.gray,windowsize);	  
	  dashedLine(basex+2,basey+1,basex+7*gridSize/16-2,basey+1,Color.gray,windowsize);
	  dashedLine(basex+2,basey+gridSize/4-1,basex+7*gridSize/16-2,basey+gridSize/4-1,Color.gray,windowsize);	 

      display.setColor(Color.orange);
      display.fillRoundRect(basex+gridSize/2-3,basey+1,3,gridSize/8-2,2,2);
      display.fillRoundRect(basex+gridSize/2-3,basey+gridSize/8+1,3,gridSize/8-2,2,2);
  }

  /* Draw the starting point */
  /* ================================================================= */
  private void drawStart(int x, int y, boolean bus) {
  /* ================================================================= */
    int basex = x*gridSize;
    int basey = y*gridSize;

    drawIntersection(x,y);

    display.setColor(entranceColor);
    display.fillRect(basex+gridSize/5,basey+gridSize/5,
		     3*gridSize/5,3*gridSize/5);

    for (int i = 0; i < 4; ++i)
       dashedLine(basex+3*gridSize/5+i,basey+gridSize/5,basex+3*gridSize/5+i,
		  basey+4*gridSize/5,Color.yellow,5);

    if (bus) drawBus(x,y);

  }

  /* Draw the destination */
  /* ================================================================= */
  private void drawExit(int x, int y) {
  /* ================================================================= */
    int basex = x*gridSize;
    int basey = y*gridSize;
    int square = 5, r = 0, c;

    drawIntersection(x,y);
    display.setColor(Color.red);
    display.fillOval(basex+gridSize/4,basey+gridSize/4,gridSize/2,gridSize/2);
    display.setColor(white);
	display.fillOval(basex+gridSize/3,basey+gridSize/3,gridSize/3,gridSize/3);
	display.setColor(Color.red);
	display.fillOval(basex+5*gridSize/12,basey+5*gridSize/12,gridSize/6,gridSize/6);
  }

  /* Draws an edge of the solution */
  /* ========================================================== */
  private void drawEdge(int u1, int v1) {
  /* ========================================================== */
  /* Input: edge (uv) */
   
     int x, y, width, height, offset, mapx, mapy, row, i, row2, i2;
     int u, v;
	 Color c;

     if (u1 > numNodes || v1 > numNodes) {
        System.out.println("Invalid edge ("+u1+","+v1+")");
        return;
     }
     offset = gridSize / 2 - 1;
     if (u1 > v1) {u = v1; v = u1;} else {u = u1; v = v1;}

     x = (u % mapWidth)*2*gridSize + offset;
     y = (u / mapWidth)*2*gridSize + offset;

     if (v == (u+1)) { 
       width = gridSize*2;
       height = 3;
       mapx = 2*(u % mapWidth)+1;
       mapy = 2*(u / mapWidth);
       row = mapy;
       row2 = row;
       if (u1 <= v1) {i = mapx - 1; i2 = i + 2;} else {i2 = mapx - 1; i = i2 + 2;}
	   //c = roadColor(map[mapy][mapx]);
       //drawHorRoad(mapx,mapy,c);
     }
     else if (v == (u+mapWidth)) {
       width = 3;
       height = gridSize*2;
       mapx = 2*(u % mapWidth);
       mapy = 2*(u / mapWidth)+1;
       row = mapy - 1;
       i = mapx;
       if (u1 <= v1) {row = mapy - 1; row2 = row + 2;} else {row2 = mapy - 1; row = row2 + 2;};
       i2 = i;
	   //c = roadColor(map[mapy][mapx]);
       //drawVerRoad(mapx,mapy,c);
     }
     else {
        System.out.println("Invalid edge ("+u+","+v+")");
        return;
     }

     switch (map[row][i]) {
                  case '0': drawStart(i,row,false); 
		            break;
                  case '1': drawExit(i,row); 
		            break;
                  case ' ': drawBlock(i,row); break;
 		  case '+': drawIntersection(i,row); 
     }

     if (lx != -1) { // Re-draw the last edge, as it was deleted by the bus
        display.setColor(pathColor);
        display.fillRect(lx,ly,lwidth,lheight);
     }

     display.setColor(pathColor);
     display.fillRect(x,y,width,height);

     drawBus(i2,row2);

     lx = x; ly = y; lwidth = width; lheight = height;
  }


  /* Draws an edge connecting the given nodes */
  /* ==================================== */
  public void drawEdge (Node u, Node v) {
  /* ==================================== */
      if (u != v) drawEdge(u.getName(),v.getName());
  }
}
