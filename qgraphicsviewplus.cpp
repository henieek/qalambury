#include "qgraphicsviewplus.h"

QGraphicsViewPlus::QGraphicsViewPlus(QWidget *parent) :
    QGraphicsView(parent), scribbling(false)
{
    this->setDragMode(QGraphicsView::NoDrag);
}

void QGraphicsViewPlus::mousePressEvent(QMouseEvent *event) {
    if(this->isInteractive()) {
        this->scribbling = true;
        emit drawPoint(event->globalPos());
    }
}

void QGraphicsViewPlus::mouseMoveEvent(QMouseEvent *event) {
    if(scribbling) {
 //       emit drawPoint(event->globalPos());
        emit drawLineTo(event->globalPos());
    }
}

void QGraphicsViewPlus::mouseReleaseEvent(QMouseEvent *event) {
    this->scribbling = false;
}
