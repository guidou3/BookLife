#ifndef LISTAUTENTIWIDGET_H
#define LISTAUTENTIWIDGET_H

#include "listawidget.h"

class ListaUtentiWidget : public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaUtentiWidget(Client*, QWidget *parent = 0);

    void hideAll();

private:
    QPushButton* rimuovi;

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void updateSlot(); //metodo per aggiornare le voci della lista
    void rimuoviSlot(); //metodo per rimuovere l'elemento selezionato
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti
};

#endif // LISTAUTENTIWIDGET_H
