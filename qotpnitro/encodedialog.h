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
