import java.awt.*;
import java.awt.font.*;
import java.awt.geom.*;
import java.text.*;

/**
 * A class that represents a picture.  This class inherits from 
 * SimplePicture and allows the student to add functionality to
 * the Picture class.  
 * 
 * Copyright Georgia Institute of Technology 2004-2005
 * @author Barbara Ericson ericson@cc.gatech.edu
 */
public class Picture extends SimplePicture 
{
  ///////////////////// constructors //////////////////////////////////
  
  /**
   * Constructor that takes no arguments 
   */
  public Picture ()
  {
    /* not needed but use it to show students the implicit call to super()
     * child constructors always call a parent constructor 
     */
    super();  
  }
  
  /**
   * Constructor that takes a file name and creates the picture 
   * @param fileName the name of the file to create the picture from
   */
  public Picture(String fileName)
  {
    // let the parent class handle this fileName
    super(fileName);
  }
  
  /**
   * Constructor that takes the width and height
   * @param width the width of the desired picture
   * @param height the height of the desired picture
   */
  public Picture(int width, int height)
  {
    // let the parent class handle this width and height
    super(width,height);
  }
  
  /**
   * Constructor that takes a picture and creates a 
   * copy of that picture
   */
  public Picture(Picture copyPicture)
  {
    // let the parent class do the copy
    super(copyPicture);
  }
  
  ////////////////////// methods ///////////////////////////////////////
  
  /**
   * Method to return a string with information about this picture.
   * @return a string with information about the picture such as fileName,
   * height and width.
   */
  public String toString()
  {
    String output = "Picture, filename " + getFileName() + 
      " height " + getHeight() 
      + " width " + getWidth();
    return output;
    
  }

  /*****************************************************************
   * Method to mirror a piece of the temple
   *****************************************************************/
  public void mirrorTemple(){
    //Declare local variables
    int mirrorPoint = 276;
    Pixel leftPix = null;
    Pixel rightPix = null;
    
    //Loop through all rows, where the temple must be mirrored
    for (int y=27;y<97;y++){
      for (int x=13; x<mirrorPoint; x++){
        leftPix = getPixel(x,y); //get left pixel (good pixel)
        //Get right pixel (the mirror location)
        rightPix = getPixel(mirrorPoint + (mirrorPoint-x),y);
        //Swap the colours
        rightPix.setColor(leftPix.getColor());
      }
    }
  }
  

  /*****************************************************************
   * Mirror a picture vertically
   *****************************************************************/
  public void mirrorVertical(){
    //Declare local variables
    int width = this.getWidth();
    int mirrorPoint = width/2;
    Pixel leftPix = null;
    Pixel rightPix = null;
    
    //Loop through all rows, only half way
    for (int y=0;y<this.getHeight();y++){
      for (int x=0; x<mirrorPoint; x++){
        leftPix = getPixel(x,y);
        rightPix = getPixel(width-1-x,y);
        rightPix.setColor(leftPix.getColor()); //Swap colours of left and right
      }
    }  
  }
  public void mirrorHorizontal()
  {
    int height = this.getHeight();
    int mirrorPoint = height / 2;
    Pixel topPixel = null;
    Pixel bottomPixel = null;
    for (int x=0; x<this.getWidth(); x++)
    {
      for (int y=0; y < mirrorPoint; y++)
      {
        topPixel = getPixel(x,y);
        bottomPixel = getPixel(x, height - 1 - y);
        bottomPixel.setColor(topPixel.getColor());
      }
    }
  }

