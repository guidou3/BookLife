#ifndef LISTALAVORIWIDGET_H
#define LISTALAVORIWIDGET_H

#include "listawidget.h"
#include "lightnovelwidget.h"

class ListaLavoriWidget : public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaLavoriWidget(Client*, QWidget *parent = 0);

private:
    ViewLightNovelWidget* lnw;

    QHBoxLayout* central;

    QVBoxLayout* risultato;

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void updateSlot(); //metodo per aggiornare le voci della lista
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti

};
#endif // LISTALAVORIWIDGET_H
