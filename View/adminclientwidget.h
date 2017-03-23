#ifndef ADMINCLIENTWIDGET_H
#define ADMINCLIENTWIDGET_H


#include "clientwidget.h"
#include "listalibriwidget.h"
#include "listautentiwidget.h"

class AdminClientWidget : public ClientWidget {

    Q_OBJECT

public:
    explicit AdminClientWidget(Session*, QWidget *parent = 0);
    ~AdminClientWidget();

private:
    // campi dati grafici
    ListaLibriWidget* book; //lista con permessi di creazione/modifica/lettura/rimozione per la gestione dei book
    ListaLibriWidget* ln; //lista con permessi di creazione/modifica/lettura/rimozione per la gestione delle light novel
    ListaUtentiWidget* utenti; // lista con permessi di rimozione per la gestione degli utenti

public slots:
    void hideSlot(); //metodo che chiama i rispettivi metodi dei wiget figli per nascondere le componenti normalmente nascoste
};

#endif // ADMINCLIENTWIDGET_H
