#ifndef CSVREADER_H
#define CSVREADER_H

#include <string>
#include <vector>

class CSVReader {
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> all_data;
public:
    CSVReader();
    CSVReader(std::string);
    void loadCSV(std::string);
    int parseDateString(std::string dateString);
    std::vector<std::string> getHeaders();
    std::vector<std::vector<std::string>> getData();
};

#endif // CSVREADER_H
