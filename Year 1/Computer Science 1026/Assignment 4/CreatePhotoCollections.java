//CS1026A Assignment 4
//Jameel Kaba
//this program creates a photo collection
import java.util.*;
import java.io.*;
public class CreatePhotoCollections
{
  public static void main(String[] args)
  {
    //use simple input to get the text file that contains the photo info
    String fileName = SimpleInput.getString("Enter the filename of the photo information file: ");
    
    //use simple input to get the directory name
    String directory = SimpleInput.getString("Enter the name of the directory: ");
    
    //creates a new photo collection
    PhotoCollection photoCollection = new PhotoCollection(fileName);
    
    //lists the photo information
    photoCollection.listPhotoInformation();
    
    //sorts the photos by date (from newest to oldest)
    photoCollection.sortPhotosByDate();
    
    //lists the photo information in the new order
    photoCollection.listPhotoInformation();
    
    //shows the images
    photoCollection.showPhotos();
    
    //shows the images in the pets category
    photoCollection.showPhotos("Pets");
    
    //saves the labeled photos in the directory
    photoCollection.storePhotos(directory);
  }
}