  /*****************************************************************
   * Method to make a picture greyscale
   *****************************************************************/
  public void goodGrey(){
    //Declare local variables; get an array of pixels out of the picture
    Pixel[] pixelArray = this.getPixels();
    Pixel pix = null;
    int luminance = 0;
    double redV = 0;
    double blueV= 0;
    double greenV= 0;
    
    //Loop through all pixels in the array
    for (int i=0; i<pixelArray.length;i++){
      pix = pixelArray[i];
      redV = pix.getRed() * 0.299;
      blueV = pix.getBlue() * 0.587;
      greenV = pix.getGreen() * 0.114;
      luminance = (int)(redV + greenV + blueV);
      //Change pixel colour to the new colour created using luminance
      pix.setColor(new Color(luminance, luminance, luminance));
    }
  }
  
/***************************************
** Copy picture ***
****************************************/

public void copyPicture (Picture sourcePicture) 
{ 
   Pixel sourcePixel = null; 
   Pixel targetPixel = null; 
   // loop through the columns 
   for (int sourceX = 0, targetX = 0; 
        sourceX < sourcePicture.getWidth(); 
sourceX++, targetX++)    
   {    // loop through the rows 
     for (int sourceY = 0, targetY = 0; 
          sourceY < sourcePicture.getHeight(); 
sourceY++, targetY++)    
     { 
       // set the target pixel color to the source pixel color 
       sourcePixel = sourcePicture.getPixel(sourceX,sourceY); 
       targetPixel = this.getPixel(targetX,targetY); 
       targetPixel.setColor(sourcePixel.getColor()); 
     } 
   } 
 }


/**
  * Modified version of method from page 154 of the textbook for copying pictures
  */

 public void copyPictureTo(Picture sourcePicture, int xStart, int yStart)
 {
   Pixel sourcePixel = null;
   Pixel targetPixel = null;
   
   //loop through the columns
   
   for (int sourceX = 0, targetX = xStart;
        sourceX < sourcePicture.getWidth();
        sourceX++, targetX++)
   {
     //loop through the rows
     for (int sourceY = 0,
          targetY = yStart;
          sourceY < sourcePicture.getHeight();
          sourceY++, targetY++)
     {
       sourcePixel = sourcePicture.getPixel(sourceX,sourceY);
       targetPixel = this.getPixel(targetX,targetY);
       targetPixel.setColor(sourcePixel.getColor());
     } 
   }
  
} 


/****************************
Crop picture
*****************************/
public void copyPictureTo(Picture sourcePicture, int startX, int startY,  
                           int endX, int endY, int targetStartX, int targetStartY) 
  { 
    Pixel sourcePixel = null; 
    Pixel targetPixel = null; 
    // loop through the x values 
    for (int x = startX, tx = targetStartX;  x < endX && x < sourcePicture.getWidth() && tx < this.getWidth();  x++, tx++) 
    { 
      // loop through the y values 
      for (int y = startY, ty = targetStartY; y < endY && y < sourcePicture.getHeight() &&  ty < this.getHeight();  y++, ty++)  
      {

// copy the source color to the target color 
        sourcePixel = sourcePicture.getPixel(x,y); 
        targetPixel = this.getPixel(tx,ty); 
        targetPixel.setColor(sourcePixel.getColor()); 
      } 
    } 
  }
  
  /*****************************************************************
   * Method to make a negative of a picture
   *****************************************************************/
  public void negate(){
    //Local variables
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int redV, blueV, greenV = 0;
    //Loop through all pixels in the picture
    for (int i=0; i<pixelArray.length;i++){
      pixel = pixelArray[i];
      redV=pixel.getRed();
      greenV=pixel.getGreen();
      blueV = pixel.getBlue();
      //Set the color to the negative of current color
      pixel.setColor(new Color(255-redV, 255-greenV, 255-blueV));
    }
  }
  
  
  /*****************************************************************
   * Method to create a fake sunset
   *****************************************************************/
  public void makeSunset(){
    //Create local variables and get array of pixels
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int value = 0;
    int i=0;
    
    //Loop through all pixels
    while (i<pixelArray.length){
      pixel = pixelArray[i]; //get out current picture
      value = pixel.getBlue(); //get the blue value
      pixel.setBlue((int)(value*0.7)); //set a new blue
      value = pixel.getGreen(); //get the green value
      pixel.setGreen((int)(value*0.7)); //set the new green value
      i++; //increment counter
    }
  }

