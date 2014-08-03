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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class helpDialog;
}

class helpDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit helpDialog(QWidget *parent = 0);
    ~helpDialog();
    
private:
    Ui::helpDialog *ui;
};

#endif // HELPDIALOG_H
