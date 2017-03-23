#ifndef WRITERCLIENTWIDGET_H
#define WRITERCLIENTWIDGET_H

#include "clientwidget.h"
#include "listalavoriwidget.h"

#include <QWidget>


class WriterClientWidget : public ClientWidget
{
    Q_OBJECT

public:
    explicit WriterClientWidget(Session*, QWidget *parent = 0);
    ~WriterClientWidget();

private:
    // campi dati grafici
    ListaLavoriWidget* lavori;

    QPushButton* normalAccountButton; // pulsante per passare al client utente

signals:
    void normalAccount();

public slots:
    void checkSlot(); //metodo per aggiornare la lista dei lavori di un utente e la relativa lista
    void hideSlot(); //metodo per nascondere i componenti che sono di default nascosti
};

#endif // WRITERCLIENTWIDGET_H
