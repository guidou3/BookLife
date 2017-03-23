#include "signupwidget.h"

SignUpWidget::SignUpWidget(Database * d, QWidget *parent) : QWidget(parent)
{
    db = d;
    SignUpLayout = new QVBoxLayout;
    QLabel* istruzioni = new QLabel;
    SignUpBox = new QGroupBox;
    usernameEdit = new QLineEdit;
    passwordEdit = new QLineEdit;
    QLabel* scelta = new QLabel;
    QPushButton* basic = new QPushButton;
    QPushButton* scrittore = new QPushButton;
    QPushButton* amministratore = new QPushButton;
    QPushButton* indietro = new QPushButton;
    message = new QLabel;

    SignUpBox->setTitle("Iscrizione a Book Life");
    istruzioni->setText("Inserisci i tuoi dati\n(I campi contrassegnati da * sono obbligatori)");
    QVBoxLayout* vlayout = new QVBoxLayout;
    QFormLayout* flayout = new QFormLayout;
    flayout->addRow("Username: * ",usernameEdit);
    flayout->addRow("Password: * ",passwordEdit);
    scelta->setText("Scegli la tipologia di profilo");
    scelta->setAlignment(Qt::AlignCenter);
    basic->setText("Basic");
    scrittore->setText("Scrittore");
    amministratore->setText("Amministratore");
    indietro->setText("Annulla");
    message->setText("");
    message->setAlignment(Qt::AlignCenter);

    connect(basic,SIGNAL(clicked()),this,SLOT(creaUtente()));
    connect(scrittore,SIGNAL(clicked()),this,SLOT(creaScrittore()));
    connect(amministratore,SIGNAL(clicked()),this,SLOT(creaAmministratore()));
    connect(indietro,SIGNAL(clicked()),this,SIGNAL(indietro()));

    QHBoxLayout* hlayout = new QHBoxLayout;
    hlayout->addWidget(basic);
    hlayout->addWidget(scrittore);
    hlayout->addWidget(amministratore);
    vlayout->addWidget(istruzioni);
    vlayout->addSpacing(15);
    vlayout->addLayout(flayout);
    vlayout->addSpacing(10);
    vlayout->addWidget(scelta);
    vlayout->addLayout(hlayout);
    vlayout->addWidget(message);
    vlayout->addSpacing(5);
    message->hide();
    vlayout->addWidget(indietro);
    SignUpBox->setLayout(vlayout);
    SignUpLayout->addWidget(SignUpBox);
    SignUpLayout->setAlignment(SignUpBox,Qt::AlignCenter);
    setLayout(SignUpLayout);
}

void SignUpWidget::creaUtente()
{
    if(!(usernameEdit->text().isEmpty() || passwordEdit->text().isEmpty()))
    {
        Utente* u = new Utente(usernameEdit->text(), passwordEdit->text());
        if(db->addUtente(u))
        {
            indietro();
        }
        else
        {
            delete u;
            message->setText("Attenzione:\nUsername gia' in uso");
            message->show();
        }
    }
    else
    {
        message->setText("Attenzione:\nAlcuni campi obbligatori sono incompleti");
        message->show();
    }
}

void SignUpWidget::creaScrittore()
{
    if(!(usernameEdit->text().isEmpty() || passwordEdit->text().isEmpty()))
    {
        Scrittore* u = new Scrittore(usernameEdit->text(), passwordEdit->text());
        if(db->addUtente(u))
        {
            indietro();
        }
        else
        {
            delete u;
            message->setText("Attenzione:\nUsername gia' in uso");
            message->show();
        }
    }
    else
    {
        message->setText("Attenzione:\nAlcuni campi obbligatori sono incompleti");
        message->show();
    }
}

void SignUpWidget::creaAmministratore()
{
    if(!(usernameEdit->text().isEmpty() || passwordEdit->text().isEmpty()))
    {
        Amministratore* u = new Amministratore(usernameEdit->text(), passwordEdit->text());
        if(db->addUtente(u))
        {
            indietro();
        }
        else
        {
            delete u;
            message->setText("Attenzione:\nUsername gia' in uso");
            message->show();
        }
    }
    else
    {
        message->setText("Attenzione:\nAlcuni campi obbligatori sono incompleti");
        message->show();
    }
}

SignUpWidget::~SignUpWidget()
{

}
