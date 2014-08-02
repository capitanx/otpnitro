#ifndef BURNDIALOG_H
#define BURNDIALOG_H

#include <QDialog>

namespace Ui {
class burnDialog;
}

class burnDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit burnDialog(QWidget *parent = 0);
    ~burnDialog();
    
private slots:
    void on_btBurn_clicked();

private:
    Ui::burnDialog *ui;
};

#endif // BURNDIALOG_H
