/**
 * @author Jameel Kaba
 * CS1027B Assignment 1
 * Class that represents a magazine collection as a list of magazines
 */

public class MagazineCollection {
	/**
	 * attribute declarations // fields
	 */
	
	// magazine array
	private Magazine[] magazineCollection; 
	
	// the number of magazines in the collection
	private int numberOfMagazines; 
	
	// the default array size
	private final int DEFAULT_ARRAY_SIZE = 5; 
	

	// Constructors // 
	/**
	 * constructor that creates a magazine collection of default array size 
	 */
	
	public MagazineCollection() {
		
		// creates a magazine array of default array size
		magazineCollection = new Magazine[DEFAULT_ARRAY_SIZE];
		
		// the magazine collection starts with 0 magazines
		numberOfMagazines = 0;

	}
	
	
	/**
	 * constructor that creates a magazine collection array with the array length equal to size
	 * @param size is the array length
	 */
	
	public MagazineCollection(int size){
		
		// creates a magazine array where it's length is equal to the parameter of size
		magazineCollection = new Magazine[size];
		
		// the magazine collection starts with 0 magazines
		numberOfMagazines = 0;
	}
	
	
	// Methods //
	/**
	 * expandCapacity method that doubles the array size 
	 */
	
	private void expandCapacity(){
		
		// creates a new magazine collection that is double the length 
		// of the original magazine collection
		Magazine[] largerList = new Magazine[magazineCollection.length * 2];
		
		// the contents of the magazine collection are transfered to the larger list
		for(int i = 0; i < magazineCollection.length; i++)
		
			largerList[i] = magazineCollection[i];
		
		// the magazine collection is now assigned the contents of the larger list
		magazineCollection = largerList;
	}
	
	
	/**
	 * addMagazine method that adds a magazine to the magazine collection array
	 * @param magazine this is the magazine that is added to the collection
	 */
	
	public void addMagazine(Magazine magazine){
		
		
		// if the number of magazines in the collection
		// is equal to the length of the array
		// then double the array's capacity
		if (numberOfMagazines == magazineCollection.length)
			expandCapacity();
		
		magazineCollection[numberOfMagazines] = magazine;
		numberOfMagazines++;
	}
	
	
	/**
	 * searchMagazinePrice method that searches for the price of a magazine given the name and format 
	 * @param magazineName the name of the magazine 
	 * @param magazineFormat the format of the magazine
	 * @return the price of the magazine
	 */
	
	public double searchMagazinePrice(String magazineName, String magazineFormat){
	
		// create a constant called NOT_FOUND that is assigned a value of 0
		final int NOT_FOUND = 0;
		
		// create a variable called search and assign a value of NOT_FOUND
		int search = NOT_FOUND;
		
		// create a target magazine with parameters of
		// magazineName, magazineFormat, and a magazine price of 0.0
		Magazine targetMagazine = new Magazine(magazineName, magazineFormat, 0.0);
		
		// if there are no magazines in the collection
		// then return a price of 0.0
		if(numberOfMagazines == 0)
			return 0.0;
		
		// as long as the value of i is less then the number of magazines
		// and that the search is equal to NOT_FOUND
		for (int i = 0; i < numberOfMagazines && search == NOT_FOUND; i++)
			
			// if the magazine in position i has the same name and format as the target magazine
			// then assign the value of search to the value of i
			if (magazineCollection[i].getMagazineName().equals(targetMagazine.getMagazineName()) &&
					magazineCollection[i].getMagazineFormat().equals(targetMagazine.getMagazineFormat()))
				search = i;
		
		// return the magazine price for the magazine in position i (search)
		return magazineCollection[search].getMagazinePrice();
		
	}
	
	
	/**
	 * toString method that returns the array position, name, format, and price of the magazine in the collection
	 * @return the string with the information
	 */
	
	// toString method //
	public String toString(){
		
		// create a blank string
		String s = "";
		
		// for a magazine at position i 
		for (int i = 0; i < numberOfMagazines; i++){
			
			// fill the string with the information for the magazine at
			// position i using the magazine class's toString method
			s =  s  + "\n" + i + " " + magazineCollection[i].toString()+ "\n";
		}
		
		// return the string
		return s;
	}
	
	// Getter method //
	
	/**
	 * getNumberOfMagazines method that returns the number of magazines in the magazine collection
	 * @return numberOfMagazines the number of magazines in the collection
	 */
	
	public int getNumberOfMagazines(){
		
		return numberOfMagazines;
	}

}
