#include "writerclientwidget.h"

WriterClientWidget::WriterClientWidget(Session* s, QWidget *parent) : ClientWidget(s, parent)
{
    tipoClient->setText("WRITER CLIENT");
    logic->setTipoClient(1);

    ricerca->hide();

    lavori = new ListaLavoriWidget(logic, this);

    CentralLayout->addWidget(lavori);

    connect(lavori,SIGNAL(selected()),this,SLOT(hideSlot()));

    normalAccountButton  = new QPushButton;
    normalAccountButton->setText("ACCOUNT STANDARD");
    normalAccountButton->setMinimumWidth(200);
    normalAccountButton->setMinimumHeight(30);

    QPushButton* check = new QPushButton("Aggiorna lista lavori");
    check->setMinimumWidth(200);
    check->setMinimumHeight(30);

    connect(normalAccountButton,SIGNAL(clicked()),this,SIGNAL(normalAccount()));
    connect(check,SIGNAL(clicked()),this,SLOT(checkSlot()));

    buttons->addWidget(normalAccountButton, 0, Qt::AlignHCenter);
    buttons->addWidget(check, 0, Qt::AlignHCenter);
}

WriterClientWidget::~WriterClientWidget() {}

void WriterClientWidget::checkSlot()
{
    logic->updateListaLavori();
    dynamic_cast<ListaLavoriWidget*>(lavori)->updateSlot();
}

void WriterClientWidget::hideSlot()
{
    lavori->hideSlot();
}
