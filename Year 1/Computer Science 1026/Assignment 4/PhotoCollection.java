//CS1026A Assignment 4
//Jameel Kaba
//This class provides the basic structure to make a photo collection
import java.util.*;
import java.io.*;
public class PhotoCollection
{
  
//fields//
  //Create instance variables
  private LabeledPhoto[] photoArray;
  private int numPhoto = 0;
  
//constructor//
  //Constructor that creates a photo collection after reading the information from the fileName
  public PhotoCollection(String fileName)
  {
    //Create a simple reader to read the information file
    SimpleReader reader = new SimpleReader(fileName);
    //Create a string array to place each line from the file
    String[] stringArray = reader.readFile();
    //Make the photo array the length of the text in fileName
    numPhoto = reader.getFileLength();
    photoArray = new LabeledPhoto[numPhoto];
    //Use a for loop to create a String Tokenizer
    for (int i = 0; i < numPhoto; i++)
    {
      //Use StringTokenizer to get the information for the labeled photo's
      StringTokenizer tokenizer = new StringTokenizer(stringArray[i]);
      String id = tokenizer.nextToken();
      
      String sday = tokenizer.nextToken();
      //Convert the text to an int
      int day = Integer.parseInt(sday);
      
      String smonth = tokenizer.nextToken();
      //Convert the text to an int
      int month = Integer.parseInt(smonth);

      String syear = tokenizer.nextToken();
      //Convert the text to an int
      int year = Integer.parseInt(syear);
      
      String category = tokenizer.nextToken();
      String tempCaption = tokenizer.nextToken();
      //Replace the _ in the captions into a " "
      String caption = tempCaption.replace("_", " ");
      String photoFile = tokenizer.nextToken();
      
      //Create the labeled photo based off the information recieved in the stringtokenizer
      LabeledPhoto photo = new LabeledPhoto(id, day, month, year, category, caption, photoFile);
      photoArray[i] = photo;
    }
  }
  
    //methods//
  //Method to list the information from the photos
    public void listPhotoInformation()
    {
      for (int i = 0; i < photoArray.length; i++)
      {
        //Prints out information based on the toString method from labeled photo
        System.out.println(photoArray[i]);
      }
    }
    
    //Method to show the labeled photos
    public void showPhotos()
    {
      for (int i = 0; i < numPhoto; i++)
      {
        //Shows the labeled photos in the array
        Picture picture = photoArray[i].getPhotoPic();
        picture.show();
      }
    }
    
    //Method to show the labeled photos that belong to a specific category
    public void showPhotos(String theCategory)
    {
      for(int i = 0; i < numPhoto; i++)
      {
        //Checks to see if the labeled photo fits into the category
        if (this.photoArray[i].getCategory().equals(theCategory))
        {
          //If it does then it shows the picture
          Picture picture = photoArray[i].getPhotoPic();
          picture.show();
        }
      }
    }
    
    //Method saves the labeled images in the directory
    public void storePhotos(String directory)
    {
      //Checks the directory
      char end = directory.charAt(directory.length()-1);
      //Checks to see if the directory ends in either / or \\ if it doesn't then it adds a / to the end 
      if (end != '/' || end != '\\')
        directory = directory + '/';
      //Creates a file object called directoryFile
      File directoryFile = new File(directory);
      //Checks to see if directoryFile exists
      if (!directoryFile.exists())
        directoryFile.mkdirs();
      for(int i =0; i < photoArray.length; i++)
      {
        //Gets the labeled photo
        Picture picture = photoArray[i].getPhotoPic();
        //Saves the labeled photo in the directory
        picture.write(directory + photoArray[i].getId() + "_" + photoArray[i].getCategory() + ".jpg");
      }
    }
    
    //Method that sorts out the photos by the date they were taken (from newest to oldest)
    public void sortPhotosByDate()
    {
      //When boolean is true swap the photos
      boolean flag = true;
      LabeledPhoto swap;
      
      while(flag)
      {
        flag = false;
        for(int i = 0; i < numPhoto-1; i++)
        {
          //If the photo is is older than swap it with the photo it was compared witb
          if (this.photoArray[i].isOlder(this.photoArray[i+1]))
          {
            swap = this.photoArray[i];
            this.photoArray[i] = this.photoArray[i+1];
            this.photoArray[i+1] = swap;
            flag = true;
          }
        }
      }
    }
}



  

      