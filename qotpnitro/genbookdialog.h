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

#ifndef GENBOOKDIALOG_H
#define GENBOOKDIALOG_H

#include <QDialog>
#include <QThread>

namespace Ui {
class genbookDialog;
}

class genBook : public QThread
{
    Q_OBJECT

public:
    QString  id;

protected:
    void run();
};

class genbookDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit genbookDialog(QWidget *parent = 0);
    ~genbookDialog();
    QTimer  *timer;
    
private slots:
    void on_btGenerate_clicked();
    void bookGen_finished();
    void pb_update();

    void on_btCancel_clicked();

signals:
    void updateBooks();

private:
    Ui::genbookDialog *ui;
    QString  id;
    genBook *gen;

};

#endif // GENBOOKDIALOG_H
