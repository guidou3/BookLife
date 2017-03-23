#include "lightnovelwidget.h"
#include "writerclientwidget.h"

LightNovelWidget::~LightNovelWidget(){}

LightNovelWidget::LightNovelWidget(Client* c, Light_novel* ln, QWidget *parent) : LibroWidget(ln, c, parent), lightNovel(ln)
{
    if(lightNovel == NULL) close();

    initializeLightNovel();

    titoloSchedaLabel->setText("Modifica informazioni light novel");

    capitoli_tradottiEdit->setText(QString::number(lightNovel->getCapitoliTradotti()));
    capitoli_scrittiEdit->setText(QString::number(lightNovel->getCapitoliScritti()));
    lingua_originaleEdit->setText(lightNovel->getLinguaOriginale());

    traduttoriList->addItems(lightNovel->getTraduttori());

    if(lightNovel->isCompletato()) completatoTrue->setChecked(true);
    else completatoFalse->setChecked(true);
}

LightNovelWidget::LightNovelWidget(Client* c, QWidget *parent) : LibroWidget(c, parent)
{
    lightNovel = new Light_novel("Titolo temporaneo");

    initializeLightNovel();

    titoloSchedaLabel->setText("Crea una nuova light novel");

    fileImmagine->setText("NULL");

    completatoFalse->setChecked(true);
}

void LightNovelWidget::initializeLightNovel()
{
    capitoli_tradottiEdit = new QLineEdit;
    capitoli_scrittiEdit = new QLineEdit;
    lingua_originaleEdit = new QLineEdit;
    traduttoreEdit = new QLineEdit;

    capitoli_tradottiEdit->setValidator(new QIntValidator(0, 2000, this));
    capitoli_scrittiEdit->setValidator(new QIntValidator(0, 2000, this));

    traduttoriList = new QListWidget;

    completatoTrue = new QRadioButton;
    completatoFalse = new QRadioButton;

    addTraduttore = new QPushButton;
    removeTraduttore = new QPushButton;

    completatoTrue->setText("Vero");
    completatoFalse->setText("Falso");

    addTraduttore->setText("Inserisci");
    removeTraduttore->setText("Rimuovi");
    removeTraduttore->hide();

    traduttoriList->setMaximumHeight(100);

    connect(traduttoriList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getTraduttoreSlot()));
    connect(addTraduttore,SIGNAL(clicked()),this,SLOT(aggiungiTraduttoreSlot()));
    connect(removeTraduttore,SIGNAL(clicked()),this,SLOT(rimuoviTraduttoreSlot()));

    QVBoxLayout* v3 = new QVBoxLayout;
    v3->addWidget(traduttoriList);
    v3->addWidget(removeTraduttore);

    QHBoxLayout* h3 = new QHBoxLayout;
    h3->addWidget(traduttoreEdit);
    h3->addWidget(addTraduttore);

    QHBoxLayout* rb = new QHBoxLayout;
    rb->addWidget(completatoFalse);
    rb->addWidget(completatoTrue);

    rowLayout->addRow("Capitoli scritti: ", capitoli_scrittiEdit);
    rowLayout->addRow("Capitoli tradotti: ", capitoli_tradottiEdit);
    rowLayout->addRow("Completato: ", rb);
    rowLayout->addRow("Lingua originale: ", lingua_originaleEdit);
    listLayout->addRow("Traduttori: ", v3);
    listLayout->addRow("Nuovo traduttore: ", h3);
}

void LightNovelWidget::salvaSlot()
{
    if(!titoloEdit->text().isEmpty() && !logic->getSession()->db->findLightNovel(titoloEdit->text()) && !logic->getSession()->db->findBook(titoloEdit->text()))
    {
        lightNovel->setTitolo(titoloEdit->text());
        if(!dataPubblicazioneEdit->text().isEmpty()) lightNovel->setDataPubblicazione(dataPubblicazioneEdit->date());
        if(!linguaEdit->text().isEmpty()) lightNovel->setLingua(linguaEdit->text());
        if(!descrizioneEdit->text().isEmpty()) lightNovel->setDescrizione(descrizioneEdit->text());
        if(!capitoli_tradottiEdit->text().isEmpty()) lightNovel->setCapitoliTradotti(capitoli_tradottiEdit->text().toInt());
        if(!capitoli_scrittiEdit->text().isEmpty()) lightNovel->setCapitoliScritti(capitoli_scrittiEdit->text().toInt());

        lightNovel->setCompletato(completatoTrue->isChecked()); // gestione radio button

        if(!lingua_originaleEdit->text().isEmpty()) lightNovel->setLinguaOriginale(lingua_originaleEdit->text());

        QString x = fileImmagine->text();
        if(x != "NULL")
        {
            lightNovel->setImmagine(lightNovel->getTitolo() + x.mid(x.length()-4));
            QFile::copy(x, lightNovel->getImmagine());
        }

        QList<QString> list;
        for(int i=0; i < autoriList->count(); ++i)
          list.append(autoriList->item(i)->text());

        if(!list.isEmpty()) lightNovel->setAutori(list);

        list.clear();
        for(int i=0; i < generiList->count(); ++i)
          list.append(generiList->item(i)->text());

        if(!list.isEmpty()) lightNovel->setGeneri(list);

        list.clear();
        for(int i=0; i < traduttoriList->count(); ++i)
        {
            list.append(traduttoriList->item(i)->text());
            Scrittore* sc = dynamic_cast<Scrittore*>(logic->getSession()->db->findUtente(list.at(i)));
            if(sc) sc->setMine(lightNovel, true);
        }

        if(!list.isEmpty()) lightNovel->setTraduttori(list);

        logic->addLightNovel(lightNovel);
        emit(updateLightNovel());
        ViewLightNovelWidget* temp = new ViewLightNovelWidget(lightNovel, logic);
        close();
        temp->show();
    }
    else
    {
        if(titoloEdit->text().isEmpty()) titoloLabel->setText("Questo campo non può essere vuoto");
        else titoloLabel->setText("Un libro con lo stesso titolo è\ngià presente nel catalogo");
        titoloLabel->show();
    }
}

