#ifndef TESTTREEITEM_H
#include <QtTest/QtTest>
#include "datamodel/TreeItem.h"
#define TESTTREEITEM_H

#include <QObject>

class TestTreeItem : public QObject
{
    Q_OBJECT
public:
    explicit TestTreeItem(QObject *parent = 0);

signals:

private slots:
    void childCount();
    void checkData();
    void checkData2();
    void checkData3();
    void testNumberofRow();
    void testParentNode();
};

#endif // TESTTREEITEM_H
