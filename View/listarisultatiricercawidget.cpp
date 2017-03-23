#include "listarisultatiricercawidget.h"

ListaRisultatiRicercaWidget::ListaRisultatiRicercaWidget(Client* c, QStringList list, QWidget *parent) : ListaWidget(c, "Risultati della ricerca", parent)
{
    risultato = new QVBoxLayout;
    lista->addItems(list);

    bw =0;
    lnw =0;

    layout->addLayout(risultato);
}

void ListaRisultatiRicercaWidget::getSlot()
{
    hideSlot();
    QString x = lista->currentItem()->text();

    logic->findBook(x);

    if(!logic->getLibroSelezionato())
    {
        logic->findLightNovel(x);
        lnw = new LightNovelWidget(logic, dynamic_cast<Light_novel*>(logic->getLibroSelezionato()), this);
        lnw->setMinimumWidth(500);
        risultato->addWidget(lnw);
    }
    else {
        bw = new ViewBookWidget(dynamic_cast<Book*>(logic->getLibroSelezionato()));
        bw->setMinimumWidth(500);
        risultato->addWidget(bw);
    }
}

void ListaRisultatiRicercaWidget::hideSlot() {
    if(bw != 0) {
        bw->close();
        risultato->removeWidget(bw);
        bw =0;
    }
    else if (lnw != 0) {
        risultato->removeWidget(lnw);
        lnw->close();
        lnw =0;
    }
}
