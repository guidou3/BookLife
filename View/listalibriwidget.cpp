#include "listalibriwidget.h"

ListaLibriWidget::ListaLibriWidget(Client* c, QString title, bool ad, QWidget *parent): ListaWidget(c, "Lista di "+title, parent)
{
    admin = ad;
    type = title;

    bold = QFont("arial", 10, 80);

    if(type == "Book")
        list = logic->getListaBookStandard();
    else
        list = logic->getListaLightNovelStandard();

    for(int i=0; i<list.size(); i++)
    {
        lista->addItem(list.at(i)->getTitolo());
    }

    sort = new QHBoxLayout;
    mainLayout->insertLayout(0, sort);

    QLabel* sortLabel = new QLabel("Ordina per: ");

    comboBox = new QComboBox;
    comboBox->addItem("-");
    comboBox->addItem("Titolo");
    comboBox->addItem("Lingua");
    comboBox->addItem("Autore");
    comboBox->addItem("Genere");

    if(type == "Book")
    {
        comboBox->addItem("Editore");
        comboBox->addItem("Curatore");
        comboBox->addItem("Collana");
    }
    else
    {
        comboBox->addItem("Lingua originale");
        comboBox->addItem("Traduttore");
    }

    sort->addWidget(sortLabel);
    sort->addWidget(comboBox);

    visualizza = new QPushButton;
    visualizza->setText("Visualizza");
    visualizza->hide();

    connect(visualizza,SIGNAL(clicked()),this,SLOT(visualizzaSlot()));
    connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(sortBySlot(int)));

    mainLayout->addWidget(visualizza);

    if(admin)
    {
        modifica = new QPushButton;
        modifica->setText("Modifica");

        rimuovi = new QPushButton;
        rimuovi->setText("Rimuovi");

        aggiungi = new QPushButton;
        aggiungi->setText("Aggiungi");

        connect(rimuovi,SIGNAL(clicked()),this,SLOT(rimuoviSlot()));
        connect(modifica,SIGNAL(clicked()),this,SLOT(modificaSlot()));
        connect(aggiungi,SIGNAL(clicked()),this,SLOT(aggiungiSlot()));

        mainLayout->addWidget(modifica);
        modifica->hide();
        mainLayout->addWidget(rimuovi);
        rimuovi->hide();
    }
    else
    {
        aggiungi = new QPushButton;
        aggiungi->setText("Aggiungi ai preferiti");
        aggiungi->hide();

        connect(aggiungi,SIGNAL(clicked()),this,SLOT(aggiungiPreferitoSlot()));
    }

    mainLayout->addWidget(aggiungi);
}

void ListaLibriWidget::getSlot()
{
    if(comboBox->currentIndex() > 1) {
        if(lista->currentItem()->font() == bold)
        {
            hideSlot();
            return;
        }
    }
    QString x = lista->currentItem()->text();

    if(type == "Book")
        logic->findBook(x);
    else
        logic->findLightNovel(x);

    if(logic->getLibroSelezionato())
    {
        emit(selected());
        if(admin)
        {
            visualizza->show();
            modifica->show();
            rimuovi->show();
        }
        else {
            visualizza->show();
            aggiungi->show();
        }

    }
    else {
        updateSlot();
    }
}

void ListaLibriWidget::updateSlot()
{
    hideSlot();
    comboBox->setCurrentIndex(0);
    logic->resetSelezionati();
    lista->clear();
    if(type == "Book") {
        list = logic->getListaBookStandard();
        for(int i=0; i<list.size(); i++)
        {
            lista->addItem(list.at(i)->getTitolo());
        }
    }
    else{
        list = logic->getListaLightNovelStandard();
        for(int i=0; i<list.size(); i++)
        {
            lista->addItem(list.at(i)->getTitolo());
        }
    }
}



void ListaLibriWidget::visualizzaSlot()
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

void ListaLibriWidget::rimuoviSlot()
{
    if(logic->getLibroSelezionato()->getType() == "Book")
    {
        QString libro = dynamic_cast<Book*>(logic->getLibroSelezionato())->getLibro();
        if(!libro.isNull())
            QFile::remove(libro);

    }
    QString immagine = logic->getLibroSelezionato()->getImmagine();

    if(!immagine.isNull())
        QFile::remove(immagine);

    logic->rimuoviLibro();
    hideSlot();
    updateSlot();
}

