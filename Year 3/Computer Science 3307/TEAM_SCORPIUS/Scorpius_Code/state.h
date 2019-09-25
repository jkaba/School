#ifndef STATE_H
#define STATE_H

#include <QDialog>

namespace Ui {
class state;
}

class state : public QDialog
{
    Q_OBJECT

public:
    explicit state(QWidget *parent = 0);
    ~state();

private:
    Ui::state *ui;
};

#endif // STATE_H
