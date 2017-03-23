#include "listapreferitiwidget.h"

ListaPreferitiWidget::ListaPreferitiWidget(Client* c, QWidget *parent) : ListaWidget(c, "Lista dei Preferiti", parent)
{
    lista->addItems(logic->getListaPreferiti());

    visualizza = new QPushButton;
    visualizza->setText("Visualizza");

    rimuovi = new QPushButton;
    rimuovi->setText("Rimuovi");

    connect(visualizza,SIGNAL(clicked()),this,SLOT(visualizzaSlot()));
    connect(rimuovi,SIGNAL(clicked()),this,SLOT(rimuoviSlot()));

    mainLayout->addWidget(visualizza);
    visualizza->hide();

    mainLayout->addWidget(rimuovi);
    rimuovi->hide();
}

void ListaPreferitiWidget::getSlot()
{
    QString x = lista->currentItem()->text();

    logic->findPreferito(x);

    if(logic->getLibroSelezionato())
    {
        emit(selected());
        visualizza->show();
        rimuovi->show();
    }
    else
        updateSlot();
}

void ListaPreferitiWidget::updateSlot()
{
    hideSlot();
    logic->resetSelezionati();
    lista->clear();
    lista->addItems(logic->getListaPreferiti());
}

void ListaPreferitiWidget::visualizzaSlot()
{
    Libro* libro = logic->getLibroSelezionato();
    if(libro->getType() =="Book") {
        ViewBookWidget* bw = new ViewBookWidget(dynamic_cast<Book*>(libro));
        bw->show();
    }
    else {
        ViewLightNovelWidget* lnw = new ViewLightNovelWidget(dynamic_cast<Light_novel*>(libro), logic);
        lnw->show();
    }
}

void ListaPreferitiWidget::rimuoviSlot()
{
    if(logic->libroExists())
    {
        logic->removePreferito();

    }
    logic->resetSelezionati();
    hideSlot();
    updateSlot();
}

void ListaPreferitiWidget::hideSlot()
{
    visualizza->hide();
    rimuovi->hide();
}
