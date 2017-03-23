#include "ricercaavanzatawidget.h"

RicercaAvanzataWidget::RicercaAvanzataWidget(Client* c, QWidget* parent): QWidget(parent), logic(c)
{
    initialBox = new QGroupBox;
    layout = new QVBoxLayout;
    titoloWidget = new QLabel;
    QFont font = QFont("arial", 15);
    titoloWidget->setFont(font);

    QPushButton* libro = new QPushButton;
    libro->setText("Ricerca libro generico");
    libro->setMinimumHeight(40);
    libro->setMinimumWidth(150);

    QPushButton* book = new QPushButton;
    book->setText("Ricerca Book");
    book->setMinimumHeight(40);
    book->setMinimumWidth(150);

    QPushButton* lightNovel = new QPushButton;
    lightNovel->setText("Ricerca Light Novel");
    lightNovel->setMinimumHeight(40);
    lightNovel->setMinimumWidth(150);

    connect(libro, SIGNAL(clicked()), this, SLOT(libroViewSlot()));
    connect(book, SIGNAL(clicked()), this, SLOT(bookViewSlot()));
    connect(lightNovel, SIGNAL(clicked()), this, SLOT(lightNovelViewSlot()));

    QHBoxLayout* initial = new QHBoxLayout;
    initial->addWidget(libro);
    initial->addWidget(book);
    initial->addWidget(lightNovel);

    initialBox->setLayout(initial);
    layout->addWidget(initialBox);
    setLayout(layout);
}

void RicercaAvanzataWidget::initializeCommonView()
{
    initialBox->hide();

    inputForm = new QFormLayout;

    titoloEdit = new QLineEdit;
    linguaEdit = new QLineEdit;
    autoreEdit = new QLineEdit;
    genereEdit = new QLineEdit;

    inputForm->addRow("Titolo: ", titoloEdit);
    inputForm->addRow("Lingua: ", linguaEdit);
    inputForm->addRow("Autore: ", autoreEdit);
    inputForm->addRow("Genere: ", genereEdit);

    reset = new QPushButton;
    reset->setText("Reset");
    reset->setMinimumHeight(40);
    reset->setMinimumWidth(150);

    cerca = new QPushButton;
    cerca->setText("Cerca");
    cerca->setMinimumHeight(40);
    cerca->setMinimumWidth(150);

    QHBoxLayout* buttons = new QHBoxLayout;
    buttons->addWidget(reset);
    buttons->addWidget(cerca);

    layout->addWidget(titoloWidget);
    layout->setAlignment(titoloWidget, Qt::AlignHCenter);
    layout->addSpacing(15);
    layout->addLayout(inputForm);
    layout->addSpacing(15);
    layout->addLayout(buttons);
}

void RicercaAvanzataWidget::libroViewSlot()
{
    initializeCommonView();
    titoloWidget->setText("Ricerca libro generico");

    connect(reset, SIGNAL(clicked()), this, SLOT(resetLibroSlot()));
    connect(cerca, SIGNAL(clicked()), this, SLOT(cercaLibroSlot()));
}

void RicercaAvanzataWidget::bookViewSlot()
{
    initializeCommonView();
    titoloWidget->setText("Ricerca Book");

    editoreEdit = new QLineEdit;
    collanaEdit = new QLineEdit;
    curatoreEdit = new QLineEdit;

    inputForm->addRow("Editore: ", editoreEdit);
    inputForm->addRow("Collana: ", collanaEdit);
    inputForm->addRow("Curatore: ", curatoreEdit);

    connect(reset, SIGNAL(clicked()), this, SLOT(resetBookSlot()));
    connect(cerca, SIGNAL(clicked()), this, SLOT(cercaBookSlot()));
}

void RicercaAvanzataWidget::lightNovelViewSlot()
{
    initializeCommonView();
    titoloWidget->setText("Ricerca Light Novel");

    traduttoreEdit = new QLineEdit;
    lingua_originaleEdit = new QLineEdit;

    // pulsanti
    completatoTrue = new QRadioButton;
    completatoFalse = new QRadioButton;

    completatoTrue->setText("Vero");
    completatoFalse->setText("Falso");
    completatoFalse->setChecked(true);

    QHBoxLayout* rb = new QHBoxLayout;
    rb->addWidget(completatoFalse);
    rb->addWidget(completatoTrue);

    inputForm->addRow("Traduttore: ", traduttoreEdit);
    inputForm->addRow("Lingua originale: ", lingua_originaleEdit);
    inputForm->addRow("Completato: ", rb);

    connect(reset, SIGNAL(clicked()), this, SLOT(resetLightNovelSlot()));
    connect(cerca, SIGNAL(clicked()), this, SLOT(cercaLightNovelSlot()));
}

void RicercaAvanzataWidget::cercaLibroSlot()
{
    ListaRisultatiRicercaWidget* temp = new ListaRisultatiRicercaWidget(logic, logic->findLibro(titoloEdit->text(), linguaEdit->text(), autoreEdit->text(), genereEdit->text()));
    temp->show();
}

void RicercaAvanzataWidget::cercaBookSlot()
{
    ListaRisultatiRicercaWidget* temp = new ListaRisultatiRicercaWidget(logic, logic->findBook(titoloEdit->text(), linguaEdit->text(), autoreEdit->text(), genereEdit->text(), editoreEdit->text(), collanaEdit->text(), curatoreEdit->text()));
    temp->show();
}

void RicercaAvanzataWidget::cercaLightNovelSlot()
{
    bool completato = completatoTrue->isChecked();
    ListaRisultatiRicercaWidget* temp = new ListaRisultatiRicercaWidget(logic, logic->findLightNovel(titoloEdit->text(), linguaEdit->text(), autoreEdit->text(), genereEdit->text(), traduttoreEdit->text(), lingua_originaleEdit->text(), completato));
    temp->show();
}

void RicercaAvanzataWidget::resetLibroSlot()
{
    titoloEdit->setText("");
    linguaEdit->setText("");
    autoreEdit->setText("");
    genereEdit->setText("");
}

void RicercaAvanzataWidget::resetBookSlot()
{
    resetLibroSlot();
    editoreEdit->setText("");
    collanaEdit->setText("");
    curatoreEdit->setText("");
}

void RicercaAvanzataWidget::resetLightNovelSlot()
{
    resetLibroSlot();
    traduttoreEdit->setText("");
    lingua_originaleEdit->setText("");
    completatoFalse->setChecked(true);
}