void ListaLibriWidget::aggiungiSlot()
{
    if(type == "Book")
    {
        BookWidget* bw = new BookWidget(logic);
        bw->show();
        connect(bw,SIGNAL(updateBook()),this,SLOT(updateSlot()));
    }
    else {
        LightNovelWidget* lnw = new LightNovelWidget(logic);
        lnw->show();
        connect(lnw,SIGNAL(updateLightNovel()),this,SLOT(updateSlot()));
    }
}

void ListaLibriWidget::aggiungiPreferitoSlot()
{
    logic->addPreferito();
    emit(updatePreferiti());
}

void ListaLibriWidget::modificaSlot()
{
    if(type == "Book")
    {
        BookWidget* bw = new BookWidget(dynamic_cast<Book*>(logic->getLibroSelezionato()), logic);
        bw->show();
        connect(bw,SIGNAL(updateBook()),this,SLOT(updateSlot()));
    }
    else {
        LightNovelWidget* lnw = new LightNovelWidget(logic, dynamic_cast<Light_novel*>(logic->getLibroSelezionato()));
        lnw->show();
        connect(lnw,SIGNAL(updateLightNovel()),this,SLOT(updateSlot()));
    }
}

void ListaLibriWidget::hideSlot()
{
    if(admin) {
        visualizza->hide();
        modifica->hide();
        rimuovi->hide();
    }
    else {
        visualizza->hide();
        aggiungi->hide();
    }
}

