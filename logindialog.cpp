#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Zaloguj sie!"));
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(accepted()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(rejected()));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::accepted() {
    if(ui->loginLineEdit->text().isEmpty() || ui->addressLineEdit->text().isEmpty()) return;
    QTrio<QString,QHostAddress,int> trio;
    trio.first = ui->loginLineEdit->text();
    trio.second = QHostAddress(ui->addressLineEdit->text());
    trio.third = ui->portLineEdit->text().toInt();
    emit finished(trio);
    this->close();
    delete this;
}

void LoginDialog::rejected() {
    this->close();
    delete this;
}
