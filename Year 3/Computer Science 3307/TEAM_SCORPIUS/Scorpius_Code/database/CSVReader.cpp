#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

#include "database/CSVReader.h"

// Loads the CSV file at file_name.

void CSVReader::loadCSV(std::string file_name) {
    std::ifstream myfile(file_name.c_str());
    if (myfile.fail()) {
        std::cout << "Couldn't open file \"" << file_name << "\"." << std::endl;
        return;
    }
	
    else if (myfile.is_open()) {
		std::stringstream sstr;
		sstr << myfile.rdbuf();
		std::string f = sstr.str();
		myfile.close();

        size_t len = f.length();
		
		bool setHeaders = false;
		
        size_t pos = 0;
        while( pos < len ) { // While the file's not empty
			std::vector<std::string> line;
            while( f.at( pos ) != '\n' && pos < len ) { // For each character in the line
				std::string element = "";
                while( f.at( pos ) != ',' && pos < len && f.at( pos ) != '\n' && f.at( pos ) != '\r' ) { // For each element
					if( f.at( pos ) == '"' ) { // If we have a quote, continue till the next quote
						pos++;
                        while( f[pos] != '"' && pos < len ) {
							element += f.at( pos );
							pos++;
						}
                        pos++; // Last quote
                    } else {
						element += f.at( pos );
                        pos++;
					}
				}
                line.push_back( element );

                // In case last column is missing information
                if (f.at(pos) == ',' && f.at(pos+1) == '\n')
                    line.push_back("");

                if ( f.at( pos ) == '\n') {
                    break;
                }
                pos++;
			}
			if( !setHeaders ) {
				setHeaders = true;
				headers = line;
			} else {
				all_data.push_back( line );
            }
            pos++;
		}
    }
}

// Returns the year in a date string.

int CSVReader::parseDateString(std::string dateString) {
    int year;
    sscanf(dateString.c_str(), "%4d", &year); // The only 4-digit number in a date field is a year, period
    return year;
}

// Returns the header vector for a CSV

std::vector<std::string> CSVReader::getHeaders() {
    return headers;
}

// Returns all data from a CSV

std::vector<std::vector<std::string>> CSVReader::getData() {
    return all_data;
}

CSVReader::CSVReader() {

}

CSVReader::CSVReader(std::string file) {
    loadCSV(file);
}