void ListaLibriWidget::sortBySlot(int x)
{
    hideSlot();
    lista->clear();
    switch (x) {
    case 0:
    {
        for(int i=0; i<list.size(); i++) {
            lista->addItem(list.at(i)->getTitolo());
        }
        break;
    }
    case 1:
    {
        QStringList temp;
        temp.append(list.at(0)->getTitolo());
        bool inserted;
        for(int i=1; i<list.size(); i++) {
            inserted = false;
            for(int j=0; j<temp.size(); j++) {
                if(QString::compare(list.at(i)->getTitolo(), temp.at(j), Qt::CaseInsensitive) < 0)
                {
                    temp.insert(j, list.at(i)->getTitolo());
                    inserted = true;
                    break;
                }
            }
            if(!inserted) temp.append(list.at(i)->getTitolo());
        }
        lista->addItems(temp);
        break;
    }
    case 2:
    {
        QList<Libro*> temp;

        temp.append(list.at(0));
        bool inserted;
        for(int i=1; i<list.size(); i++) {
            inserted = false;
            for(int j=0; j<temp.size(); j++) {
                if(QString::compare(list.at(i)->getLingua(), temp.at(j)->getLingua(), Qt::CaseInsensitive) < 0)
                {
                    temp.insert(j, list.at(i));
                    inserted = true;
                    break;
                }
            }
            if(!inserted) temp.append(list.at(i));
        }
        for(int i=0; i<temp.size(); i++)
        {
            QListWidgetItem* el = new QListWidgetItem;
            el->setFont(bold);

            if(temp.at(i)->getLingua().isEmpty())
                el->setText("Nessuna");
            else
                el->setText(temp.at(i)->getLingua());

            lista->addItem(el);
            lista->addItem(temp.at(i)->getTitolo());
            for(i=i+1; i<temp.size(); i++)
            {
                if(temp.at(i)->getLingua() == temp.at(i-1)->getLingua())
                    lista->addItem(temp.at(i)->getTitolo());
                else
                {
                    i = i-1;
                    break;
                }
            }
        }
        break;
    }
    case 3:
    {
        QStringList autoriList;

        bool free;
        for(int i=0; i<list.size(); i++) {
            QStringList autori = list.at(i)->getAutori();
            if(autori.isEmpty()) continue;
            for(int j=0; j<autori.size(); j++) {
                free = true;
                for(int k=0; k<autoriList.size(); k++) {
                    if(autoriList.at(k) == autori.at(j))
                    {
                        free = false;
                        break;
                    }
                }
                if(free)
                    autoriList.append(autori.at(j));
            }
        }
        for(int i=0; i<autoriList.size(); i++)
        {
            QListWidgetItem* el = new QListWidgetItem(autoriList.at(i));
            el->setFont(bold);
            lista->addItem(el);
            for(int j=0; j<list.size(); j++)
            {
                QStringList autori = list.at(j)->getAutori();
                if(!autori.isEmpty())
                {
                    for(int k=0; k<autori.size(); k++)
                    {
                        if(autori.at(k) == autoriList.at(i))
                            lista->addItem(list.at(j)->getTitolo());
                    }
                }
            }
        }
        QListWidgetItem* el = new QListWidgetItem("Nessuno");
        el->setFont(bold);
        lista->addItem(el);
        for(int i=0; i<list.size(); i++)
        {
            if(list.at(i)->getAutori().isEmpty())
                lista->addItem(list.at(i)->getTitolo());
        }
        break;
    }
    case 4:
    {
        QStringList generiList;

        bool free;
        for(int i=0; i<list.size(); i++) {
            QStringList generi = list.at(i)->getGeneri();
            if(generi.isEmpty()) continue;
            for(int j=0; j<generi.size(); j++) {
                free = true;
                for(int k=0; k<generiList.size(); k++) {
                    if(generiList.at(k) == generi.at(j))
                    {
                        free = false;
                        break;
                    }
                }
                if(free)
                    generiList.append(generi.at(j));
            }
        }
        for(int i=0; i<generiList.size(); i++)
        {
            QListWidgetItem* el = new QListWidgetItem(generiList.at(i));
            el->setFont(bold);
            lista->addItem(el);
            for(int j=0; j<list.size(); j++)
            {
                QStringList generi = list.at(j)->getGeneri();
                if(!generi.isEmpty())
                {
                    for(int k=0; k<generi.size(); k++)
                    {
                        if(generi.at(k) == generiList.at(i))
                            lista->addItem(list.at(j)->getTitolo());
                    }
                }
            }
        }
        QListWidgetItem* el = new QListWidgetItem("Nessuno");
        el->setFont(bold);
        lista->addItem(el);
        for(int i=0; i<list.size(); i++)
        {
            if(list.at(i)->getGeneri().isEmpty())
                lista->addItem(list.at(i)->getTitolo());
        }
        break;
    }
    case 5:
    {
        bool inserted;

        if(type=="Book")
        {
            QList<Book*> temp;

            temp.append(dynamic_cast<Book*>(list.at(0)));

            for(int i=1; i<list.size(); i++) {
                inserted = false;
                Book* current = dynamic_cast<Book*>(list.at(i));
                for(int j=0; j<temp.size(); j++) {
                    if(QString::compare(current->getEditore(), temp.at(j)->getEditore(), Qt::CaseInsensitive) < 0)
                    {
                        temp.insert(j, current);
                        inserted = true;
                        break;
                    }
                }
                if(!inserted) temp.append(current);
            }
            for(int i=0; i<temp.size(); i++)
            {
                QListWidgetItem* el = new QListWidgetItem;
                el->setFont(bold);

                if(temp.at(i)->getEditore().isEmpty())
                    el->setText("Nessuno");
                else
                    el->setText(temp.at(i)->getEditore());

                lista->addItem(el);
                lista->addItem(temp.at(i)->getTitolo());
                for(i=i+1; i<temp.size(); i++)
                {
                    if(temp.at(i)->getEditore() == temp.at(i-1)->getEditore())
                        lista->addItem(temp.at(i)->getTitolo());
                    else
                    {
                        i -= 1;
                        break;
                    }
                }
            }
        }
        else
        {
            QList<Light_novel*> temp;

            temp.append(dynamic_cast<Light_novel*>(list.at(0)));

            for(int i=1; i<list.size(); i++) {
                inserted = false;
                Light_novel* current = dynamic_cast<Light_novel*>(list.at(i));
                for(int j=0; j<temp.size(); j++) {
                    if(QString::compare(current->getLinguaOriginale(), temp.at(j)->getLinguaOriginale(), Qt::CaseInsensitive) < 0)
                    {
                        temp.insert(j, current);
                        inserted = true;
                        break;
                    }
                }
                if(!inserted) temp.append(current);
            }
            for(int i=0; i<temp.size(); i++)
            {
                QListWidgetItem* el = new QListWidgetItem;
                el->setFont(bold);

                if(temp.at(i)->getLinguaOriginale().isEmpty())
                    el->setText("Nessuno");
                else
                    el->setText(temp.at(i)->getLinguaOriginale());

                lista->addItem(el);
                lista->addItem(temp.at(i)->getTitolo());
                for(i=i+1; i<temp.size(); i++)
                {
                    if(temp.at(i)->getLinguaOriginale() == temp.at(i-1)->getLinguaOriginale())
                        lista->addItem(temp.at(i)->getTitolo());
                    else
                    {
                        i -= 1;
                        break;
                    }
                }
            }
        }
        break;
    }
    case 6:
    {
        bool free;

        if(type=="Book")
        {
            QStringList curatoriList;

            for(int i=0; i<list.size(); i++) {
                QStringList curatori = dynamic_cast<Book*>(list.at(i))->getCuratori();
                if(curatori.isEmpty()) continue;
                for(int j=0; j<curatori.size(); j++) {
                    free = true;
                    for(int k=0; k<curatoriList.size(); k++) {
                        if(curatoriList.at(k) == curatori.at(j))
                        {
                            free = false;
                            break;
                        }
                    }
                    if(free)
                        curatoriList.append(curatori.at(j));
                }
            }
            for(int i=0; i<curatoriList.size(); i++)
            {
                QListWidgetItem* el = new QListWidgetItem(curatoriList.at(i));
                el->setFont(bold);
                lista->addItem(el);
                for(int j=0; j<list.size(); j++)
                {
                    QStringList curatori = dynamic_cast<Book*>(list.at(j))->getCuratori();
                    if(!curatori.isEmpty())
                    {
                        for(int k=0; k<curatori.size(); k++)
                        {
                            if(curatori.at(k) == curatoriList.at(i))
                                lista->addItem(list.at(j)->getTitolo());
                        }
                    }
                }
            }
            QListWidgetItem* el = new QListWidgetItem("Nessuno");
            el->setFont(bold);
            lista->addItem(el);
            for(int i=0; i<list.size(); i++)
            {
                if(dynamic_cast<Book*>(list.at(i))->getCuratori().isEmpty())
                    lista->addItem(list.at(i)->getTitolo());
            }
        }
        else
        {
            QStringList traduttoriList;

            for(int i=0; i<list.size(); i++) {
                QStringList traduttori = dynamic_cast<Light_novel*>(list.at(i))->getTraduttori();
                if(traduttori.isEmpty()) continue;
                for(int j=0; j<traduttori.size(); j++) {
                    free = true;
                    for(int k=0; k<traduttoriList.size(); k++) {
                        if(traduttoriList.at(k) == traduttori.at(j))
                        {
                            free = false;
                            break;
                        }
                    }
                    if(free)
                        traduttoriList.append(traduttori.at(j));
                }
            }
            for(int i=0; i<traduttoriList.size(); i++)
            {
                QListWidgetItem* el = new QListWidgetItem(traduttoriList.at(i));
                el->setFont(bold);
                lista->addItem(el);
                for(int j=0; j<list.size(); j++)
                {
                    QStringList traduttori = dynamic_cast<Light_novel*>(list.at(j))->getTraduttori();
                    if(!traduttori.isEmpty())
                    {
                        for(int k=0; k<traduttori.size(); k++)
                        {
                            if(traduttori.at(k) == traduttoriList.at(i))
                                lista->addItem(list.at(j)->getTitolo());
                        }
                    }
                }
            }
            QListWidgetItem* el = new QListWidgetItem("Nessuno");
            el->setFont(bold);
            lista->addItem(el);
            for(int i=0; i<list.size(); i++)
            {
                if(dynamic_cast<Light_novel*>(list.at(i))->getTraduttori().isEmpty())
                    lista->addItem(list.at(i)->getTitolo());
            }
        }
        break;
    }
    case 7:
    {
        bool inserted;
        QList<Book*> temp;

        temp.append(dynamic_cast<Book*>(list.at(0)));

        for(int i=1; i<list.size(); i++) {
            inserted = false;
            Book* current = dynamic_cast<Book*>(list.at(i));
            for(int j=0; j<temp.size(); j++) {
                if(QString::compare(current->getCollana(), temp.at(j)->getCollana(), Qt::CaseInsensitive) < 0)
                {
                    temp.insert(j, current);
                    inserted = true;
                    break;
                }
            }
            if(!inserted) temp.append(current);
        }
        for(int i=0; i<temp.size(); i++)
        {
            QListWidgetItem* el = new QListWidgetItem;
            el->setFont(bold);

            if(temp.at(i)->getCollana().isEmpty())
                el->setText("Nessuno");
            else
                el->setText(temp.at(i)->getCollana());

            lista->addItem(el);
            lista->addItem(temp.at(i)->getTitolo());
            for(i=i+1; i<temp.size(); i++)
            {
                if(temp.at(i)->getCollana() == temp.at(i-1)->getCollana())
                    lista->addItem(temp.at(i)->getTitolo());
                else
                {
                    i -= 1;
                    break;
                }
            }
        }
        break;
    }
    default:
        break;
    }
}
