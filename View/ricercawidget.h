#ifndef RICERCAWIDGET_H
#define RICERCAWIDGET_H

#include "Controller/client.h"

#include "listarisultatiricercawidget.h"
#include "ricercaavanzatawidget.h"

class RicercaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RicercaWidget(Client*, QWidget *parent = 0);

private:
    Client* logic;

    QGroupBox* ricercaBox; // widget contenente i campi relativi alla ricerca
    QHBoxLayout* ricercaLayout;
    QVBoxLayout* mainLayout;

    QLabel* presentazione;
    QLabel* ricercaMessageLabel;

    QLineEdit* ricerca;

    QPushButton* cerca;
    QPushButton* ricercaAvanzata;

    void hideAll();
signals:
    void selected();

public slots:
    void cercaSlot(); // procedura per la ricerca di un libro tramite qualunque parametro
    void ricercaAvanzataSlot(); //procedura per chiamare un'istanza del widget per la ricerca avanzata
};

#endif // RICERCA_H
