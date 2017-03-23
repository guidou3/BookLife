#ifndef LISTARISULTATIRICERCAWIDGET_H
#define LISTARISULTATIRICERCAWIDGET_H

#include "listawidget.h"
#include "bookwidget.h"
#include "lightnovelwidget.h"

class ListaRisultatiRicercaWidget  : public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaRisultatiRicercaWidget(Client*, QStringList, QWidget *parent = 0);

private:
    ViewBookWidget* bw;
    LightNovelWidget* lnw;

    QVBoxLayout* risultato;

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti

};

#endif // LISTARISULTATIRICERCAWIDGET_H
