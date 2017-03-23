#include "clientwidget.h"

ClientWidget::ClientWidget(Session* s, QWidget *parent) : QWidget(parent)
{
    logic = new Client(s);

    layout = new QVBoxLayout;
    CentralLayout = new QHBoxLayout;
    buttons = new QHBoxLayout;

    ricerca = new RicercaWidget(logic, this);

    tipoClient = new QLabel;
    QFont font = QFont("arial", 15, QFont::Bold);
    tipoClient->setFont(font);

    logoutButton = new QPushButton;
    logoutButton->setText("LOGOUT");
    logoutButton->setMinimumWidth(200);
    logoutButton->setMinimumHeight(30);

    buttons->addWidget(logoutButton);
    buttons->setAlignment(logoutButton, Qt::AlignCenter);

    connect(ricerca,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(logoutButton,SIGNAL(clicked()),this,SIGNAL(logoutSignal()));

    layout->addWidget(tipoClient, 0, Qt::AlignHCenter);
    layout->addWidget(ricerca);
    layout->addLayout(CentralLayout);
    layout->setSpacing(20);
    layout->addLayout(buttons);
    setLayout(layout);
}

ClientWidget::~ClientWidget()
{
    delete logic;
}
