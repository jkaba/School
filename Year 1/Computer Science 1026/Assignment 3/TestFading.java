// CS1026A Assignment 3
// Jameel Kaba
// this program tests the cross fade method
import java.awt.Color;
public class TestFading
{
  public static void main(String[] args)
  {
    // set the start pic and end pic as pictures from the working directory
    Picture startPicture = new Picture("rose.jpg");
    Picture endPicture = new Picture("whiteFlower.jpg");
    
    // create three new pictures to be the same size as the starting picture
    Picture p1 = new Picture(startPicture.getWidth(), startPicture.getHeight());
    Picture p2 = new Picture(startPicture.getWidth(), startPicture.getHeight());
    Picture p3 = new Picture(startPicture.getWidth(), startPicture.getHeight());
    
    // perform the crossfade method on the three new pictures, using a different percentage each time
    p1.crossFade(startPicture, endPicture, 0.25);
    p2.crossFade(startPicture, endPicture, 0.5);
    p3.crossFade(startPicture, endPicture, 0.75);
    
    // explore the five total pictures to see the difference between them
    startPicture.explore();
    p1.explore();
    p2.explore();
    p3.explore();
    endPicture.explore();
  }
}