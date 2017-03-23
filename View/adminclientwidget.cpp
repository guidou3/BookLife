#include "adminclientwidget.h"

AdminClientWidget::~AdminClientWidget()
{
}

AdminClientWidget::AdminClientWidget(Session* s, QWidget *parent) : ClientWidget(s, parent)
{
    tipoClient->setText("ADMIN CLIENT");
    logic->setTipoClient(2);

    book = new ListaLibriWidget(logic, "Book", true, this);
    ln = new ListaLibriWidget(logic, "Light novel", true, this);
    utenti = new ListaUtentiWidget(logic, this);

    CentralLayout->addWidget(book);
    CentralLayout->addWidget(ln);
    CentralLayout->addWidget(utenti);

    connect(book,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(ln,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(utenti,SIGNAL(selected()),this,SLOT(hideSlot()));
}

void AdminClientWidget::hideSlot()
{
    book->hideSlot();
    ln->hideSlot();
    utenti->hideSlot();
}