  /*****************************************************************
   * Method to decrease the red in a picture
   *****************************************************************/
  public void decreaseRed(){
    //Declare variables and get an array with all the pixels
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int value = 0;
    int index = 0;
    //Loop through all pixels
    while (index < pixelArray.length){
      pixel = pixelArray[index]; //get pixel at each spot in the array in turn
      value = pixel.getRed(); //get the red value
      value=(int)(value*0.5); //change the red value by half
      pixel.setRed(value); //set a new red value
      index= index + 1; //increment so next time you get new pixel
    }
  }
  
  public void changeRed(double amount)
  {
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int value = 0;
    int index = 0;
    for (index = 1; index <= pixelArray.length; index++)
    {
      pixel = pixelArray[index];
      value = pixel.getRed();
      value = (int)(amount);
      pixel.setRed(value);
      index = index + 1;
    }
  }
  
    public void clearBlue2()
  {
    Pixel pixelObj;
    // loop through the columns (x direction)
    for (int x = 0; x < this.getWidth(); x++)
           {
      // loop through the rows (y direction)
      for (int y = 0; y < this.getHeight(); y++)
      {
        // get pixel at the x and y location
        pixelObj = this.getPixel(x,y);
        // set its blue to 0
        pixelObj.setBlue(0);
      }
    }
    }
    
      // original method //
     public void mirrorMirror()
      {
        // set reference variables
        int height = this.getHeight();
        int width = this.getWidth();
        int mirrorPoint1 = height / 2;
        int mirrorPoint2 = width / 2;
        Pixel topPixel = null;
        Pixel bottomPixel = null;
        Pixel leftPixel = null;
        Pixel rightPixel = null;
        // loop through the columns when x is less than the width or when x is less than the second mirror point
        for (int x=0; x < this.getWidth() || x < mirrorPoint2; x++)
        {
          // loop through the rows when y is less than the first mirrorpoint or when y is less than the height
          for (int y = 0; y < mirrorPoint1 || y < this.getHeight(); y++)
              {
            // get the pixel from the top and set the bottom pixels to image the top pixels
            topPixel = getPixel(x,y);
            bottomPixel = getPixel(x, height - 1- y);
            bottomPixel.setColor(topPixel.getColor());
            // get the pixel from the right and set the left pixels to image the right pixels
            rightPixel = getPixel(x,y);
            leftPixel = getPixel (width -1 - x, y);
            leftPixel.setColor(rightPixel.getColor());
          }
        }
     }
      
      // original method //
        public void swapColor()
        {
          // create the local reference variables
          Pixel[] pixelArray = this.getPixels();
          Pixel pixel = null;
          int value = 0;
          int value2 = 0;
          int value3 = 0;
          int i = 0;
          // loop theough all the pixels
          while (i<pixelArray.length)
          {
            pixel = pixelArray[i];
            // get the blue values from the pixels
            value = pixel.getBlue();
            // get the green values from the pixels
            value2 = pixel.getGreen();
            // get the red values from the pixels
            value3 = pixel.getRed();
            // swap the blue values to make them equal to the red values
            pixel.setBlue(value3);
            // swap the green values to make them equal to the blue values
            pixel.setGreen(value);
            // swap the red values to make them equal to the green values
            pixel.setRed(value2);
            // increase the counter
            i++;
          }
        }
  
