public class TestDict {

	/*
	 ** Test program for the Dictionary class.
	 ** This program WILL NOT COMPILE if your insert or remove
	 ** methods do not throw a DictionaryException.
	 */

	public static void main(String[] args){
		Dictionary dict = new Dictionary(9887);
		DictEntry pair;

		if (args.length == 0 || (args[0].equals("1") || args[0].equals("2") ||
				args[0].equals("3") || args[0].equals("6") ||
				args[0].equals("4") || args[0].equals("5"))) {
			// Test 1: add an entry.
			// Should not throw an exception.
			try {
				dict.insert(new DictEntry("answer", 42));
				System.out.println("   Test 1 succeeded");
			} catch (DictionaryException e) {
				System.out.println("***Test 1 failed");
			}
		}

		if (args.length == 0 || (args[0].compareTo("3") < 0))
			// Test 2: try to add another entry with the same key.
			// Should throw an exception.
			try {
				dict.insert(new DictEntry("answer", 56));
				System.out.println("***Test 2 failed");
			} catch (DictionaryException e) {
				System.out.println("   Test 2 succeeded");
			}

		if (args.length == 0 || (args[0].compareTo("4") < 0))
			// Test 3: find a key in the table.
			if (dict.find("answer") == null) 
				System.out.println("***Test 3 failed");
			else System.out.println("   Test 3 succeeded");

		if (args.length == 0 || (args[0].compareTo("5") < 0))
			// Test 4: look for an inexistent key
			if (dict.find("chicken") != null) 
				System.out.println("***Test 4 failed");
			else System.out.println("   Test 4 succeeded");

		if (args.length == 0 || (args[0].compareTo("6") < 0))
			// Test 5: try to delete a nonexistent entry.
			// Should throw an exception.
			try {
				dict.remove("chicken");
				System.out.println("***Test 5 failed");
			} catch (DictionaryException e) {
				System.out.println("   Test 5 succeeded");
			}

		if (args.length == 0 || (args[0].compareTo("7") < 0))
			// Test 6: delete an actual entry.
			// Should not throw an exception.
			try {
				dict.remove("answer");
				System.out.println("   Test 6 succeeded");
			} catch (DictionaryException e) {
				System.out.println("***Test 6 failed");
			}

		int collisions = 0;
		String s;


		// Test 7: insert 10000 different values into the Dictionary
		try {
			for (int i = 0; i < 10000; ++i) {
				s = (new Integer(i)).toString();
				for (int j = 0; j < 5; ++j) s += s;
				collisions += dict.insert(new DictEntry(s,i));
			}
			System.out.println("   Test 7 succeeded");
		} catch (DictionaryException e) {
			System.out.println("***Test 7 failed");
		}


		if (args.length == 0 || (args[0].compareTo("9") != 0))
			// Test 8: check that all these values are in the Dictionary
			for (int i = 0; i < 10000; ++i) {
				s = (new Integer(i)).toString();
				for (int j = 0; j < 5; ++j) s += s;
				if (dict.find(s) == null) {
					System.out.println("***Test 8 failed");
					return;
				}
			}
		System.out.println("   Test 8 succeeded");

		
		if (args.length == 0 || (args[0].compareTo("10") != 0))
		//Test 9: Number of collisions
		if (collisions >= 6000) {
			System.out.println("***Test 9 failed");
			System.out.println("Too many collisions: "+collisions);
		}
		else  System.out.println("   Test 9 succeeded");
	}
}
