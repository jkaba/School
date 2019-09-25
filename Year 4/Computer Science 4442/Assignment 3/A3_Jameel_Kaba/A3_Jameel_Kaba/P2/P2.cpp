/*
Name: Jameel Kaba
UWO/GAUL id: jkaba
Student #: 250796017

CS4442B Assignment 3 P2
*/

// Include Statements
#include <stdlib.h>
#include <iostream>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Ngrams/fileRead.h"
#include "../Ngrams/VectorHash.h"

using namespace std;

int main(int argc, char const *argv[]) {

	// Check to make sure there are enough args
	if (argc != 5) {
		return -1;
	}

	// Get data from arugments
	string textFile1 = argv[1];
	string textFile2 = argv[2];
	int n = stoi(argv[3]);
	bool printNGrams = atoi(argv[4]);

	// Get every word from each text
	vector<string> tokensA;
	read_tokens(textFile1, tokensA, false);

	vector<string> tokensB;
	read_tokens(textFile2, tokensB, false);

	// Error checking, if size of either file is too small return an error
	if (tokensA.size() < n || tokensB.size() < n) {
		cout << "One of the files is too small to create n-Grams of the requested size of n";
		return -1;
	}

	// So long as we are looking for an N Gram where n > 0
	if (n > 0) {

		// Initialize dictionary to store N Grams and counts
		unordered_map <vector<string>, int> corpusA;

		// Determine frequencies, and save N Grams *Possibly faster if auto used instead*
		for (int i = 0; i < tokensA.size() - (n - 1); i++) {
			vector<string> nGram;

			// Get the n Gram and store it in a vector
			for (int j = 0; j < n; j++) {
				nGram.push_back(tokensA.at(i + j));
			}

			// If n Gram is in corpus, increment freq, otherwise introduce it
			if (corpusA.count(nGram) == 0) {
				corpusA[nGram] = 1;
			}
			else {
				corpusA[nGram] = corpusA[nGram] + 1;
			}
		}

		// Initialize dictionary to store N Grams and counts
		unordered_map <vector<string>, int> corpusB;

		// Determine frequencies and save N Grams *possibly faster if auto used*
		for (int i = 0; i < tokensB.size() - (n - 1); i++) {
			vector<string> nGram;

			// Get the n Gram
			for (int j = 0; j < n; j++) {
				nGram.push_back(tokensB.at(i + j));
			}

			// If n Gram is in dictionary, increment freq, else introduce it
			if (corpusB.count(nGram) == 0) {
				corpusB[nGram] = 1;
			}
			else {
				corpusB[nGram] = corpusB[nGram] + 1;
			}
		}

		// Initialize vector which will store common N Grams
		vector <vector<string>> commonGrams;

		// Loop to store common N Grmas
		for (auto &check : corpusB) {
			if (corpusA.count(check.first) > 0) {
				commonGrams.push_back(check.first);
			}
		}

		// If we need to print out N Grams
		if (printNGrams == 1) {

			// Nested For loops to print out N Grams
			for (int i = commonGrams.size() - 1; i >= 0; i--) {
				for (int j = 0; j < commonGrams.at(i).size(); j++) {
					cout << commonGrams.at(i).at(j) << " ";
				}
				cout << "\n";
			}	
		}

		// Calculate and print the percentage of unobserved N Grams
		cout << (1 - commonGrams.size() / float(corpusB.size())) * 100 << '\n';
	}
	return 0;
}