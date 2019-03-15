#-------------------------------------------------
#
# Project created by QtCreator 2019-03-13T13:12:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PhoneSelector
TEMPLATE = app

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    handler.cpp \
    phone.cpp \
    filemanager.cpp \
    question.cpp \
    currentbutton.cpp

HEADERS += \
        mainwindow.h \
    handler.h \
    phone.h \
    filemanager.h \
    question.h \
    currentbutton.h

FORMS += \
        mainwindow.ui
