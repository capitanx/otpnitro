#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpdialog.h"
#include "ui_helpdialog.h"
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "encodedialog.h"
#include "ui_encodedialog.h"
#include "genbookdialog.h"
#include "ui_genbookdialog.h"
#include "burndialog.h"
#include "ui_burndialog.h"

#include <crypto.h>
#include <page.h>
#include <text.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // TOOLBAR CODE

    lbBook      = new QLabel;
    cbBook      = new QComboBox;
    lbFrom      = new QLabel;
    leFrom      = new QLineEdit;
    lbPage      = new QLabel;
    sbPage      = new QSpinBox;
    chkFormat   = new QCheckBox;

    lbBook->setText("BOOK  ");
    lbFrom->setText("FROM  ");
    leFrom->setMaximumWidth(60);
    lbPage->setText("PAGE  ");
    sbPage->setMaximum(9999);
    chkFormat->setText("Formatted msg  ");

    ui->mainToolBar->addWidget(lbBook);
    ui->mainToolBar->addWidget(cbBook);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(lbFrom);
    ui->mainToolBar->addWidget(leFrom);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(lbPage);
    ui->mainToolBar->addWidget(sbPage);
    ui->mainToolBar->addSeparator();
    ui->mainToolBar->addWidget(chkFormat);
    ui->mainToolBar->addSeparator();

    connect( chkFormat, SIGNAL(clicked()), this, SLOT(chkFormat_clicked()) );

    // INITIAL
    refreshBooks();

}

MainWindow::~MainWindow()
{
    // TOOLBAR
    delete lbBook;
    delete cbBook;
    delete lbFrom;
    delete leFrom;
    delete lbPage;
    delete sbPage;
    delete chkFormat;

    // MAIN
    delete ui;
}

void MainWindow::refreshBooks()
{
    Page  * page  = new Page;
    QString pageString = page->list().c_str();
    QStringList pageItems = pageString.split("\n");
    cbBook->clear();
    cbBook->addItems(pageItems);
    cbBook->removeItem(pageItems.length() -1);
    delete page;
}

// SLOTS

void MainWindow::Crypt()
{
    // From in uppercase
    leFrom->setText(leFrom->text().toUpper());

    QString id  = cbBook->itemText(cbBook->currentIndex());
    QString msg = ui->msgBox->toPlainText();
    QString snt = leFrom->text();

    if (id.length() == 0) {
        QMessageBox(QMessageBox::Critical, "Error", "You must select a book", QMessageBox::Ok).exec();
        return;
    }

    if (snt.length() == 0) {
        QMessageBox(QMessageBox::Critical, "Error", "Please, you must put an id in the field \"from\"", QMessageBox::Ok).exec();
        return;
    }

    if (msg.length() == 0) {
        QMessageBox(QMessageBox::Critical, "Error", "Empty message! rly?", QMessageBox::Ok).exec();
        return;
    }

    Page   * page   = new Page;
    Crypto * crypto = new Crypto;

    // Get a usable page
    int pnum = page->next(id.toStdString());
    if (pnum == -1) {
        QMessageBox(QMessageBox::Critical, "Error", "Not found pages in book", QMessageBox::Ok).exec();
        delete page;
        delete crypto;
        return;
    }

    // Set page num to selector
    sbPage->setValue(pnum);

    // Read page X from Book (RECV ID)
    string out = page->read(pnum,id.toStdString());

    // Crypto
    string encrypted = crypto->encrypt(msg.toStdString(),out);

    // Print page
    Text * txt = new Text;
    txt->create(pnum,id.toStdString(),snt.toStdString(),encrypted);
    ui->msgBox->setPlainText(QString::fromStdString(txt->print(1)));

    //TODO: If the user dont burn the page, put the number in red on statusbar
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Burn page", "Do you want to burn this page now? (recommended)", QMessageBox::Yes|QMessageBox::No).exec())
    {
        if (!page->burn(pnum,id.toStdString()))
            QMessageBox(QMessageBox::Critical, "Error", "Error burning this page", QMessageBox::Ok).exec();
    }

    delete txt;
    delete page;
    delete crypto;
}

