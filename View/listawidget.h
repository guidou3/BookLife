#ifndef LISTAWIDGET_H
#define LISTAWIDGET_H

#include "Controller/client.h"

#include <QListWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QGroupBox>

class ListaWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListaWidget(Client*, QString, QWidget *parent = 0);

protected:
    Client* logic;

    QListWidget* lista;

    QHBoxLayout* layout;
    QVBoxLayout* mainLayout;
    QGroupBox* listaBox;

signals:
    void selected(); //signal per comunicare al client che è stata selezionata una voce (serve per far chiamare hideSlot())

public slots:
    virtual void getSlot() =0; //metodo per selezionare un elemento della lista
    virtual void hideSlot() =0; //metodo per nascondere i widget normalmente nascosti

};

#endif // LISTAWIDGET_H
