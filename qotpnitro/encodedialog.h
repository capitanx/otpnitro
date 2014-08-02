#ifndef ENCODEDIALOG_H
#define ENCODEDIALOG_H

#include <QDialog>

namespace Ui {
class encodeDialog;
}

class encodeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit encodeDialog(QWidget *parent = 0);
    ~encodeDialog();
    
private slots:
    void on_tbDecBinary_clicked();
    void on_tbDecOpen_clicked();
    void on_tbDecSave_clicked();
    void on_btEncode_clicked();
    void on_tbEncBinary_clicked();
    void on_tbEncOpen_clicked();
    void on_tbEncSave_clicked();
    void on_btDecode_clicked();

private:
    Ui::encodeDialog *ui;
};

#endif // ENCODEDIALOG_H
