#include "command.h"

AbstractCommand::AbstractCommand(QString message) {
    this->message = message;
}

AbstractCommand::~AbstractCommand() { }

QString AbstractCommand::getMessage() const {
    return this->message;
}

void AbstractCommand::setMessage(QString message) {
    this->message = message;
}

SendMessageCommand::SendMessageCommand(QString message) :
        AbstractCommand(message)
{

}

SendMessageCommand::~SendMessageCommand() {

}

void SendMessageCommand::run(QTcpSocket *sock) {
    sock->write(QString("chat\n"  + this->getMessage() + "\n").toAscii());
}

LoginCommand::LoginCommand(QString message) :
        AbstractCommand(message)
{

}

LoginCommand::~LoginCommand() { }

void LoginCommand::run(QTcpSocket *sock) {
    sock->write(QString("log\n" + this->getMessage() + "\n").toAscii());
}

DrawCommand::DrawCommand(int x, int y, int color) :
        xRect(x), yRect(y), color(color)
{

}

DrawCommand::~DrawCommand() { }

void DrawCommand::run(QTcpSocket *sock) {
    sock->write(QString("draw\n" + QString::number(xRect) + " " + QString::number(yRect)
                        + " " + QString::number(color) + "\n").toAscii());
}

ClearCommand::ClearCommand() {

}

ClearCommand::~ClearCommand() {
}

void ClearCommand::run(QTcpSocket *sock) {
    sock->write("clear\n");
}
