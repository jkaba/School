//CS1026A Assignment 4
//Jameel Kaba
//This class creates a photo with a caption and a watermark
public class LabeledPhoto
{
  //fields//
  //Create instance variables
  private String id;
  private String category;
  private int year;
  private int month;
  private int day;
  private String caption;
  private String photoFile;
  private Picture photoPic;
  
  //constructors//
  //Constructor that creates a new LabeledPhoto object
  public LabeledPhoto(String theId, int theDay, int theMonth, int theYear, String theCategory, String theCaption, String thePhotoFile)
  {
   //Constructor initializes the attributes of the class
    this.id = theId;
    this.day = theDay;
    this.month = theMonth;
    this.year = theYear;
    this.category = theCategory;
    this.caption = theCaption;
    this.photoFile = thePhotoFile;
    
    //Creates a picture object based on the photofile
    Picture sourcePic = new Picture(this.photoFile);
    //Creates a watermark that contains the category and the date
    String wtrMark = this.category + " " + this.day + "/" + this.month + "/" + this.year;
    
    //Creates a new picture object that is slightly taller than the source picture
    photoPic = new Picture(sourcePic.getWidth(), sourcePic.getHeight()+20);
    
    //The new picture is a copy of the source picture, just with some white space for the caption
    photoPic.copyPicture(sourcePic);
    
    //The Caption is written in the space below the picture, in size 10 font, with the watermark in size 20 font
    photoPic.drawCenteredString(this.caption, photoPic.getHeight()-10, 10);
    photoPic.drawInfoWatermark(wtrMark,20);
    
  }
  
  //accessor//
  //Returns the String or int specified when used
  public String getId()
  {
    return this.id;
  }
  public String getCategory()
  {
    return this.category;
  }
  public int getYear()
  {
    return year;
  }
  public int getDay()
  {
    return day;
  }
  public int getMonth()
  {
    return month;
  }
  public String getPhotoFile()
  {
    return this.photoFile;
  }
  public String getCaption()
  {
    return this.caption;
  }
  public Picture getPhotoPic()
  {
    //Creates a copy of the photoPic
    Picture picObj = new Picture(photoPic);
    Picture picNew = new Picture(picObj.getWidth(), picObj.getHeight());
    picNew.copyPicture(picObj);
    //Shows the copied picture
    return picNew;
  }
  
  //modifier//
  //Changes the caption and updates the picture with the new caption
  public void setCaption(String newCaption)
  {
    //Assign the caption string to be the new caption
    caption = newCaption;
    
    //Recreates the picture object but with the new caption
    Picture sourcePic = new Picture(this.photoFile);
    String wtrMark = this.category + " " + this.day + "/" + this.month + "/" + this.year;
    
    photoPic = new Picture(sourcePic.getWidth(), sourcePic.getHeight()+20);
    photoPic.copyPicture(sourcePic);
    
    photoPic.drawCenteredString(this.caption, photoPic.getHeight()-10, 10);
    photoPic.drawInfoWatermark(wtrMark,20);
  }
  
  //Changes the category and updates the picture with the new category
  public void setCategory(String newCategory)
  {
    //Assign the category string to be the new category
    category = newCategory;
    
    //Recreates the picture object but with the new category
    Picture sourcePic = new Picture(this.photoFile);
    String wtrMark = this.category + " " + this.day + "/" + this.month + "/" + this.year;
    
    photoPic = new Picture(sourcePic.getWidth(), sourcePic.getHeight()+20);
    photoPic.copyPicture(sourcePic);
    
    photoPic.drawCenteredString(this.caption, photoPic.getHeight()-10, 10);
    photoPic.drawInfoWatermark(wtrMark,20);
   }
  
  //toString//
   public String toString()
  {
     //Returns the caption, id, and the date (day/month/year)
    return  this.caption + 
           " ( " + this.id +
           ", " + this.category +
           ", " + this.day +"/"+ this.month +"/"+ this.year + " )";
   }
   
   //methods//
   
   //A method to compare the pictures to see which one is older
   public boolean isOlder(LabeledPhoto otherLabeledPhoto)
   {
     //If the year in the first picture is less than the year in the second pic then return true
     if(this.getYear() < otherLabeledPhoto.getYear())
       return true;
     //If the years are equal then compare the months in which the photos were taken
     else if(this.getYear() == otherLabeledPhoto.getYear() && this.getMonth() < otherLabeledPhoto.getMonth())
       return true;
     //If both the years and months are equal then compare the day in which the photos were taken
     else if(this.getYear() == otherLabeledPhoto.getYear() && this.getMonth() == otherLabeledPhoto.getMonth() && this.getDay() < otherLabeledPhoto.getDay())
       return true;
     //If the second picture is younger then return fals
     else
       return false;
   }
   
     //Main Method for testing//
   //Creates two labeled photo objects showing that the accessors, toString, and isOlder methods work
     public static void main(String[] args)
     {
       //Creates a new LabeledPhoto based on the cat_squirrel image
       LabeledPhoto photo = new LabeledPhoto("cat01", 17, 06, 2012, "Pets", "Where's_my_glass_cutter!", "cat_squirrel.jpg");
       
       //Returns the Id
       System.out.println(photo.getId());
       
       //Returns the day
       System.out.println(photo.getDay());
       
       //Returns the month
       System.out.println(photo.getMonth());
       
       //Returns the year
       System.out.println(photo.getYear());
       
       //Returns the category
       System.out.println(photo.getCategory());
       
       //Returns the caption
       System.out.println(photo.getCaption());
       
       //Returns the photo file
       System.out.println(photo.getPhotoFile());
       
       //Returns the labeled image itself
       photo.getPhotoPic().show();
       
       //Returns the toString
       System.out.println(photo.toString());

       
       //Creates a new LabeledPhoto based on the cooldog image and invokes the toString method
       LabeledPhoto photo2 = new LabeledPhoto("dog01", 31, 07, 2012, "Pets", "Cool!__Now_someone_rub_my_tummy", "cooldog.jpg");
       System.out.println(photo2.toString());
       
       //Compares first image with the second image to determine which one is older
       System.out.println(photo.isOlder(photo2));
       
       //Compares the second image with first image to see which one is older
       System.out.println(photo2.isOlder(photo));
     }
}