#ifndef BOOKWIDGET_H
#define BOOKWIDGET_H

#include "librowidget.h"
#include "viewbookwidget.h"

class BookWidget : public LibroWidget
{
    Q_OBJECT

public:
    explicit BookWidget(Book*, Client*, QWidget *parent = 0);
    explicit BookWidget(Client*, QWidget *parent = 0);
    ~BookWidget();

private:
    // campi dati logici
    Book* libro;

    // campi dati grafici per la visualizzazione dei dati
    QLabel* fileLibro;

    QListWidget* curatoriList;

    // campi dati grafici per l'inserimento/modfica dei dati
    QLineEdit* numeroPagineEdit;
    QLineEdit* editoreEdit;
    QLineEdit* collanaEdit;
    QLineEdit* curatoreEdit;

    // pulsanti
    QPushButton* addCuratore;
    QPushButton* removeCuratore;

    QPushButton* addLibro;

    //metodi privati
    void initializeBook(); //metodo per l'inizializzazione delle componenti comuni ai due costruttori
    void hide(); //metodo per nascondere i pulsanti normalmente non visibili

signals:
    void updateBook(); //segnale per avvisare il widget listaLibri che è stato inserito un nuovo book

public slots:
    void salvaSlot(); // procedura per il salvataggio di un nuovo book nel database
    void aggiornaSlot(); // procedura per l'update dei dati di un book nel database
    void getCuratoreSlot(); // procedura per il selezionamento di un item dalla lista curatori e visualizzazione del pulsante di rimozione
    void aggiungiCuratoreSlot(); // procedura per l'inserimento di una nuova voce nella lista curatori
    void rimuoviCuratoreSlot(); // procedura per la rimozione di una nuova voce dalla lista curatori
    void apriFile(); // procedura per il selezionamento di un file pdf dai file presenti nella macchina
};

#endif // BOOKWIDGET_H
