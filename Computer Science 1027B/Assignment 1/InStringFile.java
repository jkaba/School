import java.io.*;

/**
 * InStringFile makes file reading simpler. It allows
 * information to be read one line at a time from a
 * data file, as a String.
 * @author CS1027
 * @author Jameel Kaba
 * CS1027B Assignment 1
 */

public class InStringFile {
   
  /**
   * the handle to read in the file
   */
  private BufferedReader in;

  /**
   * the next line of the file to be read
   */
  private String nextLine;

  /**
   * Constructs the object that controls file reading
   * Exits gracefullly if file not found or file cannot be read
   * @param filename the name of the file to be read
   */
  public InStringFile(String filename) {   
    try {   	
      in = new BufferedReader(new FileReader(filename));
      nextLine = in.readLine();
    }
    catch (FileNotFoundException ee){
      System.out.println("File " + filename + " not found.");
      System.exit(0);
    }
    catch (IOException e){
      System.out.println("File " + filename + " cannot be read.");
      System.exit(0);
    }
  }

  /**
   * Reads the next line of input as a String
   * Exits gracefully if an error occurs while reading the file
   * @return the next line from the input file
   */ 
  public String read() {
    String current = nextLine;
    try {
      nextLine = in.readLine();
    }
    catch (IOException e){
      System.out.println("File cannot be read.");
      System.exit(0);
    }
    return current;
  }

  /**
   * Lookahead test for end of input
   * @return true if end of file has been reached
   */
  public boolean endOfFile() {
    return (nextLine == null);
  }

  /**
   * Closes the file (making it inaccessible though this InStringFile)
   */
  public void close(){
    try {
      in.close();
      in = null;
    }
    catch (IOException e){
      System.out.println("Problem closing file.");
      System.exit(0);
    }
  }
}

