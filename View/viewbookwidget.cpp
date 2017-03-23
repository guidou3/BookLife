#include "viewbookwidget.h"

ViewBookWidget::ViewBookWidget(Book* b, QWidget *parent) : ViewLibroWidget(b, parent), libro(b)
{
    numeroPagineLabel = new QLabel;
    editoreLabel = new QLabel;
    collanaLabel = new QLabel;

    curatoriList = new QListWidget;

    numeroPagineLabel->setText(QString::number(libro->getNumeroPagine()));
    editoreLabel->setText(libro->getEditore());
    collanaLabel->setText(libro->getCollana());

    curatoriList->addItems(libro->getCuratori());
    curatoriList->setMaximumHeight(100);

    rowLayout->addRow("Numero pagine: ", numeroPagineLabel);
    rowLayout->addRow("Editore: ", editoreLabel);
    rowLayout->addRow("Collana: ", collanaLabel);
    listLayout->addRow("Curatori: ", curatoriList);

    if(!libro->getLibro().isEmpty())
    {
        linkToPdf = new QPushButton;
        linkToPdf->setText("Leggi");
        linkToPdf->setMinimumHeight(50);
        linkToPdf->setMinimumWidth(100);
        connect(linkToPdf,SIGNAL(clicked()),this,SLOT(visualizzaPdfSlot()));
        parallelLayout->addWidget(linkToPdf);
    }
}

void ViewBookWidget::visualizzaPdfSlot()
{
    QDesktopServices::openUrl(QUrl::fromLocalFile(libro->getLibro()));
}
