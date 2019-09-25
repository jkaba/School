#ifndef TESTQSORTLISTIO_H
#include <QDataStream>
#include <QFile>
#include <QStringList>
#include "database/QSortListIO.h"
#include <QtTest/QtTest>
#define TESTQSORTLISTIO_H

#include <QObject>

class TestQSortListIO : public QObject
{
    Q_OBJECT
public:
    explicit TestQSortListIO(QObject *parent = 0);

signals:

private slots:
    void readWriteTest_01();
    void readWriteTest_02();
    void readWriteTest_03();
    void readWriteTest_04();
    void readWriteTest_05();

};

#endif // TESTQSORTLISTIO_H
