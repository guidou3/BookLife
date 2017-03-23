#include "listacapitoliwidget.h"

ListaCapitoliWidget::ListaCapitoliWidget(Client* c, Light_novel* ln, bool w, QWidget *parent): ListaWidget(c, "Lista dei capitoli", parent), lightNovel(ln), writer(w)
{
    lista->addItems(lightNovel->getTitoli());

    if(writer)
    {
        visualizza = new QPushButton;
        visualizza->setText("Visualizza");

        modifica = new QPushButton;
        modifica->setText("Modifica");

        aggiungi = new QPushButton;
        aggiungi->setText("Aggiungi");

        connect(visualizza,SIGNAL(clicked()),this,SLOT(visualizzaSlot()));
        connect(modifica,SIGNAL(clicked()),this,SLOT(modificaSlot()));
        connect(aggiungi,SIGNAL(clicked()),this,SLOT(aggiungiSlot()));

        mainLayout->addWidget(visualizza);
        visualizza->hide();
        mainLayout->addWidget(modifica);
        modifica->hide();
        mainLayout->addWidget(aggiungi);
    }
}

void ListaCapitoliWidget::getSlot()
{
    QString x = lista->currentItem()->text();
    int index = lightNovel->getCapitoloIndex(x);
    if(index != -1)
    {
        cap = lightNovel->getCapitolo(index);
        if(writer)
        {
            hideSlot();
            visualizza->show();
            modifica->show();
        }
        else {
            CapitoloWidget* cw = new CapitoloWidget(cap);
            cw->show();
        }
    }
}

void ListaCapitoliWidget::updateSlot()
{
    hideSlot();
    lista->clear();
    lista->addItems(lightNovel->getTitoli());
}

void ListaCapitoliWidget::visualizzaSlot()
{
    CapitoloWidget* cw = new CapitoloWidget(cap);
    cw->show();
}

void ListaCapitoliWidget::aggiungiSlot()
{
    CapitoloWidget* cw = new CapitoloWidget(lightNovel);
    cw->show();
    connect(cw,SIGNAL(updateCapitoli()),this,SLOT(updateSlot()));

}

void ListaCapitoliWidget::modificaSlot()
{
    CapitoloWidget* cw = new CapitoloWidget(lightNovel, lightNovel->getCapitoloIndex(cap->getTitolo()));
    cw->show();
    connect(cw,SIGNAL(updateNomeCapitolo()),this,SLOT(updateSlot()));
}

void ListaCapitoliWidget::hideSlot()
{
    visualizza->hide();
    modifica->hide();
}
