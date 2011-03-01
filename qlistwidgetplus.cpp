#include "qlistwidgetplus.h"

#include <QDebug>

QListWidgetPlus::QListWidgetPlus(QWidget *parent) :
    QListWidget(parent)
{
}

QListWidgetPlus::~QListWidgetPlus() {

}

void QListWidgetPlus::removeItemByString(QString itemText) {
    int size = this->count();
    for(int row=0;row<size;row++) {
        if(this->item(row)->text() == itemText) {
            QListWidgetItem *item = this->takeItem(row);
            delete item;
            break;
        }
    }
}
