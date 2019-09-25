/*
	Name: Jameel Kaba
	UWO/GAUL id: jkaba
	Student #: 250796017

	CS4442B Assignment 3 P1
*/

// Include Statements
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include "../Ngrams/fileRead.h"
#include "../Ngrams/VectorHash.h"

int main(int argc, char** argv) {

	// Check if enough parameters
	if (argc != 3) {
		return -1;
	}

	// Get Data from arguments
	string fileName = argv[1];
	int k = atoi(argv[2]);

	// Read file to get strings
	vector<string> tokens;
	read_tokens(fileName, tokens, false);

	// Add words to dictionary as well as there frequency
	// If auto is not used in this loop, the program takes up to 45 minutes to run
	unordered_map<string, int> dictionary;
	for (auto &token : tokens) {

		// If the word is in the dictionary, then increment count
		if (dictionary.count(token)) {
			dictionary[token] = dictionary[token] + 1;
		}

		// Else add it in
		else {
			dictionary[token] = 1;
		}
	}

	// Store words from dictionary into a vector for intial sorting
	vector<pair<int, string>> frequency;
	frequency.reserve(dictionary.size());
	for (auto &word : dictionary) {

		// Obtain the frequency and the word, make it a pair and store it
		int freq = word.second;
		string s = word.first;
		pair<int, string> insert= pair<int, string>(freq, s);
		frequency.push_back(insert);
	}

	// std sort used to sort the vector of pairs by int values
	sort(frequency.begin(), frequency.end());

	// Second Sorting process
	// some variables
	float n = 0;
	int scout = 0;
	int siz = frequency.size() - 1;

	// New vector to store lexicographic order
	vector<pair<int, string>> alpha;
	alpha.reserve(dictionary.size());

	// Loop which does the sorting 
	// New vector is highest to lowest in order of frequency and then lexicographic
	for (int i = frequency.size() - 1; i >= 0; i--) {
		// Initial value
		if (i == 0) {

			// Store the value
			alpha.push_back(frequency.at(i));

			// If for some reason there is are a set with same frequency
			if (scout != 0) {

				// Loop to store them in lexicographic order
				for (int j = i; j <= i + scout; j++) {
					alpha.push_back(frequency.at(j));
				}

				// Reset the counter
				scout = 0;
			}
		}

		// Frequencies are not equal
		else if (frequency.at(i).first != frequency.at(i - 1).first) {

			// Do we have a set with same frequncies
			if (scout != 0) {

				// If so, organize in lexigoraphic order and store
				for (int j = i; j <= i + scout; j++) {
					alpha.push_back(frequency.at(j));
				}

				// Reset counter
				scout = 0;
			}

			// If counter is 0, it is only value so store it
			else if (scout == 0) {
				alpha.push_back(frequency.at(i));
			}
		}

		// Increment counter to denote we have a set
		else {
			scout++;
		}
	}

	// For loop to print out the k most frequent words
	for (int i = 0; i < k; i++) {
		n += alpha.at(i).first;
		cout << alpha.at(i).second << ", " << alpha.at(i).first << "\n";
	}

	// Print the percentage out
	cout << n / tokens.size() * 100 << " %" << '\n';

	return 0;

}