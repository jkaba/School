#include "fileRead.h"


/////////////////////////////////////////////////////////////////////////////////
//                       class fileRead   methods                              //
/////////////////////////////////////////////////////////////////////////////////


fileRead::fileRead(string fName)
{


	// Check if can open the file
	m_ifs.open(fName.c_str(),ifstream::in);
	if ( !m_ifs.is_open()  ) throw FileReadException("Cannot open file. Check the file name.");

	m_EOS = false;
	m_LastWordReturnedEOS = false;
	m_readEOS = false;
	m_readChar = false;
};


/////////////////////////////////////////////////////////////////////////////////

fileRead::~fileRead()
{
	m_ifs.close();
}

/////////////////////////////////////////////////////////////////////////////////

string fileRead::readString()
{
	if ( m_readEOS )
		return readStringWithEOS();
	else if ( m_readChar)
	{
		string s;
	
		char ch = m_ifs.get();
		if (ch != EOF)
			s.append(1,ch);
		return(s);
	}
	return readStringWithoutEOS();
}


/////////////////////////////////////////////////////////////////////////////////

string fileRead::readStringWithEOS()
{
	string toReturn;

	if ( m_EOS ) {
		m_EOS = false;
		m_LastWordReturnedEOS = true;
		return(EOS);
	}

	// if file is finished, first return EOS if previous word was not EOS
	// then an empty string. If previous word was EOS return an empty string
	if (  m_ifs.eof() ){
		if ( m_LastWordReturnedEOS == false )
		{
			m_LastWordReturnedEOS = true;
			return(EOS);
		}
		return(toReturn);
	}
	
	// first read file characters until find a character in letter range
	// or an end of sentence character
	char ch = m_ifs.get();
	while  ( !((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) ) 
	{
		// end of sentence
		if ( ch == '.' || ch == '!' || ch == '?' || ch == 34 )
		{
			if ( m_LastWordReturnedEOS == false )
			{
				m_LastWordReturnedEOS = true;
				return(EOS);
			}
		}

		if ( m_ifs.eof() ) // end of file
		{
			if ( m_LastWordReturnedEOS == false )
			{
				m_LastWordReturnedEOS = true;
				return(EOS);
			}
			return(toReturn);
		}
		ch =  m_ifs.get();
		
	}

	// now get a concequitive sequence of letter characters
	while  ( ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) ) 
	{
		if ( (ch >= 'A' && ch <= 'Z') ) ch = ch + 32; // make capitals lowercase
			toReturn.append(1,ch);

		if (  m_ifs.eof() ){
			m_LastWordReturnedEOS = false;
			return(toReturn);
		}
		ch =  m_ifs.get();
		
	}

	// check if last character, which would be  non-letter character, is end of sentence 
	if ( ch == '.' || ch == '!' || ch == '?' || ch == 34 )
		m_EOS = true;

	m_LastWordReturnedEOS = false;
	return(toReturn);
}

/////////////////////////////////////////////////////////////////////////////////


string fileRead::readStringWithoutEOS()
{
	string toReturn;


	// if file is finished, return empty string
	if (m_ifs.eof() ) {	
		return(toReturn);
	}
	

	// first read file characters until find a character in letter range
	// or an end of sentence character
	char ch = m_ifs.get();
	while  ( !((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) ) 
	{

		if ( m_ifs.eof() ) 
		{
			return(toReturn);
		}
		ch =  m_ifs.get();
	}

	// now get a concequitive sequence of letter characters
	while  ( ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) ) 
	{
		if ( (ch >= 'A' && ch <= 'Z') ) ch = ch + 32; // make capitals lowercase
			toReturn.append(1,ch);

		if (  m_ifs.eof() ){
			return(toReturn);
		}
		ch =  m_ifs.get();
	}

	return(toReturn);
}


////////////////////////////////////////////////////////////////////////////////


void fileRead::readStringTokens(vector<string> &tokens)
{
    tokens.clear();
	
	string s;
	s.assign(readString()); // read next string from file into s

	// if no more strings left in the file, fr returns an empty string
	while ( s.size() != 0 )
	{
		tokens.push_back(s);
		s.assign(readString());  // read next string from file into s
	}
}

////////////////////////////////////////////////////////////////////////////////

void fileRead::readStringTokensEOS(vector<string> &tokens)
{
	 m_readEOS = true;
	 readStringTokens(tokens);   
}


////////////////////////////////////////////////////////////////////////////////

void fileRead::readCharTokens(vector<string> &tokens)
{
	 m_readChar = true;
	 readStringTokens(tokens);    
}