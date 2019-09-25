#include <iostream>
#include <stdio.h>
#include <QApplication>
#include <QTreeView>

#include "gui/mainwindow.h"
#include "test/TestCSVReader.h"
#include "test/testtreeitem.h"
#include "test/testrecordsmanager.h"
#include "test/testqsortlistio.h"


using namespace std;

int main(int argc, char *argv[]) {

    int test = 0;

if(test){
    TestCSVReader *test1 = new TestCSVReader();
    QTest::qExec(test1);
    TestTreeItem *test2 = new TestTreeItem();
    QTest::qExec(test2);
    TestRecordsManager *test3 = new TestRecordsManager();
    QTest::qExec(test3);
    TestQSortListIO *test4 = new TestQSortListIO();
    QTest::qExec(test4);
}


else {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}

}

