#include "burndialog.h"
#include "ui_burndialog.h"

#include <page.h>

#include <QMessageBox>

burnDialog::burnDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::burnDialog)
{
    ui->setupUi(this);

    // Init cbBook
    Page  * page  = new Page;
    QString pageString = page->list().c_str();
    QStringList pageItems = pageString.split("\n");
    ui->cbBook->clear();
    ui->cbBook->addItems(pageItems);
    ui->cbBook->removeItem(pageItems.length() -1);
    delete page;

}

burnDialog::~burnDialog()
{
    delete ui;
}

void burnDialog::on_btBurn_clicked()
{
    int    pnum = ui->sbPage->value();
    string id   = ui->cbBook->itemText(ui->cbBook->currentIndex()).toStdString();

    if(id.length() == 0) {
        QMessageBox(QMessageBox::Critical,    "Burn page", "Please, this field cannot be empty.",  QMessageBox::Ok).exec();;
        return;
    }

    Page  * page  = new Page;

    if (page->burn(pnum,id))
        QMessageBox(QMessageBox::Information, "Burn page", "Page burned successfully.", QMessageBox::Ok).exec();
    else
        QMessageBox(QMessageBox::Critical,    "Burn page", "This page doesn't exist.",  QMessageBox::Ok).exec();;

    delete page;
}
