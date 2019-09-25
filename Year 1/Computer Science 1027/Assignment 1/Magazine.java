/**
 * @author Jameel Kaba
 * CS 1027B Assignment 1
 * This class represents a magazine 
 * with attributes of magazine name, magazine format, and magazine price
 */
public class Magazine {

	/**
	 * Attribute declarations // fields
	 */
	private String magazineName; // magazine name

	private String magazineFormat; // magazine format

	private double magazinePrice; // magazine price

	//Constructor//
	/**
	 * constructor initializes a magazine object based on the magazine's name, format, and price
	 * @param magazineName name of the magazine
	 * @param magazineFormat format of the magazine
	 * @param magazinePrice price of the magazine
	 */

	public Magazine(String magazineName, String magazineFormat, double magazinePrice) {
		// Constructor initializes the attributes of the class

		this.magazineName = magazineName;

		this.magazineFormat = magazineFormat;

		this.magazinePrice = magazinePrice;
	}



	//Getter methods//
	//Returns the String or double specified when used

	/**
	 * getMagazineName method returns the name of the magazine in a string
	 * @return the magazineName
	 */

	public String getMagazineName() {

		return magazineName;
	}



	/**
	 * getMagazineFormat method returns the format of the magazine whether it's digital or print in a string
	 * @return the magazineFormat
	 */

	public String getMagazineFormat() {

		return magazineFormat;
	}



	/**
	 * getMagazinePrice method returns the price of the magazine as a double value
	 * @return the magazinePrice
	 */

	public double getMagazinePrice() {

		return magazinePrice;
	}


	//toString//
	/**
	 * toString method returns a string representation of the magazine
	 * @return string with magazine name, format, and price
	 */

	public String toString() {
		// A string that contains the name, format, and price of the magazine 

		String s = magazineName + " " + magazineFormat + " " + magazinePrice;

		return s;
	}
}

