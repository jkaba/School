#include "testqsortlistio.h"

TestQSortListIO::TestQSortListIO(QObject *parent) : QObject(parent)
{

}


//Following exampled in mainwindow.cpp lines 431-493
//Reading default sort oder of publications defined as 1
//Testing save and read parity
void TestQSortListIO::readWriteTest_01() {

    QList<QStringList> allFundOrders;
    QStringList defaultOrder;
    defaultOrder << "Default";

    defaultOrder << "Member Name" << "Funding Type" << "Peer Reviewed?" << "Status" << "Role" << "Title";

    // add default list to member variable
    allFundOrders << defaultOrder;

    // save the default for the user
    QSortListIO saveFundSort("fundsortorder.dat");
    saveFundSort.saveList(allFundOrders);

    QList<QStringList> result = saveFundSort.readList();

    QVERIFY(allFundOrders == result);
    std::remove("fundsortoder.dat");
}

//Simulating saving in the app for PRESENTATIONS
void TestQSortListIO::readWriteTest_02() {
#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"

    QList<QStringList> allPresOrders;
    QStringList defaultOrder;
    defaultOrder << "Default";
    /*********************************************
     * From mainwindow.cpp lines 450-461
    *********************************************/
    // specify default sort order
    defaultOrder << "Member Name" << "Type" << "Role" << "Title";

    // add default list to member variable
    allPresOrders << defaultOrder;

    // save the default for the user
    QSortListIO savePresSort(PRESORDER_SAVE);
    savePresSort.saveList(allPresOrders);
    /********************************************
     * End of case from mainwindow.cpp
     * *****************************************/

    QSortListIO result(PRESORDER_SAVE);

    QVERIFY(allPresOrders == result.readList());

    std::remove(PRESORDER_SAVE);


#undef FUNDORDER_SAVE
#undef PRESORDER_SAVE
#undef PUBORDER_SAVE
#undef TEACHORDER_SAVE

}

//Simulating saving in the app for PUBLICATIONS
void TestQSortListIO::readWriteTest_03() {
#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"

    QList<QStringList> allPubOrders;
    QStringList defaultOrder;
    defaultOrder << "Default";
    /*********************************************
     * From mainwindow.cpp lines 450-461
    *********************************************/

    //specify default sort order
    defaultOrder << "Member Name" << "Type" << "Role" << "Title";

    // add default list to member variable
    allPubOrders << defaultOrder;

    // save the default for the user
    QSortListIO savePubSort(PUBORDER_SAVE);
    savePubSort.saveList(allPubOrders);
    /********************************************
     * End of case from mainwindow.cpp
     * *****************************************/

    QSortListIO result(PUBORDER_SAVE);

    QVERIFY(allPubOrders == result.readList());

    std::remove(PUBORDER_SAVE);
    std::remove(FUNDORDER_SAVE);

#undef FUNDORDER_SAVE
#undef PRESORDER_SAVE
#undef PUBORDER_SAVE
#undef TEACHORDER_SAVE

}

//Simulating saving in the app for TEACH
void TestQSortListIO::readWriteTest_04() {
#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"

    QList<QStringList> allTeachOrders, allFundOrders;
    QStringList defaultOrder;
    defaultOrder << "Default";
    /*********************************************
     * From mainwindow.cpp original lines 450-461
    *********************************************/

    //specify default sort order
    defaultOrder << "Member Name" << "Program";

    // add default list to member variable
    allTeachOrders << defaultOrder;

    // save the default for the user
    QSortListIO saveTeachSort(PUBORDER_SAVE);
    saveTeachSort.saveList(allFundOrders);
    /********************************************
     * End of case from mainwindow.cpp
     * *****************************************/

    //Reading later
    QSortListIO result(TEACHORDER_SAVE);

    QEXPECT_FAIL("","Original code has typo", Continue);
    QVERIFY(allTeachOrders == result.readList());

    std::remove(PUBORDER_SAVE);
    std::remove(TEACHORDER_SAVE);


#undef FUNDORDER_SAVE
#undef PRESORDER_SAVE
#undef PUBORDER_SAVE
#undef TEACHORDER_SAVE

}

//Testing rewritten lines for mainwindow.cpp for saving TEACH
void TestQSortListIO::readWriteTest_05() {
#define FUNDORDER_SAVE  "fundsortorder.dat"
#define PRESORDER_SAVE  "pressortorder.dat"
#define PUBORDER_SAVE   "pubsortorder.dat"
#define TEACHORDER_SAVE "teachsortorder.dat"

    QList<QStringList> allTeachOrders;
    QStringList defaultOrder;
    defaultOrder << "Default";
    /*********************************************
     * From mainwindow.cpp REWRITTEN lines 450-461
    *********************************************/

    //specify default sort order
    defaultOrder << "Member Name" << "Program";

    // add default list to member variable
    allTeachOrders << defaultOrder;

    // save the default for the user
    QSortListIO saveTeachSort(TEACHORDER_SAVE);
    saveTeachSort.saveList(allTeachOrders);
    /********************************************
     * End of case from mainwindow.cpp
     * *****************************************/

    //Reading later
    QSortListIO result(TEACHORDER_SAVE);

    QVERIFY(allTeachOrders == result.readList());

    std::remove(TEACHORDER_SAVE);


#undef FUNDORDER_SAVE
#undef PRESORDER_SAVE
#undef PUBORDER_SAVE
#undef TEACHORDER_SAVE
}
