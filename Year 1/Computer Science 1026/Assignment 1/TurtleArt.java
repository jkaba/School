//CS1026A assignment 1
//Jameel Kaba

//This program uses the turtle class to draw a robot head
//The robot's head consists of 3 octagons, 2 squares, and 2 rectangles
//octagons are represented with a color of blue and a pen width of 5 pixels
//squares are represented with a color of red and a pen width of 10 pixels
//rectangles are represented with a color of green and a pen width of 1 pixel

import java.awt.Color;
public class TurtleArt
{
  public static void main (String[] args)
  {
    World worldObj = new World(1000,600);
    Turtle turtle1 = new Turtle(400,300,worldObj);
    //The above codes creates a new World with length of 1000 pixels and height of 600 pixels
    //Inside this world lives a turtle which starts at point 400,300
    turtle1.drawRectangle(100,190);
    //The turtle draws a rectangle that is 100 pixels in width and 190 pixels in height
    turtle1.penUp();
    //The pen up command causes the turtle to lift its pen
    turtle1.moveTo(480,405);
    //The turtle moves to coordinates 480,405
    turtle1.penDown();
    //The pen down command causes the turtle to put its pen back down
    turtle1.setPenColor(Color.RED);
    //The set pen color changes the color of the pen's ink from green to red
    turtle1.setPenWidth(10);
    //set pen width increases the pen width from 1 to 10 pixels
    turtle1.drawSquare(30);
    //The turtle draws a square with width of 30 pixels 
    turtle1.penUp();
    
    turtle1.moveTo(445,345);
    
    turtle1.penDown();
    
    turtle1.setPenColor(Color.GREEN);
    //This changes the pen's color from red to green
    turtle1.setPenWidth(1);
    //This decreases the pen width from 10 pixels to 1 pixel
    turtle1.drawRectangle(40,100);
    
    turtle1.penUp();
    
    turtle1.moveTo(435,330);
    
    turtle1.penDown();
    
    turtle1.setPenColor(Color.BLUE);
    //This changes the pen color from green to blue
    turtle1.setPenWidth(5);
    //This increases the pen width from 1 pixel to 5 pixels
    turtle1.drawOctagon(10);
    //The turtle draws an octoagon which has a length of 10 pixels all around
    turtle1.penUp();
    
    turtle1.moveTo(535,330);
    
    turtle1.penDown();
    
    turtle1.drawOctagon(10);
    
    turtle1.penUp();
    
    turtle1.moveTo(420,275);
    
    turtle1.penDown();
    
    turtle1.setPenWidth(10);
    //This increases the pen width from 5 pixels to 10 pixels
    turtle1.setPenColor(Color.RED);
    //This changes the pen color from blue to red
    turtle1.drawSquare(20);
    
    turtle1.penUp();
    
    turtle1.moveTo(395,250);
    
    turtle1.penDown();
    
    turtle1.setPenWidth(5);
    //This decreases the pen width from 10 pixels to 5 pixels
    turtle1.setPenColor(Color.BLUE);
    //This changes the pen color from red to blue
    turtle1.drawOctagon(30);
    
    turtle1.penUp();
    
    turtle1.moveTo(425,235);
    //The turtle moves into the top octagon to show the robot's head
  }
}