//CS1026A assignment 1
//Jameel Kaba

/**
 * Class that represents a turtle which is similar to a Logo turtle.
 * This class inherts from SimpleTurtle and is for students
 * to add methods to.
 *
 * Copyright Georgia Institute of Technology 2004
 * @author Barb Ericson ericson@cc.gatech.edu
 */
public class Turtle extends SimpleTurtle
{
  ////////////////// constructors ///////////////////////
  
  /** Constructor that takes the x and y and a picture to
   * draw on
   * @param x the starting x position
   * @param y the starting y position
   * @param picture the picture to draw on
   */
  public Turtle (int x, int y, Picture picture) 
  {
    // let the parent constructor handle it
    super(x,y,picture);
  }
  
  /** Constructor that takes the x and y and a model
   * display to draw it on
   * @param x the starting x position
   * @param y the starting y position
   * @param modelDisplayer the thing that displays the model
   */
  public Turtle (int x, int y, ModelDisplay modelDisplayer) 
  {
    // let the parent constructor handle it
    super(x,y,modelDisplayer);
  }
  
  /** Constructor that takes the model display
   * @param modelDisplay the thing that displays the model
   */
  public Turtle (ModelDisplay modelDisplay) 
  {
    // let the parent constructor handle it
    super(modelDisplay);
  }
  
  /**
   * Constructor that takes a picture to draw on
   * @param p the picture to draw on
   */
  public Turtle (Picture p)
  {
    // let the parent constructor handle it
    super(p);
  }  
  
  /////////////////// methods ///////////////////////

  //Method to draw a square of a specified width:
  //the turtle starts at the top left corner of square
  //and ends where it started, facing the same way
  public void drawSquare(int width)
  {
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(width);
  }
 
  public void drawVee (int length)
  {
    this.turn(-30);
    this.forward(length);
    this.turn(180);
    this.forward(length);
    this.turn(-120);
    this.forward(length);
    this.turn(180);
    this.forward(length);
    this.turn(150);
  }
  //Method to draw a rectangle of specified width and height
  //turtle starts at top left corner of the rectangle
  //and ends where it started facing the same direction
  public void drawRectangle (int width, int height)
  {
    this.turnRight();
    this.forward(height);
    this.turnRight();
    this.forward(width);
    this.turnRight();
    this.forward(height);
    this.turnRight();
    this.forward(width);
  }
  //Method to draw an octagon of specified length
  //turtle starts and ends off in the same point and same direction 
  public void drawOctagon (int length)
  {
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
    this.forward(length);
    this.turn(45);
  }
} // end of class Turtle, put all new methods before this