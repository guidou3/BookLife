#ifndef CLIENT_H
#define CLIENT_H

#include "Model/session.h"
#include "Model/amministratore.h"

class Client
{
private:
    Session* current; // sessione corrente
    Utente* utenteSelezionato;
    Libro* libroSelezionato;
    int tipoClient;

public:
    Client(Session*);

    Libro* getLibroSelezionato() const;
    Utente* getUtenteSelezionato() const;
    void resetSelezionati();
    Session* getSession() const;

    bool libroExists() const;
    bool utenteExists() const;

    void setTipoClient(int);
    int getTipoClient() const;

    QStringList getListaUtenti() const; // metodo per ottenere la lista degli utenti
    QStringList getListaPreferiti() const;
    QList<Book*> getListaBook() const; // metodo per ottenere la lista dei book
    QList<Light_novel*> getListaLightNovel() const; // metodo per ottenere la lista delle light novel
    QList<Libro*> getListaBookStandard() const;
    QList<Libro*> getListaLightNovelStandard() const;
    QStringList getLavori(); // metodo con due compiti: come primo verificare la presenza dei lavori dello scrittore e aggiornare la lista nel database, come secondo riportare la lista aggiornata

    void updateListaLavori();

    void rimuoviUtente(); // metodo per la rimozione di utenteSelezionato dal database
    void rimuoviLibro(); // metodo per la rimozione di libroSelezionato dal database
    bool addPreferito(); // metodo per l'inserimento del libro selezionato tra i preferiti dell'utente
    void removePreferito(); // metodo per la rimozione del preferito selezionato dai preferiti dell'utente
    void removePreferito(QString); // metodo per la rimozione di un preferito mediante il suo titolo
    void findUtente(QString); // metodo per cercare un utente mediante l'username all'interno del database e l'inserimento del valore ottenuto in utenteSelezionato
    bool findPreferito(QString);
    void findBook(QString); // metodo per cercare un book mediante il titolo all'interno del database e l'inserimento del valore ottenuto in libroSelezionato
    void findLightNovel(QString); // metodo per cercare una light novel mediante il titolo all'interno del database e l'inserimento del valore ottenuto in libroSelezionato

    QStringList findAll(QString) const;
    QStringList findLibro(QString, QString, QString, QString) const;
    QStringList findBook(QString, QString, QString, QString, QString, QString, QString) const;
    QStringList findLightNovel(QString, QString, QString, QString, QString, QString, bool) const;

    bool addBook(Book*);
    bool updateBook(Book*);
    bool addLightNovel(Light_novel*);
    bool updateLightNovel(Light_novel*);
};

#endif // CLIENT_H
