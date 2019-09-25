#include "testtreeitem.h"

TestTreeItem::TestTreeItem(QObject *parent) : QObject(parent)
{

}

void TestTreeItem::childCount()
{
    QVariant q1("Hello");
    QVariant q2(854);
    QVariant q3(85.10);
    QVariant q4("Hello world!");

    QList<QVariant> list;
    list.append(q1);
    list.append(q2);
    list.append(q3);
    list.append(q4);

    TreeItem *null = nullptr;

    TreeItem *obj1 = new TreeItem(list, null);
    TreeItem *obj2 = new TreeItem(list, obj1);
    TreeItem *obj3 = new TreeItem(list, obj1);
    TreeItem *obj4 = new TreeItem(list, obj1);

    obj1->appendChild(obj2);
    obj1->appendChild(obj3);
    obj1->appendChild(obj4);

    QCOMPARE(obj1->childCount(), 3);
}

void TestTreeItem::checkData()
{
    QVariant q1(854);
    QList<QVariant> list;
    list.append(q1);
    TreeItem *null = nullptr;
    TreeItem *obj1 = new TreeItem(list, null);
    QVERIFY(obj1->data(0)== 854);

}

void TestTreeItem::checkData2()
{
    QVariant q1(-854);
    QList<QVariant> list;
    list.append(q1);
    TreeItem *null = nullptr;
    TreeItem *obj1 = new TreeItem(list, null);
    QVERIFY(obj1->data(0)== -854);
}

void TestTreeItem::checkData3()
{
    QVariant q1(85.4);
    QList<QVariant> list;
    list.append(q1);
    TreeItem *null = nullptr;
    TreeItem *obj1 = new TreeItem(list, null);
    QVERIFY(obj1->data(0)== 85.4);
}

/*
 * Test the number of columns in list */
void TestTreeItem::testNumberofRow()
{
    QVariant q1("Hello");
    QVariant q2(854);
    QVariant q3(85.10);
    QVariant q4("Hello world!");

    QList<QVariant> list;
    list.append(q1);
    list.append(q2);
    list.append(q3);
    list.append(q4);

    TreeItem *null = nullptr;

    TreeItem *obj1 = new TreeItem(list, null);
    TreeItem *obj2 = new TreeItem(list, obj1);
    TreeItem *obj3 = new TreeItem(list, obj1);
    TreeItem *obj4 = new TreeItem(list, obj3);

    obj1->appendChild(obj2);
    obj1->appendChild(obj3);
    obj1->appendChild(obj4);


    QCOMPARE(obj1->columnCount(), 4);
}

void TestTreeItem::testParentNode()
{
    QVariant q1(8);
    QVariant q2(0);

    QList<QVariant> list;
    QList<QVariant> list2;

    list.append(q1);
    list2.append(q2);

    TreeItem *null = nullptr;

    TreeItem *obj1 = new TreeItem(list, null);
    TreeItem *obj2 = new TreeItem(list2, obj1);

    QVERIFY(obj2->parentItem()->data(0)== 8);

}








