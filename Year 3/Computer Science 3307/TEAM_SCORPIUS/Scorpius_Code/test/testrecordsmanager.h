#ifndef TESTRECORDSMANAGER_H
#include "database/RecordsManager.h"
#include "database/CSVReader.h"
#include <QtTest/QtTest>
#define TESTRECORDSMANAGER_H

#include <QObject>

using namespace std;

class TestRecordsManager : public QObject
{
    Q_OBJECT
public:
    explicit TestRecordsManager(QObject *parent = 0);

signals:

private slots:
    void Between_Dates_01();
    void Between_Dates_02();
    void Between_Dates_03();
    void Between_Dates_04();
    void Header_Confirm();
    void Column_Number_Confirm_01();
    void Column_Number_Confirm_02();
    void Column_Number_Confirm_03();
    void List_Test_01();
    void List_Test_02();
    void List_Test_03();
    void CreateQStringTestTeaching_01();
};

#endif // TESTRECORDSMANAGER_H
