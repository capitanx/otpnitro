/**
 * OTPNitro
 *
 *  Copyright 2014-2015 by capi_x <capi_x@haibane.org>
 *
 *  Licensed under GNU General Public License 3.0 or later.
 *  Some rights reserved. See COPYING, AUTHORS.
 *
 * @license GPL-3.0 <http://www.gnu.org/licenses/gpl-3.0.txt>
 */

#include "genbookdialog.h"
#include "ui_genbookdialog.h"

#include <page.h>
#include <config.h>

#include <QRegExpValidator>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>

genbookDialog::genbookDialog(QWidget *parent) :
    QDialog(parent, Qt::CustomizeWindowHint | Qt::WindowTitleHint),
    ui(new Ui::genbookDialog)
{
    gen = new genBook();
    connect(gen, SIGNAL(finished()), this, SLOT(bookGen_finished()));

    ui->setupUi(this);

    QRegExp bookRegex("([A-Za-z]+)");
    QRegExpValidator *bookValidator = new QRegExpValidator(bookRegex, this);
    ui->leBook->setValidator(bookValidator);
    ui->leBook->setMaxLength(5);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(pb_update()));
}

genbookDialog::~genbookDialog()
{
    delete timer;
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

        // Update GUI
        this->update();
        qApp->processEvents();

        // Generate book
//        ui->btCancel->setEnabled(0);
        ui->btGenerate->setEnabled(0);
        gen->id = this->id;
        gen->start();
        timer->start(1000);
    }
}

void genbookDialog::pb_update()
{
    Config *cfg = new Config();
    int maxPages = cfg->getPages();
    delete cfg;

    Page * page = new Page;
    int currPage = 0;
    currPage = page->last(id.toStdString());
    delete page;

    ui->pbBook->setValue((currPage*100)/maxPages);
}

void genbookDialog::bookGen_finished()
{
    // Exit without action in a blank ID
    if (this->id == "")
        return;

    // Completed, set pb to 100%
    ui->pbBook->setValue(100);

    // Update GUI
    this->update();
    qApp->processEvents();

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

void genbookDialog::on_btCancel_clicked()
{
    if (gen->isRunning())
    {
        if (QMessageBox::Yes == QMessageBox(QMessageBox::Critical, "Generating book", "Do you want cancel the process?\nYou can continue later generating the same book again.", QMessageBox::Yes|QMessageBox::No).exec())
        {
            // Terminate threads
            gen->terminate();
            timer->stop();

            // Burn the last generated page (maybe incomplete?)
            Page * page = new Page;
            page->burn(page->last(this->id.toStdString()),this->id.toStdString());

            // ID to blank (used in the qthread action)
            this->id = "";

            // Clean the house
            delete page;
            this->close();
        }
    }
    else
    {
        this->close();
    }
}
