/*
Name: Jameel Kaba
UWO/GAUL id: jkaba
Student #: 250796017

CS4442B Assignment 3 P5
*/

// Include Statements
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include "../Ngrams/fileRead.h"
#include "../Ngrams/VectorHash.h"
#include "../Ngrams/utilsToStudents.h"

using namespace std;

int main(int argc, char const *argv[]) {

	// Check if there are enough args
	if (argc != 5) {
		return -1;
	}

	cout << "Program is incomplete, and will not produce appropriate output";

	// Get data from args
	string corpusFileName = argv[1];
	string sentenceFileName = argv[2];
	int n = stoi(argv[3]);
	int threshold = stoi(argv[4]);

	// Get all the words from text model and sentence
	vector<string> textModel;
	vector<string> sentenceTokens;
	read_tokens(corpusFileName, textModel, false);
	read_tokens(sentenceFileName, sentenceTokens, false);

	// If text model or sentence are too small, return an error
	if (textModel.size() < n || sentenceTokens.size() < n) {
		cout << "Either Text model or sentence is too small to create N Grams of requested size n";
		return -1;
	}

	// Store words and freq in dictionary, need to use auto in loop else it takes a long time
	unordered_map <string, int> dictionary;
	unordered_map <vector<string>, int> corpus;
	for (auto &word : textModel) {
		if (dictionary.count(word) == 0) {
			dictionary[word] = 1;
		}
	}

	// Initialize variables
	vector<double> probs;
	int vocabSize = dictionary.size() + 1;
	double N = textModel.size();
	unordered_map<vector<string>, int> corpusA;
	unordered_map<vector<string>, int> corpusB;

	// Build corpus based on text model
	for (int i = 0; i < textModel.size() - (n - 1); i++) {
		vector<string> nGram;

		// Get current n gram from text
		for (int j = 0; j < n; j++) {
			nGram.push_back(textModel.at(i + j));
		}

		// If it is not in dictionary introduce it, otherwise increment freq
		if (corpusA.count(nGram) == 0) {
			corpusA[nGram] = 1;
		}
		else {
			corpusA[nGram] = corpusA[nGram] + 1;
		}
	}

	// Build second corpus based on sentences
	for (int i = 0; i < sentenceTokens.size() - (n - 1); i++) {
		vector<string> nGram;

		// Get current n gram from text
		for (int j = 0; j < (n - 1); j++) {
			nGram.push_back(sentenceTokens.at(i + j));
		}

		// If n gram is not in dictionary, add it, else increment freq
		if (corpusB.count(nGram) == 0) {
			corpusB[nGram] = 1;
		}
		else {
			corpusB[nGram] = corpusB[nGram] + 1;
		}
	}

	// Initialize vector which will store how many times common n grams occur
	int size = corpusB.size();
	vector<int> count;

	// Loop to calculate probabilities
	// NORMALIZATION IS NOT DONE
	for (auto &check : corpusB) {

		double rate = 0;

		// If n gram occurs in both, then increment rate
		for (int i = 0; i < corpusA.size(); i++) {
			if (corpusA.count(check.first) != 0)
				rate += corpusA[check.first];
		}

		double prob;

		//If r < threshold we use Good Turing
		if (rate < threshold) {
			prob = (rate + 1) * (corpusA.count(check.first)+1) / (N * corpusA.count(check.first));
		}

		// Otherwise we just use MLE
		else {
			prob = rate / N;
		}

		// Store the probability
		probs.push_back(prob);
	}

	// Initialize more variables
	double probability = 0;
	bool flag = false;

	// Calculate total probaility
	for (int i = 0; i < probs.size(); i++) {
			probability += log(probs.at(i));
	}

	// Print out probability
	cout << probability << '\n';

	return 0;
}