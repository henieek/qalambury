#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QtNetwork/QTcpSocket>

#include "command.h"

class KalSocket : public QTcpSocket
{
    Q_OBJECT
signals:
    void nicknames(QList<QString>);
    void pointsReceived(int,int,int);
    void clear();
    void someoneLoggedIn(QString);
    void chatMessage(QString,QString);
    void logout(QString);
private slots:
    void receiveData();
    void drawPointsReceived(QByteArray);
    void loginReceived(QByteArray);
    void getNicknames();
private:
    QString nickname;
    void chatMessageReceived(QByteArray,QByteArray);
    void someoneLogout(QByteArray);
public:
    KalSocket();
    ~KalSocket();
    void sendPoints(int,int,int);
    void sendClear();
    void loginAs(QString);
    void sendMessage(QString);
    void runCommand(AbstractCommand*);
    void setNickname(QString);
};

#endif // SOCKETTHREAD_H
