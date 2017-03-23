#ifndef LISTALIBRIWIDGET_H
#define LISTALIBRIWIDGET_H

#include "listawidget.h"    //classe base
#include "lightnovelwidget.h"   //widget per la modifica e creazione di una light novel (da esso viene importata la visualizzazione di una light novel)
#include "bookwidget.h"         //widget per la modifica e creazione di un book (da esso viene importata la visualizzazione di un book)

#include <QComboBox>
#include <QStringList>

class ListaLibriWidget: public ListaWidget
{
    Q_OBJECT

public:
    explicit ListaLibriWidget(Client*, QString, bool, QWidget *parent = 0);

private:
    QList<Libro*> list; //lista di puntatori polimorfi agli elementi della lista
    QString type; //campo che identifica se stiamo operando su un book o una light novel
    bool admin; //campo booleano per capire se stiamo creando il widget per un amministratore o per un utente
    QFont bold; //campo utilizzato per identificare se il campo della lista è un valore o una label per il sort

    QComboBox *comboBox; //menu a tendina per ordinare la lista
    QHBoxLayout* sort; //layout per la visualizzazione della label e del menu a tendina del sort

    //pulsanti per effettuare
    QPushButton* visualizza;
    QPushButton* modifica;
    QPushButton* rimuovi;
    QPushButton* aggiungi;

signals:
    void updatePreferiti(); //signal per avvisare il client di aggiornare la lista dei preferiti

public slots:
    void getSlot(); //metodo per selezionare un elemento della lista
    void updateSlot(); //metodo per aggiornare le voci della lista
    void visualizzaSlot(); //metodo per visualizzare l'elemento selezionato
    void rimuoviSlot(); //metodo per rimuovere l'elemento selezionato
    void aggiungiSlot(); //metodo per aggiungere una nuova voce alla lista
    void aggiungiPreferitoSlot(); //metodo per aggiungere l'elemento selezionato ai preferiti
    void modificaSlot(); //metodo per modificare l'elemento selezionato
    void hideSlot(); //metodo per nascondere i widget normalmente nascosti
    void sortBySlot(int); //metodo per aggiornare la lista in base ad un campo identificato dal valore passato come int
};

#endif // LISTALIBRIWIDGET_H
