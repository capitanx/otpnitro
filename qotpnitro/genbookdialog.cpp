#include "genbookdialog.h"
#include "ui_genbookdialog.h"

#include <page.h>

#include <QMessageBox>
#include <QApplication>

genbookDialog::genbookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::genbookDialog)
{
    ui->setupUi(this);
}

genbookDialog::~genbookDialog()
{
    delete ui;
}

void genbookDialog::on_btGenerate_clicked()
{
    ui->leBook->setText(ui->leBook->text().toUpper());
    QString id = ui->leBook->text();

    if(id.length() == 0)
        QMessageBox(QMessageBox::Critical, "Burn page", "Please, this field cannot be empty.", QMessageBox::Ok).exec();
    else
    {
        ui->lbBook->setText("Generating book...");
        ui->leBook->setEnabled(0);

        // Busy progress bar
        ui->pbBook->setEnabled(1);
        ui->pbBook->setMaximum(0);

        // Update GUI
        this->update();
        qApp->processEvents();

        // Generate book
        Page * page = new Page;
        page->generate(id.toStdString());
        delete page;

        // Update cbBooks in Main
        emit updateBooks();

        this->close();
    }
}
