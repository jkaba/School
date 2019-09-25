/**
 * It's a class that manages records. No, but seriously, this class stores the
 * individual records of an Excel spreadsheet obtained from Acuity STAR for
 * processing and analysis.
 *
 * CS3307, Team Peach
 */
#define _GNU_SOURCE 1

#include "database/RecordsManager.h"
#include "datamodel/TreeModel.h"

#include <sstream>
#include <iomanip>
#include <QDebug>

/**
 * Default constructor.
 *
 * @param _headers  a vector of headers attributed to this manager
 */
RecordsManager::RecordsManager(BasicRecord* _headers) {
    headers = *_headers;
}

/**
 * Default destructor.
 */
RecordsManager::~RecordsManager() {
}

/**
 * Adds a new record to the manager.
 *
 * @param key       the record's key
 * @param record    the record itself
 */
void RecordsManager::addRecord(int key, BasicRecord* record) {
    manager.emplace(key, record);
}

/**
 * Returns a vector of records containing a matching date key.
 *
 * @param key   the key of the record
 * @return      a vector of records with the given key
 */
std::vector<BasicRecord*> RecordsManager::findRecord(int key) {
    std::vector<BasicRecord*> returnList;
    std::pair <Manager::iterator, Manager::iterator> ret;
    ret = manager.equal_range(key);

    for (Manager::iterator itr = ret.first; itr != ret.second; itr++) {
        returnList.push_back(itr->second);
    }

    return returnList;
}

/**
 * Returns a vector of records between two given date keys.
 *
 * @param startYear the start year in the range to search
 * @param endYear   the end year in the range to search
 * @return          a vector of records between two dates
 */
std::vector<BasicRecord*> RecordsManager::findRecordsInRange(int startYear, int endYear) {
    if (startYear > endYear){
        int temp = startYear;
        startYear = endYear;
        endYear = temp;
    }
    std::vector<BasicRecord*> returnList;
    Manager::iterator startPoint = manager.lower_bound(startYear);
    Manager::iterator endPoint = manager.upper_bound(endYear);

    for (Manager::iterator itr = startPoint; itr != endPoint; itr++) {
        returnList.push_back(itr->second);
    }

    return returnList;
}

/**
 * Returns the header list for this manager.
 *
 * @return a vector of string representing column headers
 */
BasicRecord RecordsManager::getHeaders() {
    return headers;
}

/**
 * Returns the column number of the header in the CSV file.
 *
 * @param headerTitle   the title of the header (i.e. the string to search for)
 * @return              its index in the headers list
 */
int RecordsManager::getHeaderIndex(std::string headerTitle) {
    for (unsigned int i = 0; i < headers.size(); i++) {
        // temp fix, requires proper CSV processing, I feel dirty, my hands are unclean
        std::string tempfix = headerTitle;
        if (headers[i].compare(headerTitle) == 0 || headers[i].compare(tempfix.append(" *")) == 0) {
            return i;
        }
    }

    return -1;
}

/**
 * Helper method to return a vector of strings given a variable list of strings.
 *
 * @param n     the number of string arguments passed
 * @param ...   the arguments, a list of strings to add to a vector
 * @return      a vector of the passed strings
 */
std::vector<std::string> RecordsManager::list(int n, ...) {
    std::vector<std::string> list;
    char* val;

    va_list v;
    va_start(v, n);

    for (int i = 0; i < n; i++) {
        val = va_arg(v, char*);
        list.push_back(val);
    }

    va_end(v);

    return list;
}

/**
 * Returns the formatted QString for the Grants data. To be used with TreeModel.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @return              a formatted QString to be used directly in the creation
 *                      of a TreeModel
 */
QString RecordsManager::createQStringForGrants(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd) {
    QString s = QString(analyze(startYear, endYear, sortFields, list(1, "Total Amount"), 0x1, sortFields.back(), filterStart, filterEnd).c_str());
    return s;
}

/**
 * Returns the headers for Grants data. To be used with TreeModel.
 *
 * @param topLevel  the header name of the top-level sort field
 * @return          a QList containing the headers for the tree view
 */
QList<QVariant> RecordsManager::createHeadersListForGrants(std::string topLevel) {
    QList<QVariant> hds;
    hds << topLevel.c_str() << "Total" << "Total $";
    return hds;
}

