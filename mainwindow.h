#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPen>
#include <QMessageBox>
#include <QIODevice>
#include <QTimer>
#include <QScrollBar>

#include "socketthread.h"
#include "logindialog.h"
#include "command.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    ServerSettings serverSettings;
    AbstractCommand *command;
    bool connected;
    bool chatTimeout;
    int currColorId;
    KalSocket *socket;
    QPen currentPen;
    QGraphicsScene *graphicsScene;
    QPushButton *lastColorButton;
    Ui::MainWindow *ui;
    QString loginName;
    QTimer *chatTimer;
    QList<QString> nicknames;
private slots:
    void addMessage(QString,QString);
    void drawPoint(QPoint);
    void clearView();
    void switchColor();
    void switchColor(int);
    void displayError(QAbstractSocket::SocketError);
    void pointsReceived(int,int,int);
    void connectWindowExec();
    void connectToHost(QTrio<QString,QHostAddress,int>);
    void connectionSuccess();
    void someoneLoggedIn(QString);
    void sendMessage();
    void timeout();
    void wantDrawToggled(bool);
    void getNicknames(QList<QString>);
    void someoneLoggedOut(QString);
    void disconnect();
    // uzywane przy laczeniu. jezeli sie polaczymy, to wylaczamy akcje "Polacz" z menu.
    // jezeli natomiast jestesmy rozlaczeni, to wylaczamy "Rozlacz"
    void disableActions(bool);
    void drawStart(QString);
    void drawTimeout();
    void getSettings(ServerSettings);
};

#endif // MAINWINDOW_H
