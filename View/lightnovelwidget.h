#ifndef LIGHTNOVELWIDGET_H
#define LIGHTNOVELWIDGET_H

#include "viewlightnovelwidget.h"
#include "librowidget.h"

#include <QRadioButton>

class LightNovelWidget : public LibroWidget
{
    Q_OBJECT

public:
    explicit LightNovelWidget(Client*, Light_novel*, QWidget *parent = 0);
    explicit LightNovelWidget(Client*, QWidget *parent = 0);
    ~LightNovelWidget();

private:
    // campi dati logici
    Light_novel* lightNovel;

    // campi grafici di visualizzazione
    QListWidget* traduttoriList;

    // campi grafici per l'inserimento/modifica dei dati 
    QLineEdit* capitoli_tradottiEdit;
    QLineEdit* capitoli_scrittiEdit;
    QLineEdit* lingua_originaleEdit;
    QLineEdit* traduttoreEdit;

    // pulsanti

    //radio buttons per esprimere il valore "completato"
    QRadioButton* completatoTrue;
    QRadioButton* completatoFalse;

    QPushButton* addTraduttore;
    QPushButton* removeTraduttore;

    // metodi di classe privati
    void initializeLightNovel(); //metodo per l'inizializzazione delle componenti comuni ai due costruttori
    void hide(); // metodo per nascondere i widget che normalmente non dovrebbero essere visibili

signals:
    void updateLightNovel(); //segnale per avvisare il widget listaLibri che è stato inserita una nuova light novel

public slots:
    void salvaSlot(); // procedura per il salvataggio di una nuova light novel nel database
    void aggiornaSlot(); // procedura per l'update dei dati di una light novel nel database
    void getTraduttoreSlot(); // procedura per il selezionamento di un item dalla lista traduttori e visualizzazione del pulsante di rimozione
    void aggiungiTraduttoreSlot(); // procedura per l'inserimento di una nuova voce nella lista traduttori
    void rimuoviTraduttoreSlot(); // procedura per la rimozione di una nuova voce dalla lista traduttori
};

#endif // LIGHTNOVELWIDGET_H
