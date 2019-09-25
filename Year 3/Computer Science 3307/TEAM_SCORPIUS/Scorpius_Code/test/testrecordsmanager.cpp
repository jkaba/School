#include "testrecordsmanager.h"

TestRecordsManager::TestRecordsManager(QObject *parent) : QObject(parent)
{

}

//Following example in mainwindow.cpp line 197
//Creating a RecordsManager of Teaching_sample.csv
//to test on
RecordsManager createTeachRecordsManager(){
    vector<string> TEACH_MANFIELDS = {"Member Name", "Start Date", "Program"};


    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
    vector<string> header(reader.getHeaders());
    RecordsManager manager(&header);

    //load in data into the manager, with the date as the key
    int sortHeaderIndex = manager.getHeaderIndex("Start Date");
    vector<vector<string>> teachData = reader.getData();
    vector<vector<string>*> f_errs;

    for (int i = 0; i < (int) teachData.size(); i++) {

        int yrIndex = manager.getHeaderIndex("Start Date");
        int year;
        sscanf(teachData[i][yrIndex].c_str(), "%4d", &year);
        teachData[i][yrIndex] = std::to_string(year);

        manager.addRecord(reader.parseDateString(teachData[i][sortHeaderIndex]), &teachData[i]);
    }

    return manager;
}

//Testing findRecordsInRange with valid date
void TestRecordsManager::Between_Dates_01(){

    RecordsManager manager = createTeachRecordsManager();
    vector<BasicRecord*> records = manager.findRecordsInRange(0,30000);

    QVERIFY(records.size() != 0 );
}

//Testing findRecordsInRange with single year
void TestRecordsManager::Between_Dates_02(){

    RecordsManager manager = createTeachRecordsManager();
    vector<BasicRecord*> records = (manager.findRecordsInRange(1998,1998));

    QVERIFY(records.size() == 0 );
}

//Testing findRecordsInRange and findRecord for same result
void TestRecordsManager::Between_Dates_03(){
    RecordsManager manager = createTeachRecordsManager();

    vector<BasicRecord*> records1 = manager.findRecordsInRange(2000,2000);
    vector<BasicRecord*> records2 = manager.findRecord(2000);

    QVERIFY(records1 == records2 );
}

//Testing findRecordsInRange for invalid range
void TestRecordsManager::Between_Dates_04(){
    RecordsManager manager = createTeachRecordsManager();

    vector<BasicRecord*> records = manager.findRecordsInRange(2000,1995);

    QVERIFY(records == manager.findRecordsInRange(1995,2000));
}

//Confirming headers
void TestRecordsManager::Header_Confirm() {
//    CSVReader reader("../Project Information/Sample Data/Teaching_sample.csv");
//    RecordsManager manager(&reader.getHeaders());

//    QVERIFY(manager.getHeaders() == reader.getHeaders());
}

//Testing finding column number with invalid search term
void TestRecordsManager::Column_Number_Confirm_01() {
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.getHeaderIndex("Publication Satus") == -1);
}

//Testing finding column number with valid search
void TestRecordsManager::Column_Number_Confirm_02(){
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.getHeaderIndex("ID") == 3);
}

//Testing finding column number with valid search, last column
void TestRecordsManager::Column_Number_Confirm_03(){
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.getHeaderIndex("Total Hours") == 27);
}

//Testing list function, passing 0 arguments
void TestRecordsManager::List_Test_01(){
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.list(0).size() == 0);
}

//Passing matching # of arguments
void TestRecordsManager::List_Test_02(){
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.list(2,"a","b").size() == 2);
}

//Passing n=0, but 2 string arguments
//Expect 0
void TestRecordsManager::List_Test_03(){
    RecordsManager manager = createTeachRecordsManager();

    QVERIFY(manager.list(0,"a","b").size() == 0);
}

//Creating QString from a 0 result search
void TestRecordsManager::CreateQStringTestTeaching_01(){
    RecordsManager manager = createTeachRecordsManager();
    std::vector<std::string> sortFields = manager.list(2, "Member Name", "Faculty");

    QString str = manager.createQStringForTeaching(0,0,sortFields, 'A', 'Z');
    QCOMPARE(str, QString("Total\t0\t0\t0\n"));
}
