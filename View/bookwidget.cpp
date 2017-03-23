#include "bookwidget.h"

BookWidget::BookWidget(Book* lib, Client* c, QWidget *parent) : LibroWidget(lib, c, parent), libro(lib)
{
    if(libro == NULL)
    {
        cerr << "Libro non fornito" << endl;
        return;
    }

    initializeBook();

    titoloSchedaLabel->setText("Modifica informazioni del Book");

    numeroPagineEdit->setText(QString::number(libro->getNumeroPagine()));
    editoreEdit->setText(libro->getEditore());
    collanaEdit->setText(libro->getCollana());

    fileLibro->setText(libro->getLibro());
    if(fileLibro->text().isEmpty()) fileLibro->setText("NULL");

    curatoriList->addItems(libro->getCuratori());
}

BookWidget::BookWidget(Client* c, QWidget *parent) : LibroWidget(c, parent)
{
    libro = new Book("Titolo temporaneo");

    initializeBook();

    titoloSchedaLabel->setText("Crea un nuovo Book");

    fileLibro->setText("NULL");
}

BookWidget::~BookWidget()
{

}

void BookWidget::initializeBook()
{
    numeroPagineEdit = new QLineEdit;
    numeroPagineEdit->setValidator(new QIntValidator(0, 10000, this));
    editoreEdit = new QLineEdit;
    collanaEdit = new QLineEdit;
    curatoreEdit = new QLineEdit;

    fileLibro = new QLabel;

    curatoriList = new QListWidget;

    addCuratore = new QPushButton;
    removeCuratore = new QPushButton;
    addLibro = new QPushButton;

    addCuratore->setText("Inserisci");
    removeCuratore->setText("Rimuovi");
    removeCuratore->hide();
    addLibro->setText("Aggiungi file");

    curatoriList->setMaximumHeight(100);

    connect(curatoriList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getCuratoreSlot()));
    connect(addCuratore,SIGNAL(clicked()),this,SLOT(aggiungiCuratoreSlot()));
    connect(removeCuratore,SIGNAL(clicked()),this,SLOT(rimuoviCuratoreSlot()));
    connect(addLibro,SIGNAL(clicked()),this,SLOT(apriFile()));

    QVBoxLayout* v3 = new QVBoxLayout;
    v3->addWidget(curatoriList);
    v3->addWidget(removeCuratore);

    QHBoxLayout* h3 = new QHBoxLayout;
    h3->addWidget(curatoreEdit);
    h3->addWidget(addCuratore);

    rowLayout->addRow("Numero pagine: ", numeroPagineEdit);
    rowLayout->addRow("Editore: ", editoreEdit);
    rowLayout->addRow("Collana: ", collanaEdit);
    listLayout->addRow("Curatori: ", v3);
    listLayout->addRow("Nuovo curatore: ", h3);
    othersLayout->addRow("File selezionato : ", fileLibro);
    othersLayout->addRow("", addLibro);
}

void BookWidget::hide()
{
    LibroWidget::hide();
    if(!removeCuratore->isHidden()) removeCuratore->hide();
}

void BookWidget::salvaSlot()
{
    if(!titoloEdit->text().isEmpty() && !logic->getSession()->db->findBook(titoloEdit->text()) && !logic->getSession()->db->findLightNovel(titoloEdit->text()))
    {
        libro->setTitolo(titoloEdit->text());
        if(!dataPubblicazioneEdit->text().isEmpty()) libro->setDataPubblicazione(dataPubblicazioneEdit->date());
        if(!linguaEdit->text().isEmpty()) libro->setLingua(linguaEdit->text());
        if(!descrizioneEdit->text().isEmpty()) libro->setDescrizione(descrizioneEdit->text());
        if(!numeroPagineEdit->text().isEmpty()) libro->setNumeroPagine(numeroPagineEdit->text().toInt());
        if(!editoreEdit->text().isEmpty()) libro->setEditore(editoreEdit->text());
        if(!collanaEdit->text().isEmpty()) libro->setCollana(collanaEdit->text());
        if(fileLibro->text() != "NULL")
        {
            libro->setLibro(libro->getTitolo() + ".pdf");
            QFile::copy(fileLibro->text(), libro->getLibro());
        }
        QString x = fileImmagine->text();
        if(x != "NULL")
        {
            libro->setImmagine(libro->getTitolo() + x.mid(x.length()-4));
            QFile::copy(x, libro->getImmagine());
        }

        QList<QString> list;
        for(int i=0; i < autoriList->count(); ++i)
          list.append(autoriList->item(i)->text());

        if(!list.isEmpty()) libro->setAutori(list);

        list.clear();
        for(int i=0; i < generiList->count(); ++i)
          list.append(generiList->item(i)->text());

        if(!list.isEmpty()) libro->setGeneri(list);

        list.clear();
        for(int i=0; i < curatoriList->count(); ++i)
          list.append(curatoriList->item(i)->text());

        if(!list.isEmpty()) libro->setCuratori(list);

        logic->addBook(libro);
        emit(updateBook());
        ViewBookWidget* temp = new ViewBookWidget(libro);
        close();
        temp->show();
    }
    else
    {
        if(titoloEdit->text().isEmpty()) titoloLabel->setText("Questo campo non può essere vuoto");
        else titoloLabel->setText("Un libro con lo stesso titolo è\ngià presente nel catablogo");
        titoloLabel->show();
    }
}

