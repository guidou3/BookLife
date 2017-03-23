#ifndef CATALOGO_H
#define CATALOGO_H

#include "Model/book.h"
#include "Model/light_novel.h"
#include "Model/amministratore.h"
#include "Model/scrittore.h"
#include "Model/dblist.h"

#include <typeinfo>
#include <QFile>
#include <QTextStream>

//database contenente tutti i libri

class Database
{
public:
    Database();
    ~Database();

    QList<Book*> books; // contenitore contenente i book
    QList<Light_novel*> lightNovels; // contenitore contenente le light novel
    dbList<Utente*> utenti; // contenitore contenente gli utenti

    void load(); // metodo per caricare da un file le informazioni del db
    void save(); // metodo per salvare in un file le informazioni del db

    Utente* findUtente(QString) const; // metodo per cercare e restituire un utente dato il suo username
    Book* findBook(QString) const; // metodo per cercare e restituire un book dato il suo titolo
    Light_novel* findLightNovel(QString) const; // metodo per cercare e restituire una light novel dato il suo titolo

    QStringList findAll(QString) const; //metodo per cercare tutti i libri che posseggono in qualche attributo la stringa fornita
    QStringList findLibro(QString, QString, QString, QString) const; //metodo per cercare tutti i libri che contengono i valori forniti nei loro attributi corrispondenti
    QStringList findBook(QString, QString, QString, QString, QString, QString, QString) const; //stesso scopo del precedente metodo, solo che applicato ai Book
    QStringList findLightNovel(QString, QString, QString, QString, QString, QString, bool) const; //stesso scopo del precedente metodo, solo che applicato alle Light_novel

    QStringList listaUtenti() const; // metodo per restituire la lista degli username degli utenti presenti nel database
    QList<Book*> listaBooks() const; // metodo per restituire la lista dei titoli dei book presenti nel database
    QList<Light_novel*> listaLightNovels() const; // metodo per restituire la lista dei titoli delle light novel presenti nel database

    // i nomi dei metodi mi sembrano auto-esplicativi
    bool addBook(Book*);
    void removeBook(Book*);
    bool updateBook(Book*);

    bool addLightNovel(Light_novel*);
    void removeLightNovel(Light_novel*);
    bool updateLightNovel(Light_novel*);

    bool addUtente(Utente*);
    void removeUtente(Utente*);
};

#endif // CATALOGO_H
