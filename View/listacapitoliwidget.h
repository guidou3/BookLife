#ifndef LISTACAPITOLIWIDGET_H
#define LISTACAPITOLIWIDGET_H

#include "listawidget.h"
#include "capitolowidget.h"

class ListaCapitoliWidget : public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaCapitoliWidget(Client*, Light_novel*, bool, QWidget *parent = 0);

private:
    Light_novel* lightNovel;
    bool writer;
    Capitolo* cap;

    QPushButton* visualizza;
    QPushButton* modifica;
    QPushButton* aggiungi;

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void updateSlot(); //metodo per aggiornare le voci della lista
    void visualizzaSlot(); //metodo per visualizzare l'elemento selezionato
    void aggiungiSlot(); //metodo per aggiungere una nuova voce alla lista
    void modificaSlot(); //metodo per modificare l'elemento selezionato
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti
};

#endif // LISTACAPITOLIWIDGET_H

