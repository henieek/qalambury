#ifndef SOCKETTHREAD_H
#define SOCKETTHREAD_H

#include <QtNetwork/QTcpSocket>

#include "command.h"
#include "serversettings.h"

class KalSocket : public QTcpSocket
{
    Q_OBJECT
public:
    enum DrawType {
        POINT,
        LINE
    };
signals:
    void nicknames(QList<QString>);
    void pointsReceived(int,int,int,KalSocket::DrawType);
    void clear();
    void someoneLoggedIn(QString);
    void chatMessage(QString,QString);
    void logout(QString);
    void drawStart(QString);
    void gotSettings(ServerSettings);
    void errorMessage(QString);
private slots:
    void receiveData();
    void drawPointsReceived(QByteArray,KalSocket::DrawType);
    void loginReceived(QByteArray);
    void getNicknames();
private:
    QString nickname;
    void chatMessageReceived(QByteArray,QByteArray);
    void someoneLogout(QByteArray);
    void drawingStart(QByteArray);
    void settingsReceived(QByteArray);
public:
    /*enum DrawType {
        POINT,
        LINE
    };*/
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