  public void mirrorMirror2()
  {
    // set the reference variables
    int height = this.getHeight();
    int width = this.getWidth();
    int mirrorPoint1 = height / 2;
    int mirrorPoint2 = width / 2;
    Pixel topPixel = null;
    Pixel bottomPixel = null;
    Pixel leftPixel = null;
    Pixel rightPixel = null;
    // loop through the rows
    for (int y = 0; y < this.getHeight(); y++)
    {
      // loop from 0 to the mirror point (middle)
      for (int x = 0; x < mirrorPoint2; x++)
      {
        // get the right pixels and set the left pixels to image the right pixels
        rightPixel = getPixel(x,y);
        leftPixel = getPixel (width -1 - x, y);
        leftPixel.setColor(rightPixel.getColor());
      }
    }
    // loop through the columns
    for (int x=0; x<this.getWidth(); x++)
    {
      // loop from 0 to the mirror point
      for (int y = 0; y < mirrorPoint1; y++)
      {
        // get the bottom pixels and set the top pixels to image the bottom pixels
        topPixel = getPixel(x,y);
        bottomPixel = getPixel(x, height - 1- y);
        topPixel.setColor(bottomPixel.getColor());
      }
    }
  }
  
  public void clearBlueAndGreen()
    {
      Pixel pixelObj;
      // loop through the columns (x direction)
      for (int x = 0; x < this.getWidth(); x++)
      {
        // loop through the rows (y direction)
        for (int y = 0; y < this.getHeight(); y++)
        {
          // get pixel at the x and y location
          pixelObj = this.getPixel(x,y);
          //set its blue value to 0
          pixelObj.setBlue(0);
          //set its green value to 0
          pixelObj.setGreen(0);
        }
      }
    }
     public void clearGreen(){
    //Declare variables and get an array with all the pixels
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int value = 0;
    int index = 0;
    //Loop through all pixels
    while (index < pixelArray.length){
      pixel = pixelArray[index]; //get pixel at each spot in the array in turn
      value = pixel.getGreen(); //get the green value
      pixel.setGreen(0); //set green value at 0
      index= index + 1; //increment so next time you get new pixel
    }
     }                     
     public void clearBlueAndRed()
    {
      Pixel pixelObj;
      // loop through the columns (x direction)
      for (int x = 0; x < this.getWidth(); x++)
      {
        // loop through the rows (y direction)
        for (int y = 0; y < this.getHeight(); y++)
        {
          // get the pixels location at x and y
          pixelObj = this.getPixel(x,y);
          // set its blue value to 0
          pixelObj.setBlue(0);
          // set its red value to 0
          pixelObj.setRed(0);
        }
      }
     }
    public void clearRedAndGreen()
    {
      Pixel pixelObj;
      // loop through the columns (x direction)
      for (int x = 0; x < this.getWidth(); x++)
      {
        // loop through the rows (y direction)
        for (int y = 0; y < this.getHeight(); y++)
        {
          // get the pixels location at x and y
          pixelObj = this.getPixel(x,y);
          // set its red value to 0
          pixelObj.setRed(0);
          // set its green value to 0
          pixelObj.setGreen(0);
        }
      }
    }
    
    public void clearRed(){
    //Declare variables and get an array with all the pixels
    Pixel[] pixelArray = this.getPixels();
    Pixel pixel = null;
    int value = 0;
    int index = 0;
    //Loop through all pixels
    while (index < pixelArray.length){
      pixel = pixelArray[index]; //get pixel at each spot in the array in turn
      pixel.setRed(0); //set red value at 0
      index= index + 1; //increment so next time you get new pixel
    }
      }
       
    public void copyExceptWhite(Picture sourcePicture, int xStart, int yStart)
 {
      Pixel sourcePixel = null;
      Pixel targetPixel = null;
   
      //loop through the columns
   
      for (int sourceX = 0, targetX = xStart;
           sourceX < sourcePicture.getWidth();
           sourceX++, targetX++)
      {
        //loop through the rows
        for (int sourceY = 0,
             targetY = yStart;
             sourceY < sourcePicture.getHeight();
             sourceY++, targetY++)
        {
          Color white = new Color(255,255,255);
          sourcePixel = sourcePicture.getPixel(sourceX,sourceY);
          if (sourcePixel.getRed() !=255 
             || sourcePixel.getGreen()!=255
             || sourcePixel.getBlue() !=255)
          {
          targetPixel = this.getPixel(targetX,targetY);
          targetPixel.setColor(sourcePixel.getColor());
        } 
      }
  
    }   
    }   
    
