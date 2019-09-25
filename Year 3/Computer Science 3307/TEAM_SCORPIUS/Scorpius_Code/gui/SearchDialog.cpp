#include "gui/SearchDialog.h"
#include "ui_SearchDialog.h"
#include <QMessageBox>

SearchDialog::SearchDialog(QWidget *parent) :
    QDialog(parent, Qt::WindowTitleHint | Qt::WindowCloseButtonHint),
    ui(new Ui::SearchDialog)
{
    ui->setupUi(this);
}

SearchDialog::~SearchDialog()
{
    delete ui;
}

void SearchDialog::on_buttonBox_rejected() {
    done(0);
}

void SearchDialog::on_buttonBox_accepted() {
    QString firstName = ui->first_name->text();
    QString lastName = ui->last_name->text();

     if (firstName != "" && lastName != "") {
        done(1);
    }

    else {
        QMessageBox::critical(this, "", "Please enter both first name and last name.");
    }
}

QString SearchDialog::getFirstName() {
    return ui->first_name->text().toLower();
}

QString SearchDialog::getLastName() {
    return ui->last_name->text().toLower();
}
