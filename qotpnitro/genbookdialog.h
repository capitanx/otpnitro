#ifndef GENBOOKDIALOG_H
#define GENBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class genbookDialog;
}

class genbookDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit genbookDialog(QWidget *parent = 0);
    ~genbookDialog();
    
private slots:
    void on_btGenerate_clicked();

signals:
    void updateBooks();

private:
    Ui::genbookDialog *ui;
};

#endif // GENBOOKDIALOG_H
