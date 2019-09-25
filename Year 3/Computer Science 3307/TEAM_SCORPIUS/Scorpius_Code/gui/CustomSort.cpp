#include "gui/CustomSort.h"
#include "ui_customsort.h"
#include <QMessageBox>

CustomSort::CustomSort(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::CustomSort)
{
    ui->setupUi(this);
}

CustomSort::~CustomSort()
{
    delete ui;
}

void CustomSort::setFields(const std::vector<std::string> &headers) {
    numFields = (int) headers.size();
    fieldBoxes << ui->field_0;
    fieldBoxes << ui->field_1;
    fieldBoxes << ui->field_2;
    fieldBoxes << ui->field_3;
    fieldBoxes << ui->field_4;
    fieldBoxes << ui->field_5;
    fieldBoxes << ui->field_6;
    fieldBoxes << ui->field_7;
    fieldBoxes << ui->field_8;

    // hide unnessary field boxes
    for (int i = numFields; i < fieldBoxes.size(); i++) {
        fieldBoxes[i]->setHidden(true);
    }

    // add items to field_1 drop down list
    for (int i = 0; i < (int) headers.size(); i++) {
        ui->field_0->addItem(QString::fromStdString(headers[i]));
    }
}

QStringList CustomSort::getSortFields() {   
    return sortFields;
}

void CustomSort::setNext(int fieldNum, int currentIndex) {
    for (int i=fieldNum+1; i<numFields; i++) {
        fieldBoxes.at(i)->clear();
    }

    for (int i=0; i<fieldBoxes[fieldNum]->count(); i++) {
        fieldBoxes[fieldNum+1]->addItem(fieldBoxes[fieldNum]->itemText(i));
    }
    fieldBoxes[fieldNum+1]->removeItem(currentIndex);
}

void CustomSort::on_field_0_currentIndexChanged(int index) { setNext(0, index);}
void CustomSort::on_field_1_currentIndexChanged(int index) { setNext(1, index);}
void CustomSort::on_field_2_currentIndexChanged(int index) { setNext(2, index);}
void CustomSort::on_field_3_currentIndexChanged(int index) { setNext(3, index);}
void CustomSort::on_field_4_currentIndexChanged(int index) { setNext(4, index);}
void CustomSort::on_field_5_currentIndexChanged(int index) { setNext(5, index);}
void CustomSort::on_field_6_currentIndexChanged(int index) { setNext(6, index);}
void CustomSort::on_field_7_currentIndexChanged(int index) { setNext(7, index);}


void CustomSort::on_buttonBox_rejected() {
    done(0);
}

void CustomSort::on_buttonBox_accepted() {
    sortFields.clear();

    if (ui->sort_name->text()!="") {
        if (fieldBoxes.at(0)->currentText()!="") {
            if (!fieldBoxes.at(0)->currentText().contains("Date")) {
                sortFields << ui->sort_name->displayText();

                for (int i=0; i<numFields; i++) {
                    QString currentText = fieldBoxes.at(i)->currentText();
                    if (currentText!="") {
                        sortFields << currentText;
                    }
                }
                done(1);
            } else {
                QMessageBox::critical(this, "", "Sorry, cannot sort by date first.");
            }
        } else {
            QMessageBox::critical(this, "", "Please select at least 1 sort field.");
        }
    } else {
        QMessageBox::critical(this, "", "Please enter a name.");
    }
}