void LightNovelWidget::aggiornaSlot()
{
    Light_novel* nuovo = new Light_novel(lightNovel->getTitolo());
    nuovo->setDataPubblicazione(dataPubblicazioneEdit->date());
    nuovo->setLingua(linguaEdit->text());
    nuovo->setDescrizione(descrizioneEdit->text());
    nuovo->setCapitoliTradotti(capitoli_tradottiEdit->text().toInt());
    nuovo->setCapitoliScritti(capitoli_scrittiEdit->text().toInt());

    nuovo->setCompletato(completatoTrue->isChecked()); // gestione radio button

    nuovo->setLinguaOriginale(lingua_originaleEdit->text());

    if(fileImmagine->text() != lightNovel->getImmagine() && fileImmagine->text()!= "NULL")
    {
        QString x = fileImmagine->text().mid(fileImmagine->text().length()-4);
        if(lightNovel->getImmagine().isEmpty())
        {
            nuovo->setImmagine(nuovo->getTitolo() + x);
            cout << "campo precedentemente vuoto: " << nuovo->getImmagine().toStdString() << endl;
        }
        else
        {
            cout << "campo precedentemente non vuoto" << endl;
            QFile::remove(lightNovel->getImmagine());
            if(lightNovel->getImmagine().mid(lightNovel->getImmagine().length()-4) != x) //controllo se le estensioni sono uguali
            {
                nuovo->setImmagine(nuovo->getTitolo() + x);
                cout << "estensione diversa: " << nuovo->getImmagine().toStdString() << endl;
            }
            else
            {
                nuovo->setImmagine(lightNovel->getImmagine());
                cout << "stessa estensione: " << nuovo->getImmagine().toStdString() << endl;
            }
        }
        QFile::copy(fileImmagine->text(), nuovo->getImmagine());
    }
    else if(fileImmagine->text() == lightNovel->getImmagine() && fileImmagine->text()!= "NULL")
    {
        nuovo->setImmagine(lightNovel->getImmagine());
    }
    lightNovel->setImmagine("");

    QList<QString> list;
    for(int i=0; i < autoriList->count(); ++i)
      list.append(autoriList->item(i)->text());

    if(!list.isEmpty()) nuovo->setAutori(list);

    list.clear();
    for(int i=0; i < generiList->count(); ++i)
      list.append(generiList->item(i)->text());

    if(!list.isEmpty()) nuovo->setGeneri(list);

    list.clear();
    QStringList qsl = lightNovel->getTraduttori();
    for(int i=0; i < traduttoriList->count(); ++i)
    {
        list.append(traduttoriList->item(i)->text());
        if(!qsl.contains(list.at(i)))
        {
            Scrittore* sc = dynamic_cast<Scrittore*>(logic->getSession()->db->findUtente(list.at(i)));
            if(sc) sc->setMine(nuovo, true);
        }
    }
    for(int i=0; i<qsl.size(); ++i)
    {
        if(!list.contains(qsl.at(i)))
        {
            Scrittore* sc = dynamic_cast<Scrittore*>(logic->getSession()->db->findUtente(list.at(i)));
            if(sc) sc->setMine(nuovo, false);
        }
    }


    if(!list.isEmpty())
        nuovo->setTraduttori(list);

    QList<Capitolo*> caps = lightNovel->getCapitoli();
    for(int i=0; i<caps.length(); ++i)
    {
        nuovo->addCapitolo(caps.at(i));
    }


    logic->updateLightNovel(nuovo);
    emit(updateLightNovel());
    close();
}

void LightNovelWidget::hide()
{
    LibroWidget::hide();
    if(!removeTraduttore->isHidden()) removeTraduttore->hide();
}

void LightNovelWidget::getTraduttoreSlot()
{
    element = traduttoriList->currentItem();
    hide();
    removeTraduttore->show();
}

void LightNovelWidget::aggiungiTraduttoreSlot()
{
    QString x = traduttoreEdit->text();
    if(!x.isEmpty())
    {
        for(int i=0; i < traduttoriList->count(); ++i)
        {
            if(traduttoriList->item(i)->text() == x)
                return;
        }
        traduttoriList->addItem(x);
        traduttoreEdit->setText("");
    }
}

void LightNovelWidget::rimuoviTraduttoreSlot()
{
    traduttoriList->removeItemWidget(element);
    delete element;
    removeTraduttore->hide();
    element = 0;
}
