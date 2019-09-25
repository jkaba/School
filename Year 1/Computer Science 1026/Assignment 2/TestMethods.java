//CS1026A assignment 2
// Jameel Kaba
// This program tests the 2 methods that I had made
import java.awt.Color;
public class TestMethods
{
  public static void main(String[] args)
  {
    // pick an image
    String fileName = FileChooser.pickAFile();
    // create a picture object for it
    Picture pictureObj = new Picture(fileName);
    // explore the original image
    pictureObj.explore();
    // mirror the image horizontally then vertically
    pictureObj.mirrorMirror();
    // explore the image after it has been mirrored
    pictureObj.explore();
    // pick an image
    String  fileName2 = FileChooser.pickAFile();
    // create a picture object for the image
    Picture pictureObj2 = new Picture(fileName2);
    // explore the image
    pictureObj2.explore();
    // swap the r,g,b values of the image
    pictureObj2.swapColor();
    // explore the image after it has swapped its color values
    pictureObj2.explore();
  }
}
    