#include "userclientwidget.h"

UserClientWidget::UserClientWidget(Session* s, QWidget *parent) : ClientWidget(s, parent)
{
    tipoClient->setText("USER CLIENT");
    logic->setTipoClient(0);

    book = new ListaLibriWidget(logic, "Book", false, this);
    ln = new ListaLibriWidget(logic, "Light novel", false, this);
    preferiti = new ListaPreferitiWidget(logic, this);

    CentralLayout->addWidget(book);
    CentralLayout->addWidget(ln);
    CentralLayout->addWidget(preferiti);

    connect(book,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(ln,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(preferiti,SIGNAL(selected()),this,SLOT(hideSlot()));
    connect(book,SIGNAL(updatePreferiti()),preferiti,SLOT(updateSlot()));
    connect(ln,SIGNAL(updatePreferiti()),preferiti,SLOT(updateSlot()));
}

UserClientWidget::~UserClientWidget() {}

void UserClientWidget::hideSlot()
{
    book->hideSlot();
    ln->hideSlot();
    preferiti->hideSlot();
}