    public void blueExtremes()
    {
      Pixel pixelObj;
      int blueValue = 0;
      for (int x = 0; x< this.getWidth(); x++){
        for (int y=0; y<this.getHeight(); y++){
          pixelObj = this.getPixel(x,y);
          blueValue = pixelObj.getBlue();
          if(blueValue >= 128)
            pixelObj.setBlue(255);
          else 
            pixelObj.setBlue(0);
        }
      }
    }
            
// CS1026A Assignment 3
// Jameel Kaba
// This method blends two photos together
    public void crossFade(Picture startPicture, Picture endPicture, double percentEndPic)
    {
      // set an array to ocntain the pixels of the target picture
      Pixel[] targetPixel = this.getPixels();
      
      // set an array to contain the pixels of the starting picture
      Pixel[] startPixel = startPicture.getPixels();
      
      // set an array to contain the pixels of the ending picture
      Pixel[] endPixel = endPicture.getPixels();
      
      // make the pixel's named target, start, and end become null
      Pixel target = null;
      Pixel start = null;
      Pixel end = null;
      
      // use an if statement to see if the starting picture and ending picture are the same height and width
      if (startPicture.getWidth() == endPicture.getWidth() && startPicture.getHeight() == endPicture.getHeight())
      {
        
        // use a for loop to loop through all the pixels
        for (int i = 0; i < targetPixel.length; i++)
        {
          
          // set the target pixels, start pixels, and end pixels to i
          target = targetPixel[i];
          start = startPixel[i];
          end = endPixel[i];
          
          // set the r,g,b values for the target picture 
          target.setRed((int)(start.getRed() + (end.getRed() - start.getRed()) * percentEndPic));
          target.setGreen((int)(start.getGreen() + (end.getGreen() - start.getGreen()) * percentEndPic));
          target.setBlue((int)(start.getBlue() + (end.getBlue() - start.getBlue()) * percentEndPic));
        }
      }
    }
 
    
//CS1026 Assignment 4
//Jameel Kaba
    
//This method creates a centered string  based on the text info
//Placing it in the desired y position
//And written in the desired font size
    public void drawCenteredString(String text, int yPos, int fontSize){
    Graphics2D g = (Graphics2D)this.getGraphics();
    
    g.setFont(new Font("Arial",Font.BOLD,fontSize));
    g.setColor(Color.BLACK);
    int stringLen = (int) g.getFontMetrics().getStringBounds(text, g).getWidth();  
    int xPos = this.getWidth()/2 - stringLen/2;  
    
    g.drawString(text, xPos, yPos);
  }
  
//This method creates a watermark based on the text information, written in a desired font size
    public void drawInfoWatermark(String text, int fontSize){
    
    //Get the graphics object of this image
    Graphics2D g = (Graphics2D)this.getGraphics();
    
    //Set up transparency (alpha channel)
    AlphaComposite alpha = AlphaComposite.getInstance(AlphaComposite.SRC_OVER,0.5f);
    g.setComposite(alpha);
    g.setColor(Color.white);  
    g.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);  
    
    //Font setup
    g.setFont(new Font("Arial", Font.ITALIC, fontSize));   
    
    //use a pad at the edge
    final int PAD = 20;
    int stringLen = (int) g.getFontMetrics().getStringBounds(text, g).getWidth();  
    int stringHeight = (int) g.getFontMetrics().getStringBounds(text, g).getHeight();
    //write text onto the image
    g.drawString(text, this.getWidth()-stringLen-PAD, this.getHeight()-stringHeight);  
  }
} // end of class Picture, put all new methods before this

 