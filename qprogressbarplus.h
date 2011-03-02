#ifndef QPROGRESSBARPLUS_H
#define QPROGRESSBARPLUS_H

#include <QProgressBar>
#include <QTimer>

class QProgressBarPlus : public QProgressBar
{
    Q_OBJECT
private:
    int unitInterval;
    int wholeInterval;
    QTimer *timer;
private slots:
    void unitTimeout();
public:
    explicit QProgressBarPlus(QWidget *parent = 0);
    virtual ~QProgressBarPlus();
    void setInterval(int);
    void start();
signals:
    void full();
public slots:

};

#endif // QPROGRESSBARPLUS_H
