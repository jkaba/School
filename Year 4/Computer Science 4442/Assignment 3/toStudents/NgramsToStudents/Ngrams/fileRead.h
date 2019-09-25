#ifndef __fileRead_H
#define __fileRead_H



#include <fstream>
#include <iostream>
#include <string>
#include <ctime>
#include <functional>
#include <vector>
using namespace std;

#define EOS  "<END>"

// for reading characters or words (strings) from file
// when reading words(strings), if end of sentence is detected
// output a special string END_OF_SENTENCE = "<END>"


class fileRead {
public:
	fileRead(string fName);
	~fileRead();
	void readCharTokens(vector<string> &tokens);
	void readStringTokens(vector<string> &tokens);
	void readStringTokensEOS(vector<string> &tokens);

private:
	//FILE *m_stream;
	
	ifstream m_ifs;
	bool m_EOS;
	bool m_LastWordReturnedEOS;
	bool m_readEOS;
	bool m_readChar;

	string readStringWithEOS();
	string readStringWithoutEOS();
	string readString();
};

/////////////////////////////////////////////////////////////////////
// Class for handling errors 
/////////////////////////////////////////////////////////////////////

class FileReadException
{
public:
	char* message;
	FileReadException( char* m ) { message = m;  }
	void Report() {
		printf("\n%s\n",message);
	}
};

//////////////////////////////////////////////////////////////////////

inline void read_tokens(const std::string& filename, std::vector<std::string>& tokens, bool eos) {
	fileRead fr(filename);  // open file for reading 
	if (eos)
		fr.readStringTokensEOS(tokens);  //  reads string tokens with EOS marker
	else
		fr.readStringTokens(tokens);        //  reads string tokens without EOS marker
}

//////////////////////////////////////////////////////////////////////

inline void read_tokens(const std::string& filename, std::vector<char>& tokens, bool latin_only) {
	ifstream fr(filename);
	for (char token; fr >> token;)
		if (!latin_only )
			tokens.push_back(token);
		else  if (  'a' <= token && token <= 'z' || 'A' <= token && token <= 'Z'){
			if ( (token >= 'A' && token <= 'Z') ) token = token + 32; // make capitals lowercase
			tokens.push_back(token);
		}
}

#endif

