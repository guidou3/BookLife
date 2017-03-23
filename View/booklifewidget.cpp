#include "booklifewidget.h"

#include<iostream>
using namespace std;

BookLifeWidget::BookLifeWidget(QWidget *parent) : QWidget(parent)
{
    db = new Database;

    setWindowTitle("BookLife");

    mainLayout = new QVBoxLayout;
    mainBox = new QGroupBox;
    QVBoxLayout* boxLayout = new QVBoxLayout;

    QFont f( "Arial", 12);
    QLabel* welcomeLabel = new QLabel;

    welcomeLabel->setText("Benvenuti su BookLife!\n");
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setFont(f);

    messaggio = new QLabel;
    messaggio->setText("");
    messaggio->hide();

    QLabel* usernameLabel = new QLabel;
    usernameEdit = new QLineEdit;
    QLabel* passwordLabel = new QLabel;
    passwordEdit = new QLineEdit;
    QPushButton* loginButton = new QPushButton;
    QPushButton* signUpButton = new QPushButton;
    QLabel* signUpLabel = new QLabel;
    QPushButton* exitButton = new QPushButton;
    exitButton->setText("ESCI");
    exitButton->setMaximumWidth(200);

    usernameLabel->setText("Username:");
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameEdit->setMaximumWidth(100);
    passwordLabel->setText("Password");
    passwordLabel->setAlignment(Qt::AlignCenter);
    passwordEdit->setMaximumWidth(100);

    loginButton->setText("Login");
    signUpButton->setText("Registrati!");
    signUpLabel->setText("Non sei ancora registrato?");
    signUpLabel->setAlignment(Qt::AlignCenter);

    connect(loginButton,SIGNAL(clicked()),this,SLOT(effettuaLogin()));
    connect(signUpButton,SIGNAL(clicked()),this,SLOT(signupSlot()));
    connect(exitButton,SIGNAL(clicked()),this,SLOT(close()));

    QGroupBox* credentialBox = new QGroupBox;
    QHBoxLayout* layout1 = new QHBoxLayout;
    QHBoxLayout* layout2 = new QHBoxLayout;

    layout1->addWidget(usernameLabel);
    layout1->addWidget(usernameEdit);
    layout2->addWidget(passwordLabel);
    layout2->addWidget(passwordEdit);


    QVBoxLayout* box = new QVBoxLayout;
    box->addLayout(layout1);
    box->addLayout(layout2);
    credentialBox->setLayout(box);

    boxLayout->addWidget(welcomeLabel);
    boxLayout->addWidget(credentialBox);
    boxLayout->addWidget(loginButton);
    boxLayout->setAlignment(loginButton,Qt::AlignCenter);
    boxLayout->addSpacing(5);
    boxLayout->addWidget(messaggio);
    boxLayout->setAlignment(messaggio,Qt::AlignCenter);
    boxLayout->addSpacing(5);
    boxLayout->addWidget(signUpLabel);
    boxLayout->addWidget(signUpButton);
    boxLayout->setAlignment(signUpButton,Qt::AlignCenter);
    boxLayout->addSpacing(10);
    boxLayout->addWidget(exitButton);
    boxLayout->setAlignment(exitButton,Qt::AlignCenter);
    mainBox->setLayout(boxLayout);
    mainLayout->addWidget(mainBox);
    mainLayout->setAlignment(mainBox,Qt::AlignCenter);

    setLayout(mainLayout);
}

BookLifeWidget::~BookLifeWidget()
{
    delete db;
}

void BookLifeWidget::effettuaLogin()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    if(!(username.isEmpty() || password.isEmpty()))
    {
        session = new Session(username, password, db);
        if(session->isValid())
        {
            usernameEdit->setText("");
            passwordEdit->setText("");
            messaggio->setText("");
            messaggio->hide();
            switch(session->getAccountType())
            {
            case 0:
                client = new UserClientWidget(session, this);
                break;
            case 1:
                client = new WriterClientWidget(session, this);
                connect(client,SIGNAL(normalAccount()),this,SLOT(sessioneScrittoreTerminata()));
                break;
            case 2:
                client = new AdminClientWidget(session, this);
                break;
            }
            connect(client,SIGNAL(logoutSignal()),this,SLOT(sessioneTerminata()));
            mainBox->hide();
            mainLayout->addWidget(client);
        }
        else {
            messaggio->show();
            messaggio->setText("Credenziali errate!");
        }

    }
    else {
        messaggio->show();
        messaggio->setText("Username e/o password mancanti!");
    }
}

void BookLifeWidget::sessioneTerminata()
{
    delete client;
    client =0;
    mainBox->show();
}

void BookLifeWidget::sessioneScrittoreTerminata()
{
    delete client;
    client = new UserClientWidget(session, this);
    connect(client,SIGNAL(logoutSignal()),this,SLOT(sessioneTerminata()));
    mainLayout->addWidget(client);
}

void BookLifeWidget::signupSlot()
{
    signup = new SignUpWidget(db, this);
    connect(signup,SIGNAL(indietro()),this,SLOT(annullaSignUp()));
    messaggio->hide();
    mainBox->hide();
    usernameEdit->setText("");
    passwordEdit->setText("");
    mainLayout->addWidget(signup);
}

void BookLifeWidget::annullaSignUp()
{
    delete signup;
    mainBox->show();
}
