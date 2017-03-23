#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include "Controller/client.h"
#include "ricercawidget.h"

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(Session*, QWidget *parent = 0);
    virtual ~ClientWidget();

protected:
    // campi dati logici
    Client* logic;

    // campi dati grafici
    RicercaWidget* ricerca;

    QLabel* tipoClient;

    // pulsanti
    QPushButton* logoutButton;

    // layout e box
    QVBoxLayout* layout; // layout principale del widget
    QHBoxLayout* CentralLayout; // layout centrale
    QHBoxLayout* buttons;

signals:
    void logoutSignal();

public slots:
    virtual void hideSlot() =0; // procedura per nascondere tutti i widget (QLabel, QPushButton) che normalmente dovrebbero essere nascosti
};

#endif // CLIENTWIDGET_H
