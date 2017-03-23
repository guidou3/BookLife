#include "ricercawidget.h"

RicercaWidget::RicercaWidget(Client* c, QWidget *parent) : QWidget(parent)
{
    logic = c;

    ricercaBox = new QGroupBox;
    ricerca = new QLineEdit;

    ricerca->setMinimumWidth(200);

    cerca = new QPushButton;
    cerca->setText("Cerca");
    cerca->setMaximumWidth(200);

    ricercaAvanzata = new QPushButton;
    ricercaAvanzata->setText("Ricerca avanzata");
    ricercaAvanzata->setMaximumWidth(200);

    connect(cerca,SIGNAL(clicked()),this,SLOT(cercaSlot()));
    connect(ricercaAvanzata,SIGNAL(clicked()),this,SLOT(ricercaAvanzataSlot()));

    QHBoxLayout* layout = new QHBoxLayout;

    layout->addWidget(ricerca);
    layout->addWidget(cerca);
    layout->addWidget(ricercaAvanzata);

    ricercaMessageLabel = new QLabel;
    ricercaMessageLabel->setText("");
    ricercaMessageLabel->hide();
    ricercaMessageLabel->setAlignment(Qt::AlignCenter);

    ricercaLayout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    presentazione = new QLabel;
    presentazione->setText("Ricerca all'interno di BookLife!");
    QFont font = QFont("arial", 12);
    presentazione->setFont(font);

    ricercaMessageLabel = new QLabel;
    ricercaMessageLabel->setText("");
    ricercaMessageLabel->setAlignment(Qt::AlignCenter);

    ricercaLayout->addWidget(ricerca);
    ricercaLayout->addWidget(cerca);
    ricercaLayout->addWidget(ricercaAvanzata);

    mainLayout->addWidget(presentazione);
    mainLayout->addLayout(ricercaLayout);
    mainLayout->addWidget(ricercaMessageLabel);

    setLayout(mainLayout);
}

void RicercaWidget::cercaSlot()
{
    emit(selected());
    QString x = ricerca->text();
    if(x.isEmpty())
    {
        ricercaMessageLabel->setText("Impossibile effettuare la ricerca: campo di ricerca vuoto");
        ricercaMessageLabel->show();
    }
    else
    {
        QStringList temp = logic->findAll(x);
        if(temp.isEmpty())
        {
            ricercaMessageLabel->setText("Non è stato trovato alcun libro che soddisfa tali parametri");
            ricercaMessageLabel->show();
        }
        else
        {
            ricercaMessageLabel->hide();
            ListaRisultatiRicercaWidget* esiti = new ListaRisultatiRicercaWidget(logic, logic->findAll(x));
            esiti->show();
            // apri un widget per la visualizzazione dei risultati della ricerca

        }
    }
}

void RicercaWidget::ricercaAvanzataSlot()
{
    emit(selected());
    ricercaMessageLabel->hide();
    RicercaAvanzataWidget* temp = new RicercaAvanzataWidget(logic);
    temp->show();
}
