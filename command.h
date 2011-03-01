#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <QtNetwork/QTcpSocket>

class AbstractCommand
{
    QString message;
public:
    AbstractCommand(QString message = "");
    virtual ~AbstractCommand();
    virtual void run(QTcpSocket*) = 0;
    void setMessage(QString);
    QString getMessage() const;
};

class SendMessageCommand : public AbstractCommand {
public:
    SendMessageCommand(QString message = "");
    virtual ~SendMessageCommand();
    void run(QTcpSocket*);
};

class LoginCommand : public AbstractCommand {
    QString message;
public:
    LoginCommand(QString message = "");
    virtual ~LoginCommand();
    void run(QTcpSocket*);
};

class DrawCommand : public AbstractCommand {
    int xRect;
    int yRect;
    int color;
public:
    DrawCommand(int x = 0, int y = 0, int color = 0);
    virtual ~DrawCommand();
    void run(QTcpSocket*);
};

class ClearCommand : public AbstractCommand {
public:
    ClearCommand();
    virtual ~ClearCommand();
    void run(QTcpSocket *);
};

#endif // COMMAND_H
