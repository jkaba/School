#include "ui_ErrorEditDialog.h"
#include "ErrorEditDialog.h"

#include <QTableWidgetItem>
#include <QStringList>
#include <QDebug>
#include <QBrush>
#include <QColor>
#include <QAbstractButton>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QDebug>
#include <QFile>

/*
 * Load data contained in the errors vector into a QWidgetTable
 * Fields will be marked red and editable if they are a mandatory field
 * and editable.  Otherwise all other fields will not be editable.
 * Clicking Save in the dialog will return the corrected entries to the main
 * program through the errors parameter.  If not all marked fields are edited
 * then a warning message will be displayed.  If cancel is clicked all errors
 * are discarded.
 */
ErrorEditDialog::ErrorEditDialog(QWidget *parent,
                                 std::vector<std::vector<std::string>*>& errors,
                                 std::vector<std::string>& headers,
                                 std::vector<std::string>& mandatory) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    errorList(errors),
    headerList(headers),
    mandatoryList(mandatory),
    ui(new Ui::ErrorEditDialog)
{

    ui->setupUi(this);
    ui->tableWidget->setRowCount((int) errors.size());
    ui->tableWidget->setColumnCount((int) headers.size());

    QStringList listHeaders;
    for (int i = 0; i < (int) headers.size(); i++) {
        listHeaders << headers[i].c_str();
    }

    ui->tableWidget->setHorizontalHeaderLabels(listHeaders);
    QTableWidgetItem* item;
    QBrush brush(QColor(255, 0, 0, 100));
    std::vector<std::vector<std::string>*>::iterator it;
    int row = 0;
    for (it = errors.begin(); it != errors.end(); it++) {
        for (int col = 0; col < (int) headers.size() && col < (int) (*it)->size(); col++) {
            item = new QTableWidgetItem();
            Qt::ItemFlags flag = item->flags();
            item->setFlags(Qt::ItemIsSelectable);
            item->setText((*it)->at(col).c_str());
            for (int i = 0; i < (int) mandatory.size(); i++) {
                if (mandatory[i].compare(headers.at(col)) == 0
                        && (*it)->at(col).compare("") == 0) {
                    item->setBackground(brush);
                    item->setFlags(flag);
                }
            }
            ui->tableWidget->setItem(row, col, item);
        }
        row++;
    }
}

//Clean up allocated memory for the table items
ErrorEditDialog::~ErrorEditDialog()
{
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
            delete ui->tableWidget->item(i,j);
        }
    }
    delete ui;
}

//Save the new data entered by the user via the error reference var
void ErrorEditDialog::saveData() {
    for (int row = 0; row < ui->tableWidget->rowCount(); row++) {
        for (int col = 0; col < ui->tableWidget->columnCount() && col < (int) errorList[row]->size(); col++) {
            std::vector<std::string>::iterator it = errorList[row]->begin()+col;
            if (errorList[row]->at(col).compare("") == 0) {
                it = errorList[row]->erase(it);
                errorList[row]->insert(it, ui->tableWidget->item(row, col)->text().toStdString());
            }
        }
    }
    accept();
}

void ErrorEditDialog::saveDataHelper()
{
    QFile f( "test.csv" );

    bool flag = 1;

    QStringList list;
    QString text;

    foreach(const std::string value, headerList){
        text = QString::fromStdString(value);
        list << text;
    } // put everything in a QStringList


    if (f.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream out( &f );
        out << list.join(",") << "\r\n"; // join everything with a comma and a new line


        for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
        {
            list.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {
                text = ui->tableWidget->item( r, c )->text();

                if (text.contains(QRegExp(",|\r\n"))) {
                    list << ("\"" + text + "\"");
                } else if (text.contains("\"")) {
                    list << text.replace("\"", "”");
                } else {
                    list << text;
                }

            }
            out << list.join(",") << "\r\n";
        }
        f.close();
    }

}




void ErrorEditDialog::on_save_clicked()
{


    bool search = true;
    //check if mandatory fields have been filled
    for (int row = 0; row < ui->tableWidget->rowCount() && search; row++) {
        for (int j = 0; j < (int) mandatoryList.size() && search; j++) {
            std::vector<std::string>::iterator it = std::find(headerList.begin(), headerList.end(), mandatoryList[j]);
            int col = it - headerList.begin();
            QTableWidgetItem* item = ui->tableWidget->item(row, col);
        }
    }

    saveDataHelper();
    saveData();
}


void ErrorEditDialog::on_cancel_clicked()
{
    reject();
}


void ErrorEditDialog::on_find_clicked()
{
    QTableWidgetItem *item = nullptr;
    item = ui->tableWidget->currentItem();

    int itemRow;
    int itemColumn;


    /*If the pointer exist then call the methods else put the row and column at 0
     * */

    if(item){
        itemRow = item->row();
        itemColumn = item->column();
        item->setSelected(false);

    }else{
        itemRow = 0;
        itemColumn = 0;
    }

    bool end = on_find_clicked_helper(itemRow, itemColumn); // look for empty field from the front

    if(end){ // if it didn't find any
        on_find_clicked_helper(0, 0); // make sure that all fields are empty
    }


}

bool ErrorEditDialog::on_find_clicked_helper(int itemRow, int itemColumn){
    QTableWidgetItem *item = nullptr;
    QString itemText;

    bool flag= 1;

    for(int row=0; row < ui->tableWidget->rowCount(); ++row){
        for(int col=0; col < ui->tableWidget->columnCount(); ++col){
            if(flag){
                row = itemRow;
                col = itemColumn;
                flag = 0; // put the flag off after the first loop
            }
            item = ui->tableWidget->item(row, col);

            itemText = item->text();
            QString header_Q =ui->tableWidget->model()->headerData(col, Qt::Horizontal).toString();
            std::string header = header_Q.toStdString(); // switch the QString to std:string

            /*If it is a mandatory field and there is nothing in it
         * */
            //(header.compare("Start Date") ==0)||(header.compare("Division") ==0)||(header.compare("Department") ==0)
            if(!(row == itemRow && col == itemColumn) && itemText.isEmpty()){
                for(int i = 0 ;i < mandatoryList.size(); ++i){
                    if(mandatoryList[i].compare(header) == 0 ){
                        ui->tableWidget->setCurrentCell(row, col);
                        item->setSelected(true);
                        return false; //if it not the end return false
                    }

                }

            }
        }
    }
    return true; // if at end return true


}

