/**
 * CS2210 Assignment 2
 * @author Jameel Kaba (jkaba) Student #: 250796017
 * 
 * This class creates a Dictionary Entry that contains a key and code
 */

public class DictEntry {

	// private variables
	private String key;
	private int code;

	/**
	 * DictEntry constructor that creates a Dictionary Entry with the specified key and code
	 * @param key the entry's key
	 * @param code the entry's code
	 */

	public DictEntry(String key, int code){

		this.key = key;
		this.code = code;
	}



	/**
	 * Getter method that returns the value of key
	 * @return key
	 */

	public String getKey(){

		return key;
	}

	/**
	 * Getter method that returns the value of code
	 * @return code
	 */

	public int getCode(){

		return code;
	}
}
