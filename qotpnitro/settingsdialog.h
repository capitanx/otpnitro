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

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class settingsDialog;
}

class settingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit settingsDialog(QWidget *parent = 0);
    ~settingsDialog();
    
private slots:
    void on_btSave_clicked();
    void on_btPath_clicked();

signals:
    void updateBooks();

private:
    Ui::settingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
