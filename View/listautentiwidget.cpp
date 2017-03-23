#include "listautentiwidget.h"

ListaUtentiWidget::ListaUtentiWidget(Client* c, QWidget *parent) : ListaWidget(c, "Lista degli Utenti", parent)
{
    lista->addItems(logic->getListaUtenti());

    rimuovi = new QPushButton;
    rimuovi->setText("Rimuovi");

    connect(rimuovi,SIGNAL(clicked()),this,SLOT(rimuoviSlot()));

    mainLayout->addWidget(rimuovi);
    rimuovi->hide();
}

void ListaUtentiWidget::getSlot()
{
    QString x = lista->currentItem()->text();

    logic->findUtente(x);

    if(logic->getUtenteSelezionato())
    {
        emit(selected());
        rimuovi->show();
    }
    else updateSlot();
}

void ListaUtentiWidget::updateSlot()
{
    hideSlot();
    logic->resetSelezionati();
    lista->clear();
    lista->addItems(logic->getListaUtenti());
}

void ListaUtentiWidget::rimuoviSlot()
{
    if(logic->utenteExists())
    {
        logic->rimuoviUtente();

    }
    logic->resetSelezionati();
    hideSlot();
    updateSlot();
}

void ListaUtentiWidget::hideSlot()
{
    rimuovi->hide();
}
