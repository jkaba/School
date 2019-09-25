/*
 * @author Jameel Kaba
 * CS1027B Assignment 1
 * The main method that creates a magazine subscription list
 * as well as customer information and prepares the bills for customers 
 * providing the name, format, and price of the magazines they are subscribed to
 * in preparing the customer bill
 */
import java.util.*;
import java.io.*;

public class Main {

	public static void main(String[] args) {
		// Local variables
		//initialize the variables
		StringTokenizer tokenizer;
		Double magazinePrice;
		String magazineName;
		String magazineFormat;
		Integer customerNumber;
		String  customerFirstName;
		String  customerLastName;
		Magazine magazine;
		Integer numberOfMagazines;

		// The Directories in which the two data files are located
		InStringFile magazineReader=new InStringFile("C:/Users/Jameel/Desktop/CS1027B/Assignment 1/magazine.txt");
		InStringFile customerReader=new InStringFile("C:/Users/Jameel/Desktop/CS1027B/Assignment 1/customer.txt");

		// Create a magazineCollection object
		MagazineCollection magazineCollection = new MagazineCollection();

		/*
		 * The following lines read the information from the data files
		 * and then list the magazine subscription information in a list
		 */
		System.out.format("%n%n%40s%n-----------------------------------------%n",
				"PooPoo Magazines Subscription Information");
		Integer magCt=0;
		Integer custCt=0;
		Integer numTokens;
		Double customerBill=0.0;

		do {
			magCt++;
			String magazineLine = magazineReader.read();
			tokenizer=new StringTokenizer(magazineLine);
			magazineName=tokenizer.nextToken();
			magazineFormat=tokenizer.nextToken();
			magazinePrice=Double.parseDouble(tokenizer.nextToken());


			// Create a magazine object with the read data
			magazine = new Magazine(magazineName, magazineFormat, magazinePrice);
			
			// Then add the magazine object to the magazineCollection object
			magazineCollection.addMagazine(magazine);

			System.out.format("%3d%27s %10s %7.2f %n",magCt,
					magazine.getMagazineName(),
					magazine.getMagazineFormat(),
					magazine.getMagazinePrice());

		} while (!magazineReader.endOfFile());

		// Use magazineCollection's getter method to get the number of Magazines
		numberOfMagazines = magazineCollection.getNumberOfMagazines();
		
		// and insert that value in the following print statement
		System.out.format("%n%d magazines added to Magazine object%n", numberOfMagazines);
		magazineReader.close();

		// Use magazineCollection's toString to print out the magazineCollection   
		System.out.println(magazineCollection);

		/*
		 * The following lines create the bill information from the data files
		 * if the line has 3 tokens it is a customer
		 * if the line has 2 tokens then it is the magazine information
		 * if the line has 0 tokens then prepare the bill for the customer
		 */
		System.out.format("%n%nPooPoo Customer Bills%n%n");
		do {
			String customerLine = customerReader.read();
			tokenizer=new StringTokenizer(customerLine);
			numTokens=tokenizer.countTokens();

			if(numTokens==3) {
				custCt++;
				customerFirstName=tokenizer.nextToken();
				customerLastName=tokenizer.nextToken();
				customerNumber=Integer.parseInt(tokenizer.nextToken());
				System.out.format("---------------------------------------%n");
				System.out.format("%n%3d%10s %10s %d %n",custCt,customerFirstName,customerLastName,customerNumber);
			}
			else
				if(numTokens==2) {
					magazineName=tokenizer.nextToken();
					magazineFormat=tokenizer.nextToken();
					
					// Given the magazineName and magazineFormat use magazineCollection's
					// searchMagazinePrice method to get magazinePrice.
					magazinePrice = magazineCollection.searchMagazinePrice(magazineName, magazineFormat);

					customerBill+=magazinePrice;
					System.out.format("%20s %10s %7.2f %n",magazineName,magazineFormat,magazinePrice);
				} 
				else
					if(numTokens==0) {
						System.out.format("Total bill: %7.2f%n%n",customerBill);
						
						// prepare for next customer
						customerBill=0.0;
					}

		} while (!customerReader.endOfFile());
		customerReader.close();
		System.out.format("%d customers processed%n",custCt);
	}

}
