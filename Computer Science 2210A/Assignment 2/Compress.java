/**
 * CS2210A Assignment 2
 * Jameel Kaba (jkaba) Student #: 250796017
 * 
 * Compression class that takes a file from argument 0 and compresses it
 */

// import statements
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;


public class Compress {

	public static void main(String[] args){

		// Check how many arguments are passed
		if (args.length < 1){

			// If more than 1 argument then print an error statement
			System.out.println("Wrong Number of Arguments: TRY AGAIN");
			return;
		}

		// Create a Dictionary of size 4099
		Dictionary compress = new Dictionary(4099);

		try{

			// for i from 0 to 255 incremenet i
			for (int i=0; i<256; i++){

				// Create an empty string
				String newWord = "";

				// cast the int i to a character and append it to the string
				newWord = newWord + (char)i;			

				// Creates a dictionary entry consisting of the word and the code i
				// Insert this dictionary entry into the dictionary
				compress.insert(new DictEntry(newWord, i)); 
			}
		}

		// Catch a Dictionary Exception if the dictionary is not created
		catch (DictionaryException e){

			// Print an error message for the user
			System.out.println("Failed to create dictionary: TRY AGAIN");
			return;
		}

		// initialize a BufferedInputStream and BufferedOutputStream
		BufferedInputStream input;
		BufferedOutputStream outputFile;

		try {
			// Set the BufferedInputStream to take the input from the file in argument 0
			input = new BufferedInputStream(new FileInputStream(args[0]));
		} 

		// Catch a FileNotFoundException if the input file can't be opened
		catch (FileNotFoundException e) {

			// Print an error message for the user
			System.out.println("Input file not found: TRY AGAIN");
			return;
		}

		try {
			// Set the BufferedOutputStream to set the output to the file 
			// in argument 0 with a .zzz extension
			outputFile = new BufferedOutputStream(new FileOutputStream(args[0] + ".zzz"));
		} 

		// Catch a FileNotFoundException if the output file can't be created
		catch (FileNotFoundException e) {

			// Print an error message for the user
			System.out.println("The output file can not be created: TRY AGAIN");
			return;
		}

		// Make a new blank string
		String inputWord = "";

		try {
			//Read each byte in the input file
			while (input.available() > 0){

				// cast the int returned by the read method to a char and append it into the new word
				inputWord = inputWord + (char)input.read();
			}
		} 

		// Catch an IOException if there is an error reading the bytes
		catch (IOException e) {

			// Print an error message for the user
			System.out.println("Error cannot initialize characters: TRY AGAIN");
			return;
		}

		// initialize a counter called position to 0
		int position = 0;

		// while the value of position is less than the length of the word from input
		while (position < inputWord.length()){ 

			// Initialize two strings one for check and one for output
			String check = "";	
			String outputWord = "";	

			// append the the first character that hasn't been processed
			check = check + inputWord.charAt(position);	

			// while the check string is found in the dictionary
			while (compress.find(check) != null){

				// set the output string to the string check references
				outputWord = check;	

				// if the string has not been fully processed 
				if (position < inputWord.length()-1){ 

					// append the next character to the check string
					check = check + inputWord.charAt(++position); 
				}

				else{ 

					// increment position
					position++; 

					// exit the inner while loop
					break;	
				}
			}

			try {

				// write the largest word into the output file
				MyOutput output = new MyOutput();
				output.output(compress.find(outputWord).getCode(), outputFile);

			} 
			// Catch an IOException of there was an error writing to the output
			catch (IOException e) {

				// Print an error message for the user
				System.out.println("There was an error while writing to the output file: TRY AGAIN");
				return;
			}

			// if the number of elements in the dictionary is less than 4096
			// and the inputWord hasn't been processed
			if (compress.numElements() < 4096 && position < inputWord.length()){

				try {

					// Create a dictionary entry and insert it into the dictionary
					compress.insert(new DictEntry(check, compress.numElements()));	
				} 

				// Catch a DictionaryException in case the insertion failed
				catch (DictionaryException e) {

					// Print an error message for the user
					System.out.println("There was an error while adding the word into the dictionary: TRY AGAIN");
				}
			}
		}

		try {

			// Close the input buffer
			input.close();	

			// write any bytes that are still remaining
			MyOutput output = new MyOutput();
			output.flush(outputFile); 

			// close the output buffer
			outputFile.close(); 

		} 
		// Catch an IOException in case there was an error closing the buffers
		catch (IOException e) {

			// Print an error message for the user
			System.out.println("There was an error while closing the files: TRY AGAIN");
		}

		// finally print out a statement to notify the user that the file has been compressed
		finally{
			System.out.println("Your file is compressed.");
		}
		return;
	}
}