/**
 * Returns the formatted QString for the Presentations data. To be used with TreeMod
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @return              a formatted QString to be used directly in the creation
 *                      of a TreeModel
 */
QString RecordsManager::createQStringForPres(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd) {
    return QString(analyze(startYear, endYear, sortFields, sortFields.back(), filterStart, filterEnd).c_str());
}

/**
 * Returns the summary headers for Presentations data. To be used with TreeModel.
 *
 * @param topLevel  the header name of the top-level sort field
 * @return          a QList containing the headers for the tree view
 */
QList<QVariant> RecordsManager::createHeadersListForPres(std::string topLevel) {
    QList<QVariant> hds;
    hds << topLevel.c_str() << "# Presentations";
    return hds;
}

/**
 * Returns the formatted QString for the Publications data. To be used with TreeModel.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @return              a formatted QString to be used directly in the creation
 *                      of a TreeModel
 */
QString RecordsManager::createQStringForPubs(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd) {
    return QString(analyze(startYear, endYear, sortFields, sortFields.back(), filterStart, filterEnd).c_str());
}

/**
 * Returns the summary headers for Publications data. To be used with TreeModel.
 *
 * @param topLevel  the header name of the top-level sort field
 * @return          a QList containing the headers for the tree view
 */
QList<QVariant> RecordsManager::createHeadersListForPubs(std::string topLevel) {
    QList<QVariant> hds;
    hds << topLevel.c_str() << "Totals";
    return hds;
}

/**
 * Returns the formatted QString for the Teaching data. To be used with TreeModel.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @return              a formatted QString to be used directly in the creation
 *                      of a TreeModel
 */
QString RecordsManager::createQStringForTeaching(int startYear, int endYear, const std::vector<std::string> &sortFields, char filterStart, char filterEnd) {
    return QString(analyze(startYear, endYear, sortFields, list(2, "Total Hours", "Number Of Trainees"), 0x0, sortFields.back(), filterStart, filterEnd).c_str());
}

/**
 * Returns the headers for Teaching data. To be used with TreeModel.
 *
 * @param topLevel  the header name of the top-level sort field
 * @return          a QList containing the headers for the tree view
 */
QList<QVariant> RecordsManager::createHeadersListForTeaching(std::string topLevel) {
    QList<QVariant> hds;
    hds << topLevel.c_str() << "Totals" << "# of Hours" << "# of Students";
    return hds;
}

/**
 * Returns tuples containing member names and the counts for the given date range.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param filterStart   the start of a character range with which to filter the top-level by
 * @param filterEnd     the end of a character range with which to filter the top-level by
 * @return              a vector of tuples containing the member name and its count
 */
std::vector<std::pair<std::string, int>> RecordsManager::getCountByName(int startYear, int endYear, char filterStart, char filterEnd) {
    std::vector<std::pair < std::string, int>> ret;

    // query the database
    std::string query = analyze(startYear, endYear, list(1, "Member Name"), list(0), 0, "Member Name", filterStart, filterEnd);

    // interpret the result string
    size_t pos = 0, index;
    std::string tempName, tempCount;
    while ((index = query.find('\t', pos)) != std::string::npos) {
        // find the member name
        tempName = query.substr(pos, index - pos);

        // if it's the totals row, then we're done
        if (tempName.compare("Total") == 0) {
            break;
        }

        // increment our position in the string
        pos = index + 1;

        // find the count
        index = query.find('\n', pos);
        tempCount = query.substr(pos, index - pos);

        // increment our position in the string
        pos = index + 1;

        // store the name and count in a pair
        ret.emplace_back(tempName, std::stoi(tempCount));
    }

    return ret;
}

/**
 * Returns tuples for a narrowing and count field for the given date range.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param headers       a list of n headers with which to sort by
 * @param matchString   a list of n - 1 corresponding to the header name to match
 * @param filterStart   the start of a character range with which to filter the top-level by
 * @param filterEnd     the end of a character range with which to filter the top-level by
 * @return              a vector of tuples containing a member's count types and their counts
 */
