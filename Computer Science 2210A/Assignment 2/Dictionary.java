/**
 * CS2210A Assignment 2
 * @author Jameel Kaba (jkaba) Student#: 250796017
 * 
 * This class creates a Dictionary to store strings and unique codes
 * Implemented with a "HashTable" and uses separate chaining
 */

public class Dictionary implements DictionaryADT {

	// private variables
	private LinkedList[] dictionary;
	private int numWords;

	/**
	 * Dictionary constructor that creates an array of Linked Lists (the dictionary)
	 * with the size being passed as a parameter
	 * @param size the size of the dictionary
	 */

	public Dictionary(int size) {

		// create a new array of linked lists of size passed as parameter
		dictionary = new LinkedList[size];

		// while int i is less than the size of the dictionary
		for(int i = 0; i < size; i++)
		{
			// create an empty linked list at every position in the linked list
			dictionary[i] = new LinkedList();
		}
	}

	// HashFunction
	/**
	 * HashFunction that returns a location in the table that corresponds to a key
	 * @param key the key to be put through the HashFunction
	 * @param M The array of Linked Lists (dictionary)
	 * @param a a prime number
	 * @return the location for the key
	 */

	public int hashFunction(String key, LinkedList[] M, int a){

		// set an integer to reference the length of the key minus 1
		int code = (int)key.length()-1;

		// for i that is equal to the length of the key minus 2 
		// while it is greater than 0
		for(int i = key.length()-2; i > 0; i--){
			// code is equal to itself times the prime number a
			// plus an integer value of the character of key at i
			// all moduloed by the length of M
			code = ((code*a) + (int)key.charAt(i)) % M.length;

		}
		// return the code
		return code;
	}

	// insert method that inserts a DictEntry into the dictionary
	/**
	 * insert method that inserts a DictEntry into the dictionary
	 * throws a DictionaryException when the key is already inside the dictionary
	 * will return 1 if there is a collision or 0 if not
	 */

	public int insert(DictEntry pair) throws DictionaryException {

		// find the position for a key in the dictionary
		int pos = hashFunction(pair.getKey(), dictionary, 31);

		// if the key from the DictEntry is found in the dictionary
		if(find(pair.getKey()) != null){

			// throw an exception saying that it already exists
			throw new DictionaryException("ERROR: 404 WORD ALREADY EXISTS");
		}

		else{
			// if the key is not in the dictionary
			// make a new DictEntry with the pair passed in the parameters
			DictEntry add = new DictEntry(pair.getKey(), pair.getCode());

			// make a new LinearNode that references the word to be added
			LinearNode<DictEntry> addWord = new LinearNode<DictEntry>(add);

			// increment the number of words
			numWords++;
			// return the add method of the linked list when the word is added
			// return 1 if there is a collision or 0 if not
			return dictionary[pos].add(addWord);
		}
	}

	// remove method that tries to remove a word passed through as a parameter
	/**
	 * Remove method that tries to remove a word that is passed in as a parameter
	 * Throws an exception if the word does not exist
	 */

	public void remove(String key) throws DictionaryException {

		// get the position for the word
		int pos = hashFunction(key, dictionary, 31);

		// if the word is not in the dictionary
		if(find(key) == null){

			// throw an exception to tell the user it is not in the dictionary
			throw new DictionaryException("ERROR 404: WORD DOES NOT EXIST");
		}

		// if the key is found  
		if(this.find(key) != null){

			// create a DictEntry that references the word to be deleted
			DictEntry delete = new DictEntry(key, pos);

			// create a LinearNode that references the DictEntry to be deleted
			LinearNode<DictEntry> deleteWord = new LinearNode<DictEntry>(delete);

			// Use the linked list remove method to remove the word from the dictionary
			dictionary[pos].remove(deleteWord);

			// decrement the number of words in the dictionary
			numWords--;
		}
	}

	// find method that searches the dictionary for a key
	/**
	 * find method that searches the dictionary for a key that 
	 * is passed through as a parameter
	 */
	public DictEntry find(String key){

		// get the position for the key
		int pos = hashFunction(key, dictionary, 31);

		// set a LinearNode to reference the first element in the dictionary at that position
		LinearNode<DictEntry> search = dictionary[pos].getHead();

		// if search is not null
		if(search != null){

			// if the DictEntry key in search is equal to the key we are looking for
			if(search.getElement().getKey().equals(key)){

				// return the element from search
				return search.getElement();
			}
			else{

				// while the next node of search is not null
				while(search.getNext() != null){

					// set search to the next node
					search = search.getNext();

					// if the key in search is equal to the key we are looking for
					if(search.getElement().getKey().equals(key)){

						// return the element in search
						return search.getElement();
					}
				}
			}
		}
		// else return null
		return null;
	}

	/**
	 * numElements method that returns the number of words in the dictionary
	 */

	public int numElements() {

		// returns the number of words in the dictionary
		return numWords;
	}

}
