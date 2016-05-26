// CS1026A Assignment 3
// Jameel Kaba
// this program uses the crossfade method to make a movie that transitions from one picture to another
import java.awt.Color;
public class FadingMovie
{
  public static void main(String[] args) 
  { 
    
    // select the images to be the starting and ending pictures
    Picture startPic = new Picture("rose.jpg"); 
    Picture endPic = new Picture("whiteFlower.jpg");
    
    // check to see if the images are the same size
    if(startPic.getWidth() == endPic.getWidth() && startPic.getHeight() == endPic.getHeight()) 
    {
      
      // use simple input to obtain the number of cross fades and the directory location
      int numStages = SimpleInput.getIntNumber("Please enter the number of cross fades:"); 
      String directory = SimpleInput.getString("Please enter directory:"); 
      
      // creates a picture array
      Picture[] crossFades = new Picture[numStages + 2];
      
      // creates the frame sequencer
      FrameSequencer frameSequencer = new FrameSequencer(directory); 
      
      // adds the starting picture to the array and to the frame sequencer
      crossFades[0] = startPic; 
      frameSequencer.addFrame(crossFades[0]); 
      
      // determines the fading amount for each intermediate photo 
      double percent = 1/((double)numStages + 1);
      double increment = percent; 
      
      // loop that creates a new photo with the appropriate fade level
      for (int i = 1; i <= numStages; i++) 
      {
        crossFades[i] = new Picture(startPic.getWidth(), startPic.getHeight()); 
        crossFades[i].crossFade(startPic, endPic, percent); 
        frameSequencer.addFrame(crossFades[i]); 
        percent = percent + increment; 
      }
      
      // adds the end picture to the array and the frame sequencer 
      crossFades[numStages + 1] = endPic;
      frameSequencer.addFrame(crossFades[numStages + 1]); 
      
      // plays the movie 
      MoviePlayer fadeMovie = new MoviePlayer(directory + "\\");
      fadeMovie.playMovie(2); 
    }
    else 
    {
      
      // if pictures are not the same size then give an error message      
      SimpleOutput.showInformation("The files selected are not the same size, please try again.");
    }
  }
}