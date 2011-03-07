#ifndef QGRAPHICSVIEWPLUS_H
#define QGRAPHICSVIEWPLUS_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QDebug>

class QGraphicsViewPlus : public QGraphicsView
{
    Q_OBJECT
private:
    bool scribbling;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    // void resizeEvent(QResizeEvent *event);
public:
    explicit QGraphicsViewPlus(QWidget *parent = 0);
signals:
    void drawPoint(QPoint);
    void drawLineTo(QPoint);
public slots:

};

#endif // QGRAPHICSVIEWPLUS_H
