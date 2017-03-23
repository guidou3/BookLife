#include "viewlibrowidget.h"

ViewLibroWidget::ViewLibroWidget(Libro* libro, QWidget *parent) : QWidget(parent)
{
    if(libro == NULL) close();

    mainLayout = new QVBoxLayout;
    centralLayout = new QHBoxLayout;
    visualizzaBox = new QGroupBox;
    parallelLayout = new QVBoxLayout;
    rowLayout = new QFormLayout;
    listLayout = new QFormLayout;

    titoloLabel = new QLabel;
    dataPubblicazioneLabel = new QLabel;
    linguaLabel = new QLabel;
    descrizioneLabel = new QLabel;
    immagineLabel = new QLabel;

    autoriList = new QListWidget;
    generiList = new QListWidget;

    titoloLabel->setText(libro->getTitolo());
    dataPubblicazioneLabel->setText(libro->getDataPubblicazione().toString());
    linguaLabel->setText(libro->getLingua());
    descrizioneLabel->setText(libro->getDescrizione());
    descrizioneLabel->setWordWrap(true);

    autoriList->addItems(libro->getAutori());
    autoriList->setMaximumHeight(100);
    generiList->addItems(libro->getGeneri());
    generiList->setMaximumHeight(100);

    if(!libro->getImmagine().isEmpty())
    {
        QPixmap pix(libro->getImmagine());
        immagineLabel->setPixmap(pix.scaled(300, 450, Qt::KeepAspectRatio));
    }
    else
    {
        immagineLabel->hide();
    }

    rowLayout->addRow("Titolo: ", titoloLabel);
    rowLayout->addRow("Data di pubblicazione: ", dataPubblicazioneLabel);
    rowLayout->addRow("Lingua: ", linguaLabel);
    rowLayout->addRow("Descrizione: ", descrizioneLabel);
    listLayout->addRow("Autori: ", autoriList);
    listLayout->addRow("Generi: ", generiList);

    parallelLayout->addWidget(immagineLabel, Qt::AlignTop);

    mainLayout->addLayout(rowLayout);
    mainLayout->addLayout(listLayout);
    centralLayout->addLayout(mainLayout);
    centralLayout->addLayout(parallelLayout);
    setLayout(centralLayout);
}
