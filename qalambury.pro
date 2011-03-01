#-------------------------------------------------
#
# Project created by QtCreator 2011-02-15T22:39:49
#
#-------------------------------------------------

QT       += core gui network

TARGET = qalambury
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qgraphicsviewplus.cpp \
    socketthread.cpp \
    logindialog.cpp \
    command.cpp \
    qlistwidgetplus.cpp

HEADERS  += mainwindow.h \
    qgraphicsviewplus.h \
    socketthread.h \
    logindialog.h \
    command.h \
    qlistwidgetplus.h \
    qtrio.h

FORMS    += mainwindow.ui \
    logindialog.ui
