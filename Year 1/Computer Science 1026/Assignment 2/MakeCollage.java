// CS1026A assignment 2
// Jameel Kaba
// this program creates a collage of an original picture as it undergoes 5 different adjustments
// the original picture is on the left, followed by a different adjustment to the original picture
import java.awt.Color;
public class MakeCollage
{
  public static void main(String[] args)
  {
    // create a canvas of size 1200,300
    Picture canvas = new Picture (1200,300);
    // show the blank canvas
    canvas.show();
    
    // choose the original picture
    String fileName = FileChooser.pickAFile();
    // reference it by pictureObj
    Picture pictureObj = new Picture(fileName);
    // place it on the canvas at 0,0
    canvas.copyPictureTo(pictureObj,0,0);
    // show the canvas with the picture on it
    canvas.repaint();
    
    // create a new picture object for the original image
    Picture pictureObj2 = new Picture(fileName);
    // mirror the image horizontally then vertically
    pictureObj2.mirrorMirror();
    // place the picture beside the original
    canvas.copyPictureTo(pictureObj2,200,0);
    // show the canvas with the added picture
    canvas.repaint();
    
    // create a new picture object for the original image
    Picture pictureObj3 = new Picture(fileName);
    // swap the r,g,b values of the image 
    pictureObj3.swapColor();
    // add the picture to the canvas
    canvas.copyPictureTo(pictureObj3,400,0);
    // show the canvas with the added picture
    canvas.repaint();
    
    // create a new picture object for the original image
    Picture pictureObj4 = new Picture(fileName);
    // reduce the blue and red values to 0
    pictureObj4.clearBlueAndRed();
    // mirror the image vertically and then horizontally bottom to top
    pictureObj4.mirrorMirror2();
    // place the picture on the canvas
    canvas.copyPictureTo(pictureObj4,600,0);
    // show the canvas with the added picture
    canvas.repaint();
    
    // create a new picture object for the original image
    Picture pictureObj5 = new Picture(fileName);
    // reduce the blue and green values to 0
    pictureObj5.clearBlueAndGreen();
    // add the picture to the canvas
    canvas.copyPictureTo(pictureObj5,800,0);
    // show the canvas with the added picture
    canvas.repaint();
    
    // create a new picture object for the original image
    Picture pictureObj6 = new Picture(fileName);
    // reduce the red and green values to 0
    pictureObj6.clearRedAndGreen();
    // mirror the image vertically and then horizonatally
    pictureObj6.mirrorMirror();
    // add the picture to the canvas
    canvas.copyPictureTo(pictureObj6,1000,0);
    // show the canvas with all the pictures on it
    canvas.repaint();
    
    // save the picture to the hard drive in a pictures folder that is available to all users on the computer
    canvas.write("C:/Users/Public/Pictures/myCollage.jpg");
  }
}
