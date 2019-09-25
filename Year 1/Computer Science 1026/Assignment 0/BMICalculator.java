// CS1026A Assignment 0
// Jameel Kaba
// This prgram asks for the user's name, weight in pounds, and their height in inches.
// Once the info is recieved the calculator converts the user's weight into kilograms, and their height into meters.
// The program calculates the user's BMI based on the information recieved.

public class BMICalculator
{
  public static void main(String[] args)
  {
    String myName = SimpleInput.getString("What is your name?");
    
    double weight = SimpleInput.getNumber("What is your weight in pounds?");
    
    double height = SimpleInput.getNumber("What is your height in inches?");
    // Lines 11, 13, and 15 use simple input to obtain the user's name, their weight in pounds, and height in inches.
    
    double KILOGRAMS_PER_POUND = 0.453592;
    
    double METER_PER_INCH = 0.0254;
    
    double weightInKilograms = weight * KILOGRAMS_PER_POUND;
    
    double heightInMeters = height * METER_PER_INCH;
    // Lines 22 and 24 convert the user's weight from pounds to kilograms and height from inches to meters.
    // Lines 18 and 20 are the conversion rates for pounds to kilograms andd inches to meters.
    
    int BMI =  (int)weightInKilograms / ((int)(heightInMeters)^2);
    // Line 28 is the formula used to calculate the BMI based on the user's information which is converted and then plugged into the formula.
    
    SimpleOutput.showInformation("Hello: " + myName + "\nWeight in Kilograms " + weightInKilograms + 
                                 
                                 "\nHeight in meters " + heightInMeters + 
                                 
                                 "\nYour BMI is " + BMI + 
                                 
                                 "\n\nThe normal range for a BMI is 18.5 to 25");
    // Lines 31-37 is the code for the output display. This code uses many strings, and new lines, to split the display on new lines.
    // The words in the code that aren't in code are ther values that have been calculated based on the user's input.
    
  }
}