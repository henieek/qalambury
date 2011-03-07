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

DrawCommand::DrawCommand(DrawCommand::DrawType type, int x, int y, int color) :
        type(type), xRect(x), yRect(y), color(color)
{

}

DrawCommand::~DrawCommand() { }

void DrawCommand::run(QTcpSocket *sock) {
    QString cmd;
    if(this->type == LINE) {
        cmd = "drawline\n";
    }
    else {
        cmd = "drawpoint\n";
    }
    sock->write(QString(cmd + QString::number(xRect) + " " + QString::number(yRect)
                        + " " + QString::number(color) + "\n").toAscii());
}

ClearCommand::ClearCommand() {

}

ClearCommand::~ClearCommand() {
}

void ClearCommand::run(QTcpSocket *sock) {
    sock->write("clear\n");
}

WantDrawCommand::WantDrawCommand(bool want) :
        wantDraw(want)
{

}

WantDrawCommand::~WantDrawCommand() { }

void WantDrawCommand::run(QTcpSocket *sock) {
    QString message = "toggle\n";
    if(!wantDraw) message = "un" + message;
    sock->write(message.toAscii());
}
