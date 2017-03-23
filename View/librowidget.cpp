#include "librowidget.h"

LibroWidget::LibroWidget(Libro* l, Client* c, QWidget *parent) : QWidget(parent), logic(c), lib(l)
{
    if(lib == NULL) close();

    initializeLibro();

    titoloEdit->setText(lib->getTitolo());
    titoloEdit->setEnabled(false);
    dataPubblicazioneEdit->setDate(lib->getDataPubblicazione());
    linguaEdit->setText(lib->getLingua());
    descrizioneEdit->setText(lib->getDescrizione());

    fileImmagine->setText(lib->getImmagine());
    if(fileImmagine->text().isEmpty()) fileImmagine->setText("NULL");

    autoriList->addItems(lib->getAutori());
    generiList->addItems(lib->getGeneri());

    connect(salva,SIGNAL(clicked()),this,SLOT(aggiornaSlot()));
}

LibroWidget::LibroWidget(Client* c, QWidget *parent) : QWidget(parent, Qt::Window), logic(c)
{
    initializeLibro();

    titoloLabel = new QLabel;
    titoloLabel->hide();

    fileImmagine->setText("NULL");

    connect(salva,SIGNAL(clicked()),this,SLOT(salvaSlot()));
}

void LibroWidget::initializeLibro()
{
    mainLayout = new QVBoxLayout;
    visualizzaBox = new QGroupBox;

    dataLayout = new QVBoxLayout;
    rowLayout = new QFormLayout;
    listLayout = new QFormLayout;
    othersLayout = new QFormLayout;

    titoloEdit = new QLineEdit;
    dataPubblicazioneEdit = new QDateEdit;
    linguaEdit = new QLineEdit;
    descrizioneEdit = new QLineEdit;
    autoreEdit = new QLineEdit;
    genereEdit = new QLineEdit;

    fileImmagine = new QLabel;

    autoriList = new QListWidget;
    generiList = new QListWidget;

    addAutore = new QPushButton;
    removeAutore = new QPushButton;
    addGenere = new QPushButton;
    removeGenere = new QPushButton;
    addImmagine = new QPushButton;
    annulla = new QPushButton;
    salva = new QPushButton;


    addAutore->setText("Inserisci");
    removeAutore->setText("Rimuovi");
    removeAutore->hide();
    addGenere->setText("Inserisci");
    removeGenere->setText("Rimuovi");
    removeGenere->hide();
    addImmagine->setText("Aggiungi immagine");
    annulla->setText("ANNULLA");
    annulla->setMaximumWidth(150);
    salva->setText("SALVA");
    salva->setMaximumWidth(150);

    autoriList->setMaximumHeight(100);
    generiList->setMaximumHeight(100);

    connect(autoriList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getAutoreSlot()));
    connect(generiList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getGenereSlot()));
    connect(addAutore,SIGNAL(clicked()),this,SLOT(aggiungiAutoreSlot()));
    connect(removeAutore,SIGNAL(clicked()),this,SLOT(rimuoviAutoreSlot()));
    connect(addGenere,SIGNAL(clicked()),this,SLOT(aggiungiGenereSlot()));
    connect(removeGenere,SIGNAL(clicked()),this,SLOT(rimuoviGenereSlot()));
    connect(addImmagine,SIGNAL(clicked()),this,SLOT(apriImmagine()));
    connect(annulla,SIGNAL(clicked()),this,SLOT(close()));

    QVBoxLayout* v1 = new QVBoxLayout;
    v1->addWidget(autoriList);
    v1->addWidget(removeAutore);

    QVBoxLayout* v2 = new QVBoxLayout;
    v2->addWidget(generiList);
    v2->addWidget(removeGenere);

    QHBoxLayout* h1 = new QHBoxLayout;
    h1->addWidget(autoreEdit);
    h1->addWidget(addAutore);

    QHBoxLayout* h2 = new QHBoxLayout;
    h2->addWidget(genereEdit);
    h2->addWidget(addGenere);


    rowLayout->addRow("Titolo: ", titoloEdit);
    rowLayout->addRow("Data di pubblicazione: ", dataPubblicazioneEdit);
    rowLayout->addRow("Lingua: ", linguaEdit);
    rowLayout->addRow("Descrizione: ", descrizioneEdit);
    listLayout->addRow("Autori: ", v1);
    listLayout->addRow("Nuovo autore: ", h1);
    listLayout->addRow("Generi: ", v2);
    listLayout->addRow("Nuovo genere: ", h2);
    othersLayout->addRow("Immagine selezionata: ", fileImmagine);
    othersLayout->addRow("", addImmagine);

    QHBoxLayout* buttons = new QHBoxLayout;

    buttons->addWidget(annulla);
    buttons->addSpacing(50);
    buttons->addWidget(salva);

    dataLayout->addLayout(rowLayout);
    dataLayout->addLayout(listLayout);
    dataLayout->addLayout(othersLayout);

    visualizzaBox->setLayout(dataLayout);

    titoloSchedaLabel = new QLabel;
    QFont font = QFont("arial", 12, QFont::Bold);
    titoloSchedaLabel->setFont(font);

    QScrollArea* scroll = new QScrollArea;
    scroll->setWidget(visualizzaBox);
    scroll->adjustSize();
    scroll->setWidgetResizable(true);

    QVBoxLayout* mall = new QVBoxLayout;
    mall->addWidget(scroll);

    mainLayout->addWidget(titoloSchedaLabel);
    mainLayout->addLayout(mall);
    mainLayout->addLayout(buttons);
    setLayout(mainLayout);
}

void LibroWidget::hide()
{
    if(!removeAutore->isHidden()) removeAutore->hide();
    if(!removeGenere->isHidden()) removeGenere->hide();
}

void LibroWidget::getAutoreSlot()
{
    element = autoriList->currentItem();
    hide();
    removeAutore->show();
}

void LibroWidget::getGenereSlot()
{
    element = generiList->currentItem();
    hide();
    removeGenere->show();
}

void LibroWidget::aggiungiAutoreSlot()
{
    QString x = autoreEdit->text();
    if(!x.isEmpty())
    {
        for(int i=0; i < autoriList->count(); ++i)
        {
            if(autoriList->item(i)->text() == x)
                return;
        }
        autoriList->addItem(autoreEdit->text());
        autoreEdit->setText("");
    }
}

void LibroWidget::rimuoviAutoreSlot()
{
    autoriList->removeItemWidget(element);
    delete element;
    removeAutore->hide();
    element = 0;
}

void LibroWidget::aggiungiGenereSlot()
{
    QString x = genereEdit->text();
    if(!x.isEmpty())
    {
        for(int i=0; i < generiList->count(); ++i)
        {
            if(generiList->item(i)->text() == x)
                return;
        }
        generiList->addItem(x);
        genereEdit->setText("");
    }
}

void LibroWidget::rimuoviGenereSlot()
{
    generiList->removeItemWidget(element);
    delete element;
    removeGenere->hide();
    element = 0;
}

void LibroWidget::apriImmagine()
{
    QString temp = QFileDialog::getOpenFileName(this, tr("Open Image"), "C://", tr("Immagine jpg (*.jpg);;Immagine png (*.png)"));
    if(!temp.isEmpty())
    {
        fileImmagine->setText(temp);
    }
}
