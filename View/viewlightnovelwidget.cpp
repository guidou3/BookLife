#include "viewlightnovelwidget.h"

ViewLightNovelWidget::ViewLightNovelWidget(Light_novel* ln, Client* c, QWidget *parent): ViewLibroWidget(ln, parent), logic(c), lightNovel(ln)
{
    if(ln == NULL) close();

    layCap = new QVBoxLayout;

    capitoli_tradottiLabel = new QLabel;
    capitoli_scrittiLabel = new QLabel;
    completatoLabel = new QLabel;
    lingua_originaleLabel = new QLabel;

    traduttoriList = new QListWidget;

    capitoli_tradottiLabel->setText(QString::number(lightNovel->getCapitoliTradotti()));
    capitoli_scrittiLabel->setText(QString::number(lightNovel->getCapitoliScritti()));
    if(lightNovel->isCompletato()) completatoLabel->setText("Vero");
    else completatoLabel->setText("Falso");
    lingua_originaleLabel->setText(lightNovel->getLinguaOriginale());

    traduttoriList->addItems(lightNovel->getTraduttori());
    traduttoriList->setMaximumHeight(100);

    rowLayout->addRow("Capitoli scritti: ", capitoli_scrittiLabel);
    rowLayout->addRow("Capitoli tradotti: ", capitoli_tradottiLabel);
    rowLayout->addRow("Completato: ", completatoLabel);
    rowLayout->addRow("Lingua originale: ", lingua_originaleLabel);

    listLayout->addRow("Traduttori: ", traduttoriList);


    if(logic->getTipoClient() == 1 && logic->getSession()->getAccountType() == 1 && dynamic_cast<Scrittore*>(logic->getSession()->utenteLoggato)->isMine(lightNovel))
        capitoli = new ListaCapitoliWidget(logic, lightNovel, true);
    else
        capitoli = new ListaCapitoliWidget(logic, lightNovel, false);

    centralLayout->addWidget(capitoli);
}


