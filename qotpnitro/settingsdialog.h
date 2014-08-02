#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();
    
private slots:
    void on_btSave_clicked();
    void on_btPath_clicked();

signals:
    void updateBooks();

private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
