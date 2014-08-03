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
