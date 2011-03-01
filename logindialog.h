#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QtNetwork/QHostAddress>

#include "qtrio.h"

namespace Ui {
    class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT
signals:
    void finished(QTrio<QString,QHostAddress,int>);
public:
    LoginDialog(QWidget *parent = 0);
    ~LoginDialog();

private:
    Ui::LoginDialog *ui;
private slots:
    void accepted();
    void rejected();
};

#endif // LOGINDIALOG_H
