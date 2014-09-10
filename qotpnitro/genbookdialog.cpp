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

#include "genbookdialog.h"
#include "ui_genbookdialog.h"

#include <page.h>

#include <QMessageBox>
#include <QApplication>

QString id;
genBook * gen;

genbookDialog::genbookDialog(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint),
    ui(new Ui::genbookDialog)
{
    gen = new genBook();
    connect(gen, SIGNAL(finished()), this, SLOT(bookGen_finished()));

    ui->setupUi(this);
}

genbookDialog::~genbookDialog()
{
    delete gen;
    delete ui;
}

void genbookDialog::on_btGenerate_clicked()
{
    ui->leBook->setText(ui->leBook->text().toUpper());
    id = ui->leBook->text();

    if(id.length() == 0)
        QMessageBox(QMessageBox::Critical, "Burn page", "Please, this field cannot be empty.", QMessageBox::Ok).exec();
    else
    {
        ui->lbBook->setText("Generating... it can take 30min!");
        ui->leBook->setEnabled(0);

        // Busy progress bar
        ui->pbBook->setEnabled(1);
        ui->pbBook->setMaximum(0);

        // Update GUI
        this->update();
        qApp->processEvents();

        // Generate book
        gen->start();

        ui->btCancel->setEnabled(0);
        ui->btGenerate->setEnabled(0);
    }
}

void genbookDialog::bookGen_finished()
{
    QMessageBox(QMessageBox::Information, "OTPNitro GUI", "Book generated :)", QMessageBox::Ok).exec();

    // Update cbBooks in Main
    emit updateBooks();
    this->close();
}

void genBook::run()
{
    Page * page = new Page;
    page->generate(id.toStdString());
    delete page;
}
