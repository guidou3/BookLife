#include "listawidget.h"

ListaWidget::ListaWidget(Client* c, QString title, QWidget *parent) : QWidget(parent)
{
    logic = c;

    listaBox = new QGroupBox;
    listaBox->setMinimumWidth(200);
    listaBox->setTitle(title);
    QFont font = QFont("arial", 10);
    listaBox->setFont(font);

    lista = new QListWidget;
    lista->setMinimumWidth(150);
    lista->setMinimumHeight(150);

    layout = new QHBoxLayout;
    mainLayout = new QVBoxLayout;

    connect(lista,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(getSlot()));

    mainLayout->addWidget(lista);
    listaBox->setLayout(mainLayout);
    layout->addWidget(listaBox);
    setLayout(layout);
}
