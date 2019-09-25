#ifndef CUSTOMSORT_H
#define CUSTOMSORT_H

#include <QDialog>
#include <QAbstractButton>
#include <QComboBox>

namespace Ui {
class CustomSort;
}

class CustomSort : public QDialog
{
    Q_OBJECT

public:
    explicit CustomSort(QWidget *parent = 0);
    ~CustomSort();
    void setFields(const std::vector<std::string> &headers);
    QStringList getSortFields();

private slots:
    void setNext(int fieldNum, int currentIndex);

    void on_field_0_currentIndexChanged(int index);
    void on_field_1_currentIndexChanged(int index);
    void on_field_2_currentIndexChanged(int index);
    void on_field_3_currentIndexChanged(int index);
    void on_field_4_currentIndexChanged(int index);
    void on_field_5_currentIndexChanged(int index);
    void on_field_6_currentIndexChanged(int index);
    void on_field_7_currentIndexChanged(int index);

    void on_buttonBox_rejected();
    void on_buttonBox_accepted();

private:
    Ui::CustomSort *ui;
    QStringList sortFields;
    int numFields;
    QList<QComboBox*> fieldBoxes;
};

#endif // CUSTOMSORT_H
