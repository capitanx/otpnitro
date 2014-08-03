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

#ifndef GENBOOKDIALOG_H
#define GENBOOKDIALOG_H

#include <QDialog>

namespace Ui {
class genbookDialog;
}

class genbookDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit genbookDialog(QWidget *parent = 0);
    ~genbookDialog();
    
private slots:
    void on_btGenerate_clicked();

signals:
    void updateBooks();

private:
    Ui::genbookDialog *ui;
};

#endif // GENBOOKDIALOG_H
