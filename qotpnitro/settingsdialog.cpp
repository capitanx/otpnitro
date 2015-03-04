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

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <config.h>
#include <QMessageBox>
#include <QFileDialog>

settingsDialog::settingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settingsDialog)
{
    ui->setupUi(this);

    // Set max values
    ui->sbPages->setMaximum(99999999);
    ui->sbChars->setMaximum(99999999);

    // Set values
    Config * cfg = new Config;
    ui->lePath->setText(cfg->getPath());
    ui->sbPages->setValue(cfg->getPages());
    ui->sbChars->setValue(cfg->getChars());
    delete cfg;
}

settingsDialog::~settingsDialog()
{
    delete ui;
}

void settingsDialog::on_btSave_clicked()
{
    Config * cfg = new Config;

    cfg->setPath((char *)ui->lePath->text().toStdString().c_str());
    cfg->setPages(ui->sbPages->value());
    cfg->setChars(ui->sbChars->value());

    cfg->saveConfig();

    delete cfg;

    QMessageBox(QMessageBox::Information, "Settings", "Settings updated", QMessageBox::Ok).exec();

    // Update cbBooks in Main
    emit updateBooks();

    this->close();
}

void settingsDialog::on_btPath_clicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Select OTPNitro path"),ui->lePath->text(),QFileDialog::ShowDirsOnly|QFileDialog::DontResolveSymlinks);
    ui->lePath->setText(dirName + "/");
}
