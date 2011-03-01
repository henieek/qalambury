#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->chatTimeout = true;
    this->connected = false;
    this->currColorId = 2; // czarny
    this->lastColorButton = ui->blackPushButton;
    this->setWindowTitle(tr("Qalambury"));
    this->graphicsScene = new QGraphicsScene();
    ui->graphicsView->setScene(graphicsScene);
    this->currentPen.setColor(QColor("black"));

    connect(ui->graphicsView,SIGNAL(drawPoint(QPoint)),this,SLOT(drawPoint(QPoint)));
    connect(ui->clearPushButton,SIGNAL(clicked()),this,SLOT(clearView()));
    connect(ui->redPushButton,SIGNAL(clicked()),this,SLOT(switchColor()));
    connect(ui->greenPushButton,SIGNAL(clicked()),this,SLOT(switchColor()));
    connect(ui->blackPushButton,SIGNAL(clicked()),this,SLOT(switchColor()));
    connect(ui->sendMessagePushButton,SIGNAL(clicked()),this,SLOT(sendMessage()));
    connect(ui->chatLineEdit,SIGNAL(returnPressed()),this,SLOT(sendMessage()));

    this->socket = new KalSocket();
    this->chatTimer = new QTimer();

    connect(socket,SIGNAL(connected()),this,SLOT(connectionSuccess()));
    connect(socket,SIGNAL(error(QAbstractSocket::SocketError)),
            this,SLOT(displayError(QAbstractSocket::SocketError)));
    connect(socket,SIGNAL(pointsReceived(int,int,int)),this,SLOT(pointsReceived(int,int,int)));
    connect(socket,SIGNAL(clear()),graphicsScene,SLOT(clear()));
    connect(socket,SIGNAL(someoneLoggedIn(QString)),this,SLOT(someoneLoggedIn(QString)));
    connect(socket,SIGNAL(chatMessage(QString,QString)),this,SLOT(addMessage(QString,QString)));
    connect(socket,SIGNAL(nicknames(QList<QString>)),this,SLOT(getNicknames(QList<QString>)));
    connect(socket,SIGNAL(logout(QString)),this,SLOT(someoneLoggedOut(QString)));

    connect(ui->wantDrawCheckBox,SIGNAL(toggled(bool)),this,SLOT(wantDrawToggled(bool)));

    // actiony z menu: Polaczenie
    connect(ui->actionPo_cz,SIGNAL(triggered()),this,SLOT(connectWindowExec())); // laczymy sie
    connect(ui->actionRoz_cz,SIGNAL(triggered()),this,SLOT(disconnect())); // rozlaczamy sie
    connect(ui->actionZako_cz,SIGNAL(triggered()),this,SLOT(close())); // koniec programu

    // timer
    connect(chatTimer,SIGNAL(timeout()),this,SLOT(timeout()));

    // inne
    this->disableActions(false); // Polacz - aktywne, Rozlacz - nieaktywne
}

MainWindow::~MainWindow()
{
    delete socket;
    delete chatTimer;
    delete graphicsScene;
    delete ui;
}

void MainWindow::drawPoint(QPoint point) {
    this->graphicsScene->addEllipse(
            point.x(),point.y(),5,5,currentPen,QBrush(currentPen.color(),Qt::SolidPattern));
    if(!sender()->objectName().isNull()) {
        this->socket->runCommand(new DrawCommand(point.x(),point.y(),this->currColorId));
    }
}

void MainWindow::clearView() {
    this->socket->runCommand(new ClearCommand());
    this->graphicsScene->clear();
}

void MainWindow::switchColor() {
    this->lastColorButton->setEnabled(true);
    this->lastColorButton = dynamic_cast<QPushButton*>(this->sender());
    this->lastColorButton->setEnabled(false);

    if(sender()->objectName().startsWith("red")) {
        this->currentPen.setColor(QColor("red"));
        this->currColorId = 0;
    }
    else if(sender()->objectName().startsWith("green")) {
        this->currentPen.setColor(QColor("green"));
        this->currColorId = 1;
    }
    else {
        this->currentPen.setColor(QColor("black"));
        this->currColorId = 2;
    }
}

void MainWindow::switchColor(int color) {
    this->currColorId = color;
    if(color == 0) {
        this->currentPen.setColor(QColor("red"));
    }
    else if(color == 1) {
        this->currentPen.setColor(QColor("green"));
    }
    else this->currentPen.setColor(QColor("black"));

}

void MainWindow::displayError(QAbstractSocket::SocketError) {
    if(this->connected) ui->loginInfoLabel->setText(tr("Nie jestes zalogowany."));
    this->connected = false;
    QMessageBox msgBox;
    msgBox.setText(tr("Wystapil blad polaczenia"));
    msgBox.setIcon(QMessageBox::Critical);
    msgBox.setWindowTitle(tr("Wystapil blad"));
    msgBox.exec();
}

void MainWindow::pointsReceived(int x, int y, int color) {
    this->switchColor(color);
    this->drawPoint(QPoint(x,y));
}

void MainWindow::connectWindowExec() {
    LoginDialog *loginDialog = new LoginDialog(this);
    connect(loginDialog,SIGNAL(finished(QTrio<QString,QHostAddress,int>)),
            this,SLOT(connectToHost(QTrio<QString,QHostAddress,int>)));
    loginDialog->exec();
}

void MainWindow::connectToHost(QTrio<QString,QHostAddress,int> trio) {
    this->socket->connectToHost(trio.second,trio.third);
    this->loginName = trio.first;
}

void MainWindow::connectionSuccess() {
    this->connected = true;
    this->socket->setNickname(this->loginName);
    this->socket->runCommand(new LoginCommand(this->loginName));
    ui->loginInfoLabel->setText(tr("Jestes zalogowany jako: ") + this->loginName);
    this->disableActions(true);
}

void MainWindow::someoneLoggedIn(QString login) {
    ui->usersListWidget->addItem(login);
}

void MainWindow::sendMessage() {
    if(this->chatTimeout) {
        QString message = ui->chatLineEdit->text();
        ui->chatLineEdit->clear();
        this->socket->runCommand(new SendMessageCommand(message));
        this->addMessage(this->loginName,message);
        this->chatTimeout = false;
        chatTimer->setInterval(2000);
        chatTimer->start();
    }
}

void MainWindow::timeout() {
    this->chatTimeout = true;
}

void MainWindow::addMessage(QString nickname, QString message) {
    ui->chatTextBrowser->setHtml(ui->chatTextBrowser->toHtml()
                                 + nickname + ": " + message + "<br/>");
    ui->chatTextBrowser->verticalScrollBar()->setValue(ui->chatTextBrowser->verticalScrollBar()->maximum());
}

void MainWindow::wantDrawToggled(bool toggle) {
    if(toggle) {
        // wysylamy do serwera wiadomosc, ze chcemy rysowac
    } else {
        // wysylamy do serwera wiadomosc, ze jednak nie chcemy
    }
}

void MainWindow::getNicknames(QList<QString> list) {
    this->nicknames = list;
    QString nickname;
    ui->usersListWidget->clear();
    foreach(nickname,nicknames) {
        ui->usersListWidget->addItem(nickname);
    }
}

void MainWindow::someoneLoggedOut(QString nickname) {
    // usuwanie z listy nickow
    ui->usersListWidget->removeItemByString(nickname);
}

void MainWindow::disconnect() {
    this->socket->close();
    this->disableActions(false);
}

void MainWindow::disableActions(bool actionFlag) {
    ui->actionPo_cz->setEnabled(1-actionFlag);
    ui->actionRoz_cz->setEnabled(actionFlag);
}
