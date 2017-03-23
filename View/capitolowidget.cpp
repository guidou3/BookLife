#include "capitolowidget.h"

#include <QScrollArea>

CapitoloWidget::~CapitoloWidget() {}

CapitoloWidget::CapitoloWidget(Capitolo* cap, QWidget *parent) : current(cap), QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    titoloLabel = new QLabel;
    testoBrowser = new QTextBrowser;

    esci = new QPushButton;

    titoloLabel->setText(current->getTitolo());
    QFont font;
    font.setBold(true);
    titoloLabel->setFont(font);
    testoBrowser->setText(current->getTesto());
    testoBrowser->setMaximumHeight(800);

    esci->setText("ESCI");
    esci->setMaximumWidth(200);

    connect(esci, SIGNAL(clicked()), this, SLOT(close()));

    mainLayout->addWidget(titoloLabel);
    mainLayout->setAlignment(titoloLabel, Qt::AlignCenter);
    mainLayout->setSpacing(30);
    mainLayout->addWidget(testoBrowser);
    mainLayout->addWidget(esci);
    mainLayout->setAlignment(esci, Qt::AlignCenter);
    setLayout(mainLayout);
}

CapitoloWidget::CapitoloWidget(Light_novel* ln, QWidget *parent) : lightNovel(ln), QWidget(parent)
{
    initialize();
    titoloEdit->setPlaceholderText("Titolo del capitolo");
    testoEdit->setPlaceholderText("Testo del capitolo");

    testoEdit->setWordWrapMode(QTextOption::WordWrap);

    connect(salva, SIGNAL(clicked()), this, SLOT(salvaSlot()));
}

CapitoloWidget::CapitoloWidget(Light_novel* ln, int i, QWidget *parent) : lightNovel(ln), index(i), QWidget(parent)
{
    initialize();
    current = lightNovel->getCapitolo(index);

    titoloEdit->setText(current->getTitolo());
    testoEdit->setText(current->getTesto());
    testoEdit->setWordWrapMode(QTextOption::WordWrap);

    connect(salva, SIGNAL(clicked()), this, SLOT(aggiornaSlot()));
}

void CapitoloWidget::initialize()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    titoloEdit = new QLineEdit;
    testoEdit = new QTextEdit;

    titoloLabel = new QLabel;
    testoLabel = new QLabel;

    esci = new QPushButton;
    salva = new QPushButton;

    testoEdit->setMinimumHeight(300);
    testoEdit->setMinimumWidth(300);

    esci->setText("ESCI");
    esci->setMaximumWidth(200);
    salva->setText("SALVA");
    salva->setMaximumWidth(200);

    connect(esci, SIGNAL(clicked()), this, SLOT(close()));

    QHBoxLayout* buttons = new QHBoxLayout;

    buttons->addWidget(esci);
    buttons->addWidget(salva);

    mainLayout->addWidget(titoloEdit);
    mainLayout->addWidget(titoloLabel);
    mainLayout->addWidget(testoEdit);
    mainLayout->addWidget(testoLabel);
    mainLayout->addLayout(buttons);
    setLayout(mainLayout);
}

void CapitoloWidget::salvaSlot()
{
    hide();
    if(!titoloEdit->text().isEmpty() && !testoEdit->toPlainText().isEmpty())
    {
        current = new Capitolo();
        current->setTitolo(titoloEdit->text());
        current->setTesto(testoEdit->toPlainText());
        lightNovel->addCapitolo(current);
        emit(updateCapitoli());
        close();
    }
    else
    {
        if(titoloEdit->text().isEmpty())
        {
            titoloLabel->setText("Campo obbligatorio");
            titoloLabel->show();
        }
        if(testoEdit->toPlainText().isEmpty())
        {
            testoLabel->setText("Campo obbligatorio");
            testoLabel->show();
        }
    }
}

void CapitoloWidget::aggiornaSlot()
{
    hide();
    if(!titoloEdit->text().isEmpty() && !testoEdit->toPlainText().isEmpty())
    {
        Capitolo* nuovo = new Capitolo();
        nuovo->setTitolo(titoloEdit->text());
        nuovo->setTesto(testoEdit->toPlainText());
        lightNovel->modificaCapitolo(index, nuovo);
        emit(updateNomeCapitolo());
        close();
    }
    else
    {
        if(titoloEdit->text().isEmpty())
        {
            titoloLabel->setText("Campo obbligatorio");
            titoloLabel->show();
        }
        if(testoEdit->toPlainText().isEmpty())
        {
            testoLabel->setText("Campo obbligatorio");
            testoLabel->show();
        }
    }
}

void CapitoloWidget::hide()
{
    if(!titoloLabel->isHidden()) titoloLabel->hide();
    if(!testoLabel->isHidden()) testoLabel->hide();
}
