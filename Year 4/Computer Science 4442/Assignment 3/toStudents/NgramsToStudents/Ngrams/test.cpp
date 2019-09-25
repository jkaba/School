#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
using namespace std;

#include "fileRead.h"
#include "VectorHash.h"
#include "utilsToStudents.h"

////////////////////////////////////////////////////////////////
/// Illustrates how to use unordered_map STD library for language model.
// Each n-gram is stored as vector<T> of size n.
// T is "string" for word language model, and "char" for character language model.
// The function creates all n-grams from the input file, and then prints them to the
// screen with their counts.  Also outputs the count of the most frequent n-gram,
// the total number of distinct n-grams, and number n-grams read from file.
// By default, tokens are read without EOS.  
// Comment line  
//    read_tokens(filename, tokens, false);
// and uncomment line 
//   read_tokens(filename, tokens, true);
// to read tokens with EOS marker.  Note that for T = char, EOS marker is not produced.
////////////////////////////////////////////////////////////////


typedef string T;   // Currently tests string language model.
//typedef char T;   // Uncomment this and comment above for char language model.

void test() {
	
	unsigned int n = 2;                // specifies the "n" for the nGram model
	string filename = "test.txt";      // text for language modeling 
	
	cout <<"\n\nTesting language model with n = " << n;
	
	int maxCount = 0; // will store the count of most frequent nGram
	int N = 0;        // will store the number of tokens read from file 

	try
	{
		// First read all tokens from file into a vector 		
		vector<T> tokens;     // stores tokens read from file

		N = tokens.size();    // that is the number of words to process
		
		read_tokens(filename, tokens, false); // reads tokens from file without EOS 
		//read_tokens(filename, tokens, true); // reads tokens from file with EOS 

		
		// Initialize hash table storing n-grams. Each nGram is a vector<T>, used as hashtable key.
		// Associated with the key is the count of that n-gram
		unordered_map<vector<T>, int> database;  


		// Now create all n-grams from vector of tokens and insert them into the database 
		if ( tokens.size() < n )
			cout << "\nInput file is too small to create any nGrams of size " << n;
		else 
		{
			for ( int i = 0; i <=  tokens.size() - n; i++ )
			{
				vector<T> nGram(n);   // for temporarily storing tokens to go into next n-gram
			
				// Take next n tokens read from the input file 
				for ( unsigned int j = 0; j < n; j++ ) // put next n tokens into vector temp
					nGram[j] = tokens[i+j];

				if ( database.count(nGram) == 0 ) // nGram is not in the database yet, insert it with count 1
					database[nGram] = 1;
				else // nGram is already in the database, increase its count by 1
					database[nGram] = database[nGram] + 1;
			
				if ( maxCount < database[nGram] )   // update maximum nGram count, if needed 
					maxCount = database[nGram];
				
			} 

			///////////////////////////////////////////////////////////////////////////
			// now go over all nGrams in the database and print them out with their counts

			// prints summary of nGrams inserted
			cout << "\nMax nGram count " << maxCount;
			cout << "\nNumber of distinct nGrams " << database.size();
			cout << "\nTotal number of words read " << N;


			// now go over all nGrams in the database and print them out with their counts
			cout <<"\nPrinting out all the nGrams with their counts";
		
			for (auto i = database.begin(); i != database.end(); ++i) 
			{
				vector<T> nGram = i->first;
				cout << "\n";

				for ( unsigned int j = 0; j < nGram.size(); j++ )
					cout << nGram[j] << " ";  // prints out next string in the current nGram

				cout << " " << i-> second; // prints out the count of this nGram
			}	
		}	
	}
	catch (FileReadException e)                     
	{
		e.Report();
	}
}

//////////////////////////////////////////////////////////////////////////////////////

void main(int argc, char **argv)
{
	test();    // Currently test the word model
	           // For char model, uncomment char and comment string template definition 
	           // in the beginning of the file
}