void MainWindow::Decrypt()
{
    // From in uppercase
    leFrom->setText(leFrom->text().toUpper());

    QString id  = cbBook->itemText(cbBook->currentIndex());
    QString msg = ui->msgBox->toPlainText();
    QString snt = leFrom->text();
    int    pnum = sbPage->value();

    // Auto-Check if the msg is formated
    if ( (chkFormat->isChecked() != TRUE) && ( msg.contains("=")) )
    {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Formatted msg", "Is a formated msg? (XXX DE YYY N = AAAA =)", QMessageBox::Yes|QMessageBox::No).exec())
        {
            chkFormat->setChecked(1);
            leFrom->setEnabled(0);
            cbBook->setEnabled(0);
            sbPage->setEnabled(0);
        }
    }
    else
    {
        if (id.length() == 0) {
            QMessageBox(QMessageBox::Critical, "Error", "You must select a book", QMessageBox::Ok).exec();
            return;
        }
        if (snt.length() == 0) {
            QMessageBox(QMessageBox::Critical, "Error", "Please, you must put an id in the field \"from\"", QMessageBox::Ok).exec();
            return;
        }
        if (msg.length() == 0) {
            QMessageBox(QMessageBox::Critical, "Error", "Empty message! rly?", QMessageBox::Ok).exec();
            return;
        }
    }

    Page   * page   = new Page;
    Crypto * crypto = new Crypto;
    Text   * txt    = new Text;

    // Decrypts the msg formated / plain
    if (chkFormat->isChecked())
        txt->parse(msg.toStdString());
    else
        txt->create(pnum,id.toStdString(),snt.toStdString(),msg.toStdString());

    // Read page X from Book (RECV ID)
    string out = page->read(txt->page,txt->book);

    if (out.length() == 0) {
        QMessageBox(QMessageBox::Critical, "Error", "The page don't exist", QMessageBox::Ok).exec();
        delete page;
        delete crypto;
        delete txt;
        return;
    }

    // Crypto
    txt->replaceAll(txt->msg," ","");
    txt->msg = crypto->decrypt(txt->msg,out);

    // Print MSG
    ui->msgBox->setPlainText(QString::fromStdString(txt->print(0)));

    leFrom->setText(txt->from.c_str());
    cbBook->setCurrentIndex(cbBook->findText(txt->book.c_str()));
    sbPage->setValue(txt->page);

    //TODO: If the user dont burn the page, put the number in red on statusbar
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "Burn page", "Do you want to burn this page now? (recommended)", QMessageBox::Yes|QMessageBox::No).exec())
    {
        if (!page->burn(pnum,id.toStdString()))
            QMessageBox(QMessageBox::Critical, "Error", "Error burning this page.", QMessageBox::Ok).exec();
    }

    delete txt;
    delete page;
    delete crypto;
}

// ACTIONS

void MainWindow::chkFormat_clicked()
{
    if (chkFormat->isChecked()) {
        leFrom->setEnabled(0);
        cbBook->setEnabled(0);
        sbPage->setEnabled(0);
    } else {
        leFrom->setEnabled(1);
        cbBook->setEnabled(1);
        sbPage->setEnabled(1);
    }
}

void MainWindow::on_actionClear_triggered()
{
    ui->msgBox->clear();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::ReadOnly);
    QTextStream fileText(&fdText);
    ui->msgBox->setPlainText(fileText.readAll());
    fdText.close();
}

void MainWindow::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".txt",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::WriteOnly);
    fdText.write(ui->msgBox->toPlainText().toStdString().c_str());
    fdText.close();
}

void MainWindow::on_actionSettings_triggered()
{
    settingsDialog settingsDlg;

    QObject::connect(&settingsDlg, SIGNAL(updateBooks()), this, SLOT(refreshBooks()));

    settingsDlg.setModal(true);
    settingsDlg.exec();
}

void MainWindow::on_actionCrypt_triggered()
{
    Crypt();
}

void MainWindow::on_actionDecrypt_triggered()
{
    Decrypt();
}

void MainWindow::on_actionEncode_triggered()
{
    encodeDialog encodeDlg;
    encodeDlg.setModal(false);
    encodeDlg.exec();
}

void MainWindow::on_actionRefresh_books_triggered()
{
    refreshBooks();
}

void MainWindow::on_actionGenerate_book_triggered()
{
    genbookDialog genbookDlg;

    QObject::connect(&genbookDlg, SIGNAL(updateBooks()), this, SLOT(refreshBooks()));

    genbookDlg.setModal(false);
    genbookDlg.exec();
}

void MainWindow::on_actionBurn_page_triggered()
{
    burnDialog burnDlg;
    burnDlg.setModal(false);
    burnDlg.exec();
}

void MainWindow::on_actionHelp_triggered()
{
    helpDialog helpDlg;
    helpDlg.setModal(true);
    helpDlg.exec();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "OTPNitro", "<h1>OTP<i>Nitro</i> <small>0.5.0</small></h1><h3 align=center>Is a secure One Time Pad implementation to use on computers or as assistant on manual operations.</h3><p>This project is licensed under the <a href='http://www.gnu.org/licenses/gpl-3.0.html'>GPLv3</a> license.<br>More information in the <a href='https://code.haibane.org/crypto/otpnitro'>project page</a>.</p><p>2013-2014 (c) <a href='mailto:capi_x@haibane.org'>capi_x@haibane.org</a></p>");
}

void MainWindow::on_actionExit_triggered()
{
    this->close();
}
