#ifndef QLISTWIDGETPLUS_H
#define QLISTWIDGETPLUS_H

#include <QListWidget>

class QListWidgetPlus : public QListWidget
{
    Q_OBJECT
public:
    explicit QListWidgetPlus(QWidget *parent = 0);
    virtual ~QListWidgetPlus();
signals:

public slots:

public:
    void removeItemByString(QString);
};

#endif // QLISTWIDGETPLUS_H