std::vector<std::pair<std::string, int>> RecordsManager::getCountTuple(int startYear, int endYear, const std::vector<std::string> &headers, const std::vector<std::string> &matchStrings, char filterStart, char filterEnd) {
    std::vector<std::pair < std::string, int>> ret;

    // query the database
    std::string query = analyze(startYear, endYear, headers, headers.back(), filterStart, filterEnd);

    size_t pos = 0, depth = 0, index;
    int totalCount;
    std::string frontValue, countName, tempCount;

    // interpret the result string
    while ((index = query.find('\t', pos)) != std::string::npos) {
        // find the value of the first field
        frontValue = query.substr(pos + depth, index - pos - depth);

        // if it's the totals row, then we're done
        if (frontValue.compare("Total") == 0) {
            break;
        }

        if (frontValue.compare(matchStrings[depth]) == 0) {
            if (depth < matchStrings.size() - 1) {
                // we need to go deeper
                depth++;
            } else {
                // matched the first field
                index = query.find('\t', pos);

                // increment our position in the string
                pos = index + 1;

                // find the total count
                index = query.find('\n', pos);
                totalCount = std::stoi(query.substr(pos, index - pos));

                // increment our position in the string
                pos = index + 1;

                // increment depth
                depth++;

                do {
                    // find the second field
                    index = query.find('\t', pos);
                    countName = query.substr(pos + depth, index - pos - depth);

                    // increment our position in the string
                    pos = index + 1;

                    // find the count
                    index = query.find('\n', pos);
                    tempCount = query.substr(pos, index - pos);

                    // increment our position in the string
                    pos = index + 1;

                    // store the second field and count in a pair
                    ret.emplace_back(countName, std::stoi(tempCount));

                    // continue until we've counted up all of the second field
                    totalCount -= std::stoi(tempCount);
                } while (totalCount != 0);

                // we're done since analyze() returns things in order
                break;
            }
        } else {
            // increment our position in the string to the next newline
            index = query.find('\n', pos);
            pos = index + 1;
        }
    }

    return ret;
}

/**
 * Returns tuples for a narrowing and totals field for the given date range.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param headers       a list of n headers with which to sort by
 * @param matchString   a list of n - 1 corresponding to the header name to match
 * @param accCol        the header name containing the values to be accumulated
 * @param filterStart   the start of a character range with which to filter the top-level by
 * @param filterEnd     the end of a character range with which to filter the top-level by
 * @return              a vector of tuples containing a member's accumulator types and their totals
 */
std::vector<std::pair<std::string, double>> RecordsManager::getTotalsTuple(int startYear, int endYear, const std::vector<std::string> &headers, const std::vector<std::string> &matchStrings, std::string accCol, char filterStart, char filterEnd) {
    std::vector<std::pair < std::string, double>> ret;

    // query the database
    std::string query = analyze(startYear, endYear, headers, list(1, accCol.c_str()), 0x0, headers.back(), filterStart, filterEnd);

    // interpret the result string
    size_t pos = 0, depth = 0, index;
    int totalCount;
    std::string frontValue, countName, tempCount, tempTotal;
    while ((index = query.find('\t', pos)) != std::string::npos) {
        // find the value of the first field
        frontValue = query.substr(pos + depth, index - pos - depth);

        // if it's the totals row, then we're done
        if (frontValue.compare("Total") == 0) {
            break;
        }

        if (frontValue.compare(matchStrings[depth]) == 0) {
            if (depth < matchStrings.size() - 1) {
                // we need to go deeper
                depth++;
            } else {
                // matched the first field
                index = query.find('\t', pos);

                // increment our position in the string
                pos = index + 1;

                // find the total count
                index = query.find('\t', pos);
                totalCount = std::stoi(query.substr(pos, index - pos));

                // increment our position in the string
                pos = index + 1;

                // skip ahead to next line
                index = query.find('\n', pos);
                pos = index + 1;

                // increment depth
                depth++;

                do {
                    // find the second field
                    index = query.find('\t', pos);
                    countName = query.substr(pos + depth, index - pos - depth);

                    // increment our position in the string
                    pos = index + 1;

                    // find the count
                    index = query.find('\t', pos);
                    tempCount = query.substr(pos, index - pos);

                    // increment our position in the string
                    pos = index + 1;

                    // find the total
                    index = query.find('\n', pos);
                    tempTotal = query.substr(pos, index - pos);

                    // increment our position in the string
                    pos = index + 1;

                    // store the second field and total in a pair
                    ret.emplace_back(countName, std::stod(tempTotal));

                    // continue until we've counted up all of the second field
                    totalCount -= std::stoi(tempCount);
                } while (totalCount != 0);

                // we're done since analyze() returns things in order
                break;
            }
        } else {
            // increment our position in the string to the next newline
            index = query.find('\n', pos);
            pos = index + 1;
        }
    }

    return ret;
}

