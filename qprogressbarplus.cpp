#include "qprogressbarplus.h"

QProgressBarPlus::QProgressBarPlus(QWidget *parent) :
        QProgressBar(parent)
{
    this->unitInterval = wholeInterval/100;
    this->timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(unitTimeout()));
}

QProgressBarPlus::~QProgressBarPlus() {
    delete timer;
}

void QProgressBarPlus::setInterval(int interval) {
    this->wholeInterval = interval;
    this->unitInterval = wholeInterval/100;
}

void QProgressBarPlus::start() {
    this->setValue(0);
    this->timer->setInterval(unitInterval);
    this->timer->start();
}

void QProgressBarPlus::unitTimeout() {
    this->setValue(this->value() + 1);
    if(this->value() >= 100) {
        emit full();
    }
    else {
        this->timer->setInterval(unitInterval);
        this->timer->start();
    }
}
