#ifndef RICERCAAVANZATAWIDGET_H
#define RICERCAAVANZATAWIDGET_H

#include "listarisultatiricercawidget.h"

class RicercaAvanzataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RicercaAvanzataWidget(Client*, QWidget* parent=0);

private:
    QGroupBox* initialBox;
    QVBoxLayout* layout;
    QFormLayout* inputForm;

    Client* logic;

    QLabel* titoloWidget;

    QLineEdit* titoloEdit;
    QLineEdit* linguaEdit;
    QLineEdit* editoreEdit;
    QLineEdit* collanaEdit;
    QLineEdit* autoreEdit;
    QLineEdit* genereEdit;
    QLineEdit* curatoreEdit;
    QLineEdit* traduttoreEdit;
    QLineEdit* lingua_originaleEdit;

    // pulsanti
    QRadioButton* completatoTrue;
    QRadioButton* completatoFalse;

    QPushButton* cerca;
    QPushButton* reset;

    void initializeCommonView(); //metodo per l'inizializzazione dei campi in comune tra le tre possibilità

public slots:
    void libroViewSlot(); //permette di creare un widget per la ricerca di un libro
    void bookViewSlot(); //permette di creare un widget per la ricerca di un book
    void lightNovelViewSlot(); //permette di creare un widget per la ricerca di una light novel
    void cercaLibroSlot(); //metodo per utilizzare i dati forniti per cercare un libro
    void cercaBookSlot(); //metodo per utilizzare i dati forniti per cercare un book
    void cercaLightNovelSlot(); //metodo per utilizzare i dati forniti per cercare una light novel
    void resetLibroSlot(); //metodo per resettare i campi di ricerca di un libro
    void resetBookSlot(); //metodo per resettare i campi di ricerca di un book
    void resetLightNovelSlot(); //metodo per resettare i campi di ricerca di una light novel
};

#endif // RICERCAAVANZATAWIDGET_H