/**
 * Parses a string of characters returning only digits and decimals as a double.
 *
 * @param p the string to parse
 * @return  the string as a double
 */
double RecordsManager::parseStringToDouble(std::string p) {
    QString parsedString;
    if (p.compare("") == 0) return 0.0;
    else {
        for (int i = 0; i < (int) p.length(); i++) {
            if (isdigit(p[i]) || p[i] == '.') {
                parsedString.append(p[i]);
            }
        }
    }
    return parsedString.toDouble();
}

/**
 * Takes a double and turns it into a string without the trailing zeros.
 * Also, truncates the value to 3 decimal places maximum.
 *
 * Code modified from:
 * http://stackoverflow.com/questions/15165502/double-to-string-without-scientific-notation-or-trailing-zeros-efficiently
 *
 * @param d the double to format
 * @return  the double as a string without trailing zeros
 */
std::string RecordsManager::removeTrailingZeros(double d) {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << d;
    std::string s = ss.str();

    s.erase(s.find_last_not_of('0') + 1, std::string::npos);

    if (s.back() == '.') {
        s.pop_back();
    }

    return s;
}

/**
 * Analyzes the data stored in the manager. Call this function if you don't want
 * any accumulator columns.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @param countCol      the header name of the column to count totals for
 * @param filterStart   the start of a character range with which to filter the top-level by
 * @param filterEnd     the end of a character range with which to filter the top-level by
 * @return              a formatted string with the analysis, can be used for TreeModel
 */
std::string RecordsManager::analyze(int startYear, int endYear, const std::vector<std::string> &sortFields, std::string countCol, char filterStart, char filterEnd) {
    return analyze(startYear, endYear, sortFields, list(0), 0, countCol, filterStart, filterEnd);
}

/**
 * Analyzes the data stored in the manager. Call this function if you want
 * accumulator columns.
 *
 * @param startYear     the start year in the range to search
 * @param endYear       the end year in the range to search
 * @param sortFields    the fields to sort by, in order
 * @param accs          the fields to accumulate at
 * @param currencyMask  a bit mask determining which accumulators should
 *                      be formatted as currency (e.g. a 1 in the first bit means
 *                      the first accumulator is currency)
 * @param countCol      the header name of the column to count totals for
 * @param filterStart   the start of a character range with which to filter the top-level by
 * @param filterEnd     the end of a character range with which to filter the top-level by
 * @return              a formatted string with the analysis, can be used for TreeModel
 */
std::string RecordsManager::analyze(int startYear, int endYear, const std::vector<std::string> &sortFields, const std::vector<std::string> &accs,
        int currencyMask, std::string countCol, char filterStart, char filterEnd) {
    std::string ret;
    int sum = 0;
    std::vector<BasicRecord*> records = findRecordsInRange(startYear, endYear);
    int m, n;

    // take the fields to sort by, find their header indices, and put them into an array
    std::vector<int> sortFieldIndices;
    for (m = 0; m < (int) sortFields.size(); m++) {
        sortFieldIndices.push_back(getHeaderIndex(sortFields[m]));
    }

    // take the fields to be accumulated, find their header indices, and put them into an array
    std::vector<int> accsIndices;
    for (n = 0; n < (int) accs.size(); n++) {
        accsIndices.push_back(getHeaderIndex(accs[n]));
    }

    // initialize array for the accumulated totals
    std::vector<double> accsTotals(n + 1, 0);

    // find the header index for the field to count (the number of records)
    int countColIndex = getHeaderIndex(countCol);

    // create a tree sorted by the first sort field
    StringTree sortedTree;
    std::string topLevelValue;
    for (size_t x = 0; x < records.size(); x++) {
        topLevelValue = records[x]->at(sortFieldIndices[0]);

        // check that the top-level value passes our filter before adding it
        if (topLevelValue[0] == '*' && filterStart == '*') {
            sortedTree.emplace(topLevelValue, records[x]);
        } else if (filterStart <= (topLevelValue[0] & ~0x20) && (topLevelValue[0] & ~0x20) <= filterEnd) {
            sortedTree.emplace(topLevelValue, records[x]);
        }
    }

    // analyze from there
    ret = analyze(sortedTree, sortFieldIndices, accsIndices, accsTotals, currencyMask, countColIndex, &sum, 0);

    ret += "Total\t" + std::to_string(sum);
    if (n != 0) {
        for (int i = 0; i < n; i++) {
            if (((1 << i) & currencyMask) == 0) {
                ret += '\t' + removeTrailingZeros(accsTotals[i]);
            } else {
                ret += '\t' + locale.toCurrencyString(accsTotals[i]).toStdString();
            }
        }
    }
    ret += '\n';

    // return the string representation of the analysis tree
    return ret;
}

