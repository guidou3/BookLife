#ifndef VIEWBOOKWIDGET_H
#define VIEWBOOKWIDGET_H

#include "viewlibrowidget.h"
#include "Model/book.h"

class ViewBookWidget : public ViewLibroWidget
{
    Q_OBJECT

public:
    explicit ViewBookWidget(Book*, QWidget *parent = 0);

private:
    Book* libro;

    // campi dati logici
    QLabel* numeroPagineLabel;
    QListWidget* curatoriList;
    QLabel* editoreLabel;
    QLabel* collanaLabel;
    QLabel* fileLibro;

    // pulsanti
    QPushButton* linkToPdf;

public slots:
    void visualizzaPdfSlot(); // procedura per la visualizzazione del file pdf mediante software della macchina
};

#endif // VIEWBOOKWIDGET_H
