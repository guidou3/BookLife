#ifndef LISTAPREFERITIWIDGET_H
#define LISTAPREFERITIWIDGET_H

#include "listawidget.h"
#include "bookwidget.h"
#include "lightnovelwidget.h"

class ListaPreferitiWidget : public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaPreferitiWidget(Client*, QWidget *parent = 0);

    void hideAll();

private:
    QPushButton* visualizza;
    QPushButton* rimuovi;

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void updateSlot(); //metodo per aggiornare le voci della lista
    void visualizzaSlot(); //metodo per visualizzare l'elemento selezionato
    void rimuoviSlot(); //metodo per rimuovere l'elemento selezionato
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti
};

#endif // LISTAPREFERITIWIDGET_H