/**
 * Analyzes the data stored in the manager. Internal use only.
 *
 * @param sortedTree    a previous sorted tree with which to continue analysis
 * @param sortFields    the header indices of the fields to sort by, in order
 * @param sortFields.size()       the number of fields to sort by
 * @param accs          the header indices of the fields to accumulate at
 * @param accs.size()         the number of accumulators
 * @param accsTotals    the current value in the accumulators
 * @param currencyMask  a bit mask determining which accumulators should
 * @param countCol      the header index of the column to count totals for
 * @param currCount     the current value in the totals count
 * @param depth         the current depth in the analysis tree
 * @return              a formatted string with the analysis, can be used for TreeModel
 */
std::string RecordsManager::analyze(StringTree sortedTree, const std::vector<int> &sortFields, const std::vector<int> &accs, std::vector<double> &accsTotals,
        int currencyMask, int countCol, int* currCount, int depth) {
    std::pair<StringTree::iterator, StringTree::iterator> uniqueValue;
    std::string value;
    std::string fieldString = "";
    std::string returnString = "";
    int fieldCount;
    std::vector<double> accsTotal;

    for (StringTree::iterator sortField = sortedTree.begin(); sortField != sortedTree.end(); sortField = uniqueValue.second) {
        // get a unique value for this field (header)
        value = sortField->first;

        // start the counter at 0
        fieldCount = 0;

        // set accumulators to 0
        accsTotal = std::vector<double>(accs.size() + 1, 0);

        // return nodes of the trees that match this value
        uniqueValue = sortedTree.equal_range(value);

        StringTree newSorted;
        // create a newly sorted tree using the next field (header) to sort by as its key
        for (StringTree::iterator itr = uniqueValue.first; itr != uniqueValue.second; itr++) {
            // only create the tree if we're not at the deepest level
            if ((int) sortFields.size() - 1 > depth) {
                newSorted.emplace(itr->second->at(sortFields[depth + 1]), itr->second);
            } else {
                // we're at the deepest level: find values for our accumulators
                for (int i = 0; i < (int) accs.size(); i++) {
                    accsTotal[i] += parseStringToDouble(itr->second->at(accs[i]));
                }
            }

            // if we want to accumulate this field, then count the number of records
            if (sortFields[depth] == countCol) {
                fieldCount++;
            }
        }

        // analyze at the next level, should we need to go deeper
        if ((int) sortFields.size() > depth) {
            returnString = analyze(newSorted, sortFields, accs, accsTotal, currencyMask, countCol, &fieldCount, depth + 1);
        }

        // add spaces to return string depending on how deep we are in the tree
        for (int i = 0; i < depth; i++) {
            fieldString += ' ';
        }

        // build return string
        fieldString += value + '\t' + ((fieldCount == 0) ? " " : std::to_string(fieldCount));
        for (int i = 0; i < (int) accs.size(); i++) {
            if (((1 << i) & currencyMask) == 0) {
                fieldString += '\t' + removeTrailingZeros(accsTotal[i]);
            } else {
                fieldString += '\t' + locale.toCurrencyString(accsTotal[i]).toStdString();
            }
        }
        fieldString += '\n' + returnString;

        // pass accumulators to upper level
        for (int i = 0; i < (int) accs.size(); i++) {
            accsTotals[i] += accsTotal[i];
        }

        // pass count total to upper level
        *currCount += fieldCount;
    }

    // pass return string to upper level
    return fieldString;
}
