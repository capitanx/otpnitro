/**
 * OTPNitro
 *
 *  Copyright 2014 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later.
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QCheckBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void chkFormat_clicked();
    void refreshBooks();
    void Crypt();
    void Decrypt();
    
private slots:
    void on_actionClear_triggered();
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSettings_triggered();
    void on_actionCrypt_triggered();
    void on_actionDecrypt_triggered();
    void on_actionEncode_triggered();
    void on_actionRefresh_books_triggered();
    void on_actionGenerate_book_triggered();
    void on_actionBurn_page_triggered();
    void on_actionHelp_triggered();
    void on_actionAbout_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;

    QLabel      *lbBook;
    QComboBox   *cbBook;
    QLabel      *lbFrom;
    QLineEdit   *leFrom;
    QLabel      *lbPage;
    QSpinBox    *sbPage;
    QCheckBox   *chkFormat;

};

#endif // MAINWINDOW_H
