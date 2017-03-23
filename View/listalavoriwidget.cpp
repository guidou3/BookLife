#include "listalavoriwidget.h"

ListaLavoriWidget::ListaLavoriWidget(Client* c, QWidget *parent) : ListaWidget(c, "Lista dei lavori", parent)
{
    risultato = new QVBoxLayout;
    lista->addItems(logic->getLavori());

    lnw =0;

    layout->addLayout(risultato);
}

void ListaLavoriWidget::getSlot()
{
    hideSlot();
    QString x = lista->currentItem()->text();

    logic->findLightNovel(x);
    lnw = new ViewLightNovelWidget(dynamic_cast<Light_novel*>(logic->getLibroSelezionato()), logic, this);
    lnw->setMinimumWidth(500);
    risultato->addWidget(lnw);
}

void ListaLavoriWidget::updateSlot()
{
    hideSlot();
    lista->clear();
    lista->addItems(logic->getLavori());
}

void ListaLavoriWidget::hideSlot()
{
    if (lnw != 0) {
        risultato->removeWidget(lnw);
        lnw->close();
        lnw =0;
    }
}
