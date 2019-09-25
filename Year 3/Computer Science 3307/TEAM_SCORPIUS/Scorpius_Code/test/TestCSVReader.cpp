#include "test/TestCSVReader.h"



TestCSVReader::TestCSVReader(QObject *parent) : QObject(parent)
{

}


/*
 * This function is suppose to return the year with 4 numbers.
 * */

void TestCSVReader::parseDateString(){

    CSVReader temp;
    QVERIFY(temp.parseDateString("214200")== 2142);
}

void TestCSVReader::CSV_READER_TEST_01(){
    using namespace std;
CSVReader reader("../Project Information/Sample Data/Grants_expanded.csv");
vector<string> header = reader.getHeaders();

QVERIFY(header.size()!=0);

}


void TestCSVReader::CSV_READER_TEST_02(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/GrantsClinicalFunding_sample.csv");
    vector<string> header = reader.getHeaders();

QVERIFY(header.size()!=0);

}


void TestCSVReader::CSV_READER_TEST_03(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/Presentations_expanded.csv");
        vector<string> header = reader.getHeaders();

QVERIFY(header.size()!=0);

}


void TestCSVReader::CSV_READER_TEST_04(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
        vector<string> header = reader.getHeaders();

QVERIFY(header.size()!=0);

}


void TestCSVReader::CSV_READER_TEST_05(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
        vector<string> header = reader.getHeaders();

QVERIFY(header.size()!=0);

}


void TestCSVReader::CSV_READER_TEST_06(){
    using namespace std;
    CSVReader reader("NO FILE");
        vector<string> header = reader.getHeaders();

QVERIFY(header.size()==0);

}

void TestCSVReader::CSV_READER_TEST_07(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/Presentations_sample.csv");
        vector< vector<string> > all_data = reader.getData();

QVERIFY(all_data.size()!=0);

}

void TestCSVReader::CSV_READER_TEST_08(){
    using namespace std;
    CSVReader reader("../Project Information/Sample Data/Program_Teaching_expanded.csv");
    vector< vector<string> > all_data = reader.getData();
    QVERIFY(all_data.size()!=0);

}

void TestCSVReader::Last_Field_Null(){
    using namespace std;

    std::vector<std::string> PUBS_MANFIELDS = {"Member Name", "Type", "Status Date", "Role", "Title", "Department", "Division"};

    CSVReader reader("../Project Information/Sample Data/Publications_expanded_debugging.csv");
    vector< vector<string> > pubData = reader.getData();
    vector<string> header = reader.getHeaders();
    RecordsManager *pubdb;
    pubdb = new RecordsManager(&header);
    std::vector<std::vector<std::string>*> f_errs;

    for (int i = 0; i < (int) pubData.size(); i++) {
        for (int j = 0; j < PUBS_MANFIELDS.size(); j++) {
            int index = pubdb->getHeaderIndex(PUBS_MANFIELDS[j]);
            if (pubData[i][index].compare("") == 0) {
                f_errs.push_back(&pubData[i]);
                break;
            }
        }
    }

    QVERIFY(f_errs.size() != 0);

}
