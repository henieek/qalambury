#include "socketthread.h"

#include <QDebug>

KalSocket::KalSocket() {
    connect(this,SIGNAL(readyRead()),this,SLOT(receiveData()));
}

KalSocket::~KalSocket() {
    this->close();
}

void KalSocket::setNickname(QString nickname) {
    this->nickname = nickname;
}

void KalSocket::loginAs(QString login) {
    QString data = "log\n" + login + "\n";
    this->write(data.toAscii());
}

void KalSocket::sendPoints(int x, int y, int color) {
    QString data("draw\n" + QString::number(x) + " " + QString::number(y) + " "
                 + QString::number(color) + "\n");

    QByteArray byteArray(data.toAscii());
    this->write(byteArray);
}

void KalSocket::sendClear() {
    this->write("clear\n");
}

void KalSocket::receiveData() {
    // blabla, odbieranie danych, emisja sygnalu
    QByteArray byteArray;
    while(this->bytesAvailable()) {
        byteArray = this->readLine();

        if(byteArray == "clear\n") { // do zmiany, tutaj bedzie wzorzec polecenia.
            emit clear();
            continue;
        }
        if(byteArray == "draw\n") {
            this->drawPointsReceived(this->readLine());
            continue;
        }
        if(byteArray == "log\n") {
            // qDebug() << "ktos sie zalogowal\n";
            this->loginReceived(this->readLine());
            continue;
        }
        if(byteArray == "chat\n") {
            QByteArray nickname = this->readLine();
            QByteArray message = this->readLine();
            this->chatMessageReceived(nickname,message);
        }
        if(byteArray == "list start\n") {
            this->getNicknames();
            continue;
        }
        if(byteArray == "out\n") {
            this->someoneLogout(this->readLine());
            continue;
        }
        if(byteArray == "drawstart\n") {
            this->drawingStart(this->readLine());
            continue;
        }
    }
}

void KalSocket::drawPointsReceived(QByteArray byteArray) {
    int x=0, y=0, color=0, i;
    int size = byteArray.size();
    for(i=0;byteArray[i]!=' ';i++) {
        x*=10;
        x+=static_cast<int>(byteArray[i]-48);
    }
    for(++i;byteArray[i]!=' ';i++) {
        y*=10;
        y+=static_cast<int>(byteArray[i]-48);
    }
    for(++i;i<size-1;i++) {
        color*=10;
        color+=static_cast<int>(byteArray[i]-48);
    }
    emit pointsReceived(x,y,color);
}

void KalSocket::loginReceived(QByteArray byteArray) {
    QString login(byteArray.replace(QString("\n"),QByteArray("")));
    emit someoneLoggedIn(login);
}

void KalSocket::sendMessage(QString message) {
    // wysylanie wiadomosci
    this->write(QString("chat\n" + message + "\n").toAscii());
}

void KalSocket::chatMessageReceived(QByteArray nickname, QByteArray message) {
    emit chatMessage(QString(nickname),QString(message));
}

void KalSocket::runCommand(AbstractCommand *command) {
    command->run(this);
    delete command;
}

void KalSocket::getNicknames() {
    QList<QString> nicknamesList;
    QByteArray nickname = this->readLine();
    while(nickname != "list end\n") {
        nicknamesList.push_back(QString(nickname).replace(QString("\n"),QString("")));
        nickname = this->readLine();
    }
    if(!nicknamesList.isEmpty()) emit nicknames(nicknamesList);
}

void KalSocket::someoneLogout(QByteArray byteArray) {
    emit logout(QString(byteArray).replace(QString("\n"),QString("")));
}

void KalSocket::drawingStart(QByteArray byteArray) {
    emit drawStart(QString(byteArray).replace(QString("\n"),QString("")));
}
