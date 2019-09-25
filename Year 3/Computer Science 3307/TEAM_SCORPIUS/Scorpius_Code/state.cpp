#include "state.h"
#include "ui_state.h"

state::state(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::state)
{
    ui->setupUi(this);
}

state::~state()
{
    delete ui;
}
