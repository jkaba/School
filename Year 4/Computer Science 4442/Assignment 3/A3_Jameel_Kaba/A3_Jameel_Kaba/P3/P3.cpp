/*
Name: Jameel Kaba
UWO/GAUL id: jkaba
Student #: 250796017

CS4442B Assignment 3 P3
*/

// Include Statements
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <algorithm>
#include <unordered_map>
#include "../Ngrams/fileRead.h"
#include "../Ngrams/VectorHash.h"
#include "../Ngrams/utilsToStudents.h"

using namespace std;

int main(int argc, char const *argv[]) {
	
	// Check if there are correct number of arguments
	if (argc != 3) {
		return -1;
	}

	cout << "This program is not complete and will end in an error";

	// Obtain info from arguments, and intialize random seed
	string text = argv[1];
	int n = atoi(argv[2]);
	srand(time(NULL));

	// Store all the words from the text file
	vector<string> tokens;
	read_tokens(text, tokens, true);

	// If the text is too small, return an error message
	if (tokens.size() < n) {
		cout << "Text file provided is too small to create N Grams of requested size n";
		return -1;
	}

	// Store words and their frequencies in a dictionary *Must use auto for loop, else it takes too long*
	unordered_map <string, int> dictionary;
	for (auto &word : tokens) {
		if (dictionary.count(word) == 0) {
			dictionary[word] = 1;
		}
		else {
			dictionary[word] += 1;
		}
	}

	// Vector of strings to represent the generated sentence
	vector<string> sentence = {""};

	// Initialize variables
	int count = 0;
	bool rebuild = true;
	double N = tokens.size();
	unordered_map<vector<string>, int> corpus;
	vector<double> probs;
	vector<string> vocabulary;

	// While we haven't hit the end
	while (sentence.back() != "<END>") {

		// Case 1
		if (n = 1) {

			// Get N grams, find frequency, and store sentence
			for (int i = 0; i < tokens.size() - (n - 1); i++) {
				vector<string> nGram;

				for (int j = 0; j < n; j++) {
					nGram.push_back(tokens.at(i + j));
				}
				if (corpus.count(nGram) == 0) {
					corpus[nGram] = 1;
				}
				else {
					corpus[nGram] = corpus[nGram] + 1;
				}
				vocabulary.push_back(nGram.at(i));
				probs.push_back(corpus.count(nGram) / N);
			}

			// Add word to the sentence
			sentence.push_back(vocabulary[drawIndex(probs)]);
		}

		// Case 2
		if (n > 1) {

			// Get n gram, determine frequency, build sentence
			for(int i = 0; i < tokens.size() - (n - 1); i++) {
				vector<string> nGram;

				for (int j = 0; j < n; j++) {
					nGram.push_back(tokens.at(i + j));
				}
				if (corpus.count(nGram) == 0) {
					corpus[nGram] = 1;
				}
				else {
					corpus[nGram] = corpus[nGram] + 1;
				}
				vocabulary.push_back(nGram.at(i));
				probs.push_back(corpus.count(nGram) / N);
			}

			// Add word to the sentence
			sentence.push_back(vocabulary[drawIndex(probs)]);
		}

		// If end of tokens, insert end string
		if (count == tokens.size() - (n - 1)) {
			sentence.push_back("<END>");
		}

		// Increment count
		count++;
	}
	

	// Loop to print out the generated sentence
	for (int i = 0; i < sentence.size(); i++){
		cout << sentence.at(i) << " ";
	}
	cout << "\n";
	
	return 0;
}