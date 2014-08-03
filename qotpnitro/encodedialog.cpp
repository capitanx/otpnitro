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

#include "encodedialog.h"
#include "ui_encodedialog.h"

#include <text.h>

#include <QFileDialog>
#include <QTextStream>

#include <QMessageBox>

encodeDialog::encodeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::encodeDialog)
{
    ui->setupUi(this);
}

encodeDialog::~encodeDialog()
{
    delete ui;
}

void encodeDialog::on_tbDecBinary_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::ReadOnly);
    QTextStream fileTextTS(&fdText);
    QString fileText = fileTextTS.readAll().trimmed();

    Text * txt = new Text;

    int decLen = fileText.length() / 2;
    unsigned char * msgDec = new unsigned char[decLen];
    txt->decodeB26(msgDec, fileText.toStdString().c_str());
    msgDec[decLen] = 0x00;

    QString fileName2 = QFileDialog::getSaveFileName(this, tr("Save File"),".txt",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName2.length() < 1)
        return;

    QFile fdText2(fileName2);
    fdText2.open(QIODevice::WriteOnly);
    fdText2.write((const char*)msgDec);

    fdText2.close();
    fdText.close();

    delete txt;
    delete[] msgDec;
}

void encodeDialog::on_tbDecOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::ReadOnly);
    QTextStream fileText(&fdText);
    ui->teDecoded->setPlainText(fileText.readAll());
    fdText.close();
}

void encodeDialog::on_tbDecSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".txt",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::WriteOnly);
    fdText.write(ui->teDecoded->toPlainText().toStdString().c_str());
    fdText.close();
}

void encodeDialog::on_btEncode_clicked()
{
    Text * txt = new Text;

    string msgEnc = txt->encodeB26((unsigned char *)ui->teDecoded->toPlainText().toStdString().c_str(),(long)ui->teDecoded->toPlainText().length());
    ui->teEncoded->setPlainText(QString::fromStdString(msgEnc));

    delete txt;
}

void encodeDialog::on_tbEncBinary_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::ReadOnly);
    QTextStream fileTextTS(&fdText);
    QString fileText = fileTextTS.readAll().trimmed();

    Text * txt = new Text;
    string msgEnc = txt->encodeB26((unsigned char *)fileText.toStdString().c_str(),(long)fileText.length());

    QString fileName2 = QFileDialog::getSaveFileName(this, tr("Save File"),".txt",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName2.length() < 1)
        return;

    QFile fdText2(fileName2);
    fdText2.open(QIODevice::WriteOnly);
    fdText2.write(msgEnc.c_str());

    fdText2.close();
    fdText.close();

    delete txt;
}

void encodeDialog::on_tbEncOpen_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::ReadOnly);
    QTextStream fileText(&fdText);
    ui->teEncoded->setPlainText(fileText.readAll());
    fdText.close();
}

void encodeDialog::on_tbEncSave_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),".txt",tr("Text files (*.txt);;All files (*.*)"));

    if (fileName.length() < 1)
        return;

    QFile fdText(fileName);
    fdText.open(QIODevice::WriteOnly);
    fdText.write(ui->teEncoded->toPlainText().toStdString().c_str());
    fdText.close();
}

void encodeDialog::on_btDecode_clicked()
{
    Text * txt = new Text;

    int decLen = ui->teEncoded->toPlainText().length() / 2;
    unsigned char * msgDec = new unsigned char[decLen];

    txt->decodeB26(msgDec, ui->teEncoded->toPlainText().toStdString().c_str());
    string msgDecStr((char *)msgDec, decLen);

    ui->teDecoded->setPlainText(QString::fromStdString(msgDecStr));

    delete txt;
    delete[] msgDec;
}
