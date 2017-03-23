#ifndef LIBROWIDGET_H
#define LIBROWIDGET_H

#include "Controller/client.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>
#include <QScrollArea>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>

class LibroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LibroWidget(Libro*, Client*, QWidget *parent = 0); //coostruttore per la modifica di un libro
    explicit LibroWidget(Client*, QWidget *parent = 0); //costruttore per la creazione di un nuovo libro

protected:
    // campi dati logici
    Client* logic;
    Libro* lib;

    // campi dati grafici
    QVBoxLayout* mainLayout;
    QHBoxLayout* centralLayout;
    QGroupBox* visualizzaBox;

    QVBoxLayout* dataLayout; //layout che contiene i tre QFormLayout
    QFormLayout* rowLayout;
    QFormLayout* listLayout;
    QFormLayout* othersLayout;

    QLabel* titoloSchedaLabel;

    // campi dati grafici per la visualizzazione dei dati
    QLabel* titoloLabel;
    QLabel* fileImmagine;
    QLabel* immagineLabel;

    QListWidget* autoriList;
    QListWidget* generiList;

    QListWidgetItem* element;

    // campi dati grafici per l'inserimento/modfica dei dati
    QLineEdit* titoloEdit;
    QDateEdit* dataPubblicazioneEdit;
    QLineEdit* linguaEdit;
    QLineEdit* descrizioneEdit;
    QLineEdit* autoreEdit;
    QLineEdit* genereEdit;

    // pulsanti
    QPushButton* addAutore;
    QPushButton* removeAutore;
    QPushButton* addGenere;
    QPushButton* removeGenere;

    QPushButton* addImmagine;

    QPushButton* annulla;
    QPushButton* salva;

    void initializeLibro(); //metodo per l'inizializzazione delle componenti comuni ai due costruttori
    virtual void hide();

public slots:
    virtual void salvaSlot() =0; // procedura per il salvataggio di un nuovo book nel database
    virtual void aggiornaSlot() =0; // procedura per l'update dei dati di un book nel database
    void getAutoreSlot(); // procedura per il selezionamento di un item dalla lista autori e visualizzazione del pulsante di rimozione
    void getGenereSlot(); // procedura per il selezionamento di un item dalla lista generi e visualizzazione del pulsante di rimozione
    void aggiungiAutoreSlot(); // procedura per l'inserimento di una nuova voce nella lista autori
    void rimuoviAutoreSlot(); // procedura per la rimozione di una nuova voce dalla lista autori
    void aggiungiGenereSlot(); // procedura per l'inserimento di una nuova voce nella lista generi
    void rimuoviGenereSlot(); // procedura per la rimozione di una nuova voce dalla lista generi
    void apriImmagine(); // procedura per il selezionamento di un file immagine (.jpg o .png) dai file presenti nella macchina
};

#endif // LIBROWIDGET_H
