#ifndef TESTCSVREADER_H
#include "database/CSVReader.h"
#include "database/RecordsManager.h"
#include <QtTest/QtTest>
#define TESTCSVREADER_H

#include <QObject>

class TestCSVReader : public QObject
{
    Q_OBJECT
public:
    explicit TestCSVReader(QObject *parent = 0);

signals:

private slots:
    void parseDateString();
    void CSV_READER_TEST_01();
    void CSV_READER_TEST_02();
    void CSV_READER_TEST_03();
    void CSV_READER_TEST_04();
    void CSV_READER_TEST_05();
    void CSV_READER_TEST_06();
    void CSV_READER_TEST_07();
    void CSV_READER_TEST_08();
    void Last_Field_Null();
};

#endif // TESTCSVREADER_H
