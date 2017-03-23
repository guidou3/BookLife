#-------------------------------------------------
#
# Project created by QtCreator 2016-06-18T12:35:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BookLife_widget
TEMPLATE = app
CONFIG -= console

SOURCES += main.cpp \
    Model/database.cpp \
    Model/utente.cpp \
    Model/libro.cpp \
    Model/book.cpp \
    Model/light_novel.cpp \
    Model/amministratore.cpp \
    Model/scrittore.cpp \
    Model/session.cpp \
    Model/capitolo.cpp \
    View/writerclientwidget.cpp \
    View/adminclientwidget.cpp \
    View/userclientwidget.cpp \
    View/booklifewidget.cpp \
    View/signupwidget.cpp \
    View/lightnovelwidget.cpp \
    View/capitolowidget.cpp \
    View/bookwidget.cpp \
    View/ricercawidget.cpp \
    Controller/client.cpp \
    View/clientwidget.cpp \
    View/listawidget.cpp \
    View/listalibriwidget.cpp \
    View/listapreferitiwidget.cpp \
    View/listautentiwidget.cpp \
    View/listarisultatiricercawidget.cpp \
    View/ricercaavanzatawidget.cpp \
    View/listalavoriwidget.cpp \
    View/viewlibrowidget.cpp \
    View/viewbookwidget.cpp \
    View/viewlightnovelwidget.cpp \
    View/listacapitoliwidget.cpp \
    View/librowidget.cpp



HEADERS += \
    Model/database.h \
    Model/utente.h \
    Model/libro.h \
    Model/book.h \
    Model/light_novel.h \
    Model/amministratore.h \
    Model/scrittore.h \
    Model/session.h \
    Model/capitolo.h \
    Model/dblist.h \
    View/writerclientwidget.h \
    View/adminclientwidget.h \
    View/userclientwidget.h \
    View/booklifewidget.h \
    View/signupwidget.h \
    View/lightnovelwidget.h \
    View/capitolowidget.h \
    View/bookwidget.h \
    View/ricercawidget.h \
    Controller/client.h \
    View/clientwidget.h \
    View/listawidget.h \
    View/listalibriwidget.h \
    View/listapreferitiwidget.h \
    View/listautentiwidget.h \
    View/listarisultatiricercawidget.h \
    View/ricercaavanzatawidget.h \
    View/listalavoriwidget.h \
    View/viewlibrowidget.h \
    View/viewbookwidget.h \
    View/viewlightnovelwidget.h \
    View/listacapitoliwidget.h \
    View/librowidget.h


