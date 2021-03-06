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

#ifndef BURNDIALOG_H
#define BURNDIALOG_H

#include <QDialog>

namespace Ui {
class burnDialog;
}

class burnDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit burnDialog(QWidget *parent = 0);
    ~burnDialog();
    
private slots:
    void on_btBurn_clicked();

private:
    Ui::burnDialog *ui;
};

#endif // BURNDIALOG_H