void BookWidget::aggiornaSlot()
{
    Book* nuovo = new Book(libro->getTitolo());
    nuovo->setDataPubblicazione(dataPubblicazioneEdit->date());
    nuovo->setLingua(linguaEdit->text());
    nuovo->setDescrizione(descrizioneEdit->text());
    nuovo->setNumeroPagine(numeroPagineEdit->text().toInt());
    nuovo->setEditore(editoreEdit->text());
    nuovo->setCollana(collanaEdit->text());

    if(fileLibro->text() != libro->getLibro() &&  fileLibro->text()!= "NULL")
    {
        if(libro->getLibro().isEmpty())
        {
            nuovo->setLibro(nuovo->getTitolo() + ".pdf");
        }
        else
        {
            QFile::remove(libro->getLibro());
            nuovo->setLibro(libro->getLibro());
        }
        QFile::copy(fileLibro->text(), nuovo->getLibro());
    }
    else if(fileLibro->text() == libro->getLibro())
    {
        nuovo->setLibro(libro->getLibro());
    }
    libro->setLibro("");

    if(fileImmagine->text() != libro->getImmagine() && fileImmagine->text()!= "NULL")
    {
        QString x = fileImmagine->text().mid(fileImmagine->text().length()-4);
        if(libro->getImmagine().isEmpty())
        {
            nuovo->setImmagine(nuovo->getTitolo() + x);
        }
        else
        {
            QFile::remove(libro->getImmagine());
            if(libro->getImmagine().mid(libro->getImmagine().length()-4) != x) //controllo se le estensioni sono uguali
                nuovo->setImmagine(nuovo->getTitolo() + x);
            else
                nuovo->setImmagine(libro->getImmagine());
        }
        QFile::copy(fileImmagine->text(), nuovo->getImmagine());
    }
    else if(fileImmagine->text() == libro->getImmagine())
    {
        nuovo->setImmagine(libro->getImmagine());
    }
    libro->setImmagine("");

    QList<QString> list;
    for(int i=0; i < autoriList->count(); ++i)
      list.append(autoriList->item(i)->text());

    if(!list.isEmpty()) nuovo->setAutori(list);

    list.clear();
    for(int i=0; i < generiList->count(); ++i)
      list.append(generiList->item(i)->text());

    if(!list.isEmpty()) nuovo->setGeneri(list);

    list.clear();
    for(int i=0; i < curatoriList->count(); ++i)
      list.append(curatoriList->item(i)->text());

    if(!list.isEmpty()) nuovo->setCuratori(list);

    logic->updateBook(nuovo);
    emit(updateBook());
    close();
}

void BookWidget::getCuratoreSlot()
{
    element = curatoriList->currentItem();
    hide();
    removeCuratore->show();
}

void BookWidget::aggiungiCuratoreSlot()
{
    QString x = curatoreEdit->text();
    if(!x.isEmpty())
    {
        for(int i=0; i < curatoriList->count(); ++i)
        {
            if(curatoriList->item(i)->text() == x)
                return;
        }
        curatoriList->addItem(x);
        curatoreEdit->setText("");
    }
}

void BookWidget::rimuoviCuratoreSlot()
{
    curatoriList->removeItemWidget(element);
    delete element;
    removeCuratore->hide();
    element = 0;
}

void BookWidget::apriFile()
{
    QString temp = QFileDialog::getOpenFileName(this, tr("Open File"), "C://", tr("Pdf File (*.pdf)"));
    if(!temp.isEmpty())
    {
        fileLibro->setText(temp);
    }
}
