#include "database.h"
#include <iostream>
using namespace std;

Database::Database()
{
    load();
}

Database::~Database()
{
    save();
    for(int i=0; i<books.size(); ++i)
    {
        delete books.at(i);
    }
    for(int i=0; i<lightNovels.size(); ++i)
    {
        delete lightNovels.at(i);
    }
    for(int i=0; i<utenti.size(); ++i)
    {
        delete utenti.at(i);
    }

}

void Database::load()
{
    QFile fileDatabase;
    fileDatabase.setFileName("database.txt");
    fileDatabase.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&fileDatabase);
    QString x;
    {
        x = stream.readLine();
        while(!stream.atEnd())
        {
            if(x=="Begin utente")
            {
                //------------------------------ creazione nuovo utente e rilevazione tipologia account
                x = stream.readLine(); // tipologia dell'account
                QString username = stream.readLine();
                QString password = stream.readLine();

                Utente* u;
                if(x=="basic")
                {
                    u = new Utente(username, password);
                }
                else if(x=="scrittore")
                {
                    u = new Scrittore(username, password);
                }
                else if(x=="admin")
                {
                    u = new Amministratore(username, password);
                }
                else
                {
                    cerr << "Tipologia d'utente non corretta" << endl;
                }

                addUtente(u);

                //------------------------------ inserimento informazioni personali

                x = stream.readLine();
                if(x=="preferiti")
                {
                    x = stream.readLine();
                    while(x != "end_preferiti")
                    {
                        u->addPreferito(x);
                        x = stream.readLine();
                    }
                    x = stream.readLine();
                }
                if(x=="lavori")
                {
                    x = stream.readLine();
                    Scrittore* s = dynamic_cast<Scrittore*>(u);
                    while(x != "end_lavori")
                    {
                        s->addLavoro(x);
                        x = stream.readLine();
                    }
                    x = stream.readLine();
                }
                if(x=="end") x = stream.readLine();
            }
            else if(x=="Begin book")
            {
                //------------------------------ creazione nuovo book
                x = stream.readLine(); // titolo del libro

                Book* b = new Book(x);

                addBook(b);

                //------------------------------ inserimento informazioni personali

                x = stream.readLine();
                if(x=="autori")
                {
                    x = stream.readLine();
                    QList<QString> autori;
                    while(x != "end_autori")
                    {
                        autori.append(x);
                        x = stream.readLine();
                    }
                    b->setAutori(autori);
                    x = stream.readLine();
                }
                if(x=="data di pubblicazione")
                {
                    int y = stream.readLine().toInt();
                    int m = stream.readLine().toInt();
                    int d = stream.readLine().toInt();
                    b->setDataPubblicazione(QDate(y, m, d));
                    x = stream.readLine();
                }
                if(x=="lingua")
                {
                    x = stream.readLine();
                    b->setLingua(x);
                    x = stream.readLine();
                }
                if(x=="generi")
                {
                    x = stream.readLine();
                    QList<QString> generi;
                    while(x != "end_generi")
                    {
                        generi.append(x);
                        x = stream.readLine();
                    }
                    b->setGeneri(generi);
                    x = stream.readLine();
                }
                if(x=="descrizione")
                {
                    x = stream.readLine();
                    b->setDescrizione(x);
                    x = stream.readLine();
                }
                if(x=="immagine")
                {
                    x = stream.readLine();
                    b->setImmagine(x);
                    x = stream.readLine();
                }
                if(x=="numero pagine")
                {
                    x = stream.readLine();
                    b->setNumeroPagine(x.toInt());
                    x = stream.readLine();
                }
                if(x=="curatori")
                {
                    x = stream.readLine();
                    QList<QString> curatori;
                    while(x != "end_curatori")
                    {
                        curatori.append(x);
                        x = stream.readLine();
                    }
                    b->setCuratori(curatori);
                    x = stream.readLine();
                }
                if(x=="editore")
                {
                    x = stream.readLine();
                    b->setEditore(x);
                    x = stream.readLine();
                }
                if(x=="collana")
                {
                    x = stream.readLine();
                    b->setCollana(x);
                    x = stream.readLine();
                }
                if(x=="libro")
                {
                    x = stream.readLine();
                    b->setLibro(x);
                    x = stream.readLine();
                }
                if(x=="end") x = stream.readLine();
            }
            else if(x=="Begin light novel")
            {
                //------------------------------ creazione nuovo book
                x = stream.readLine(); // titolo del libro

                Light_novel* b = new Light_novel(x);

                addLightNovel(b);

                //------------------------------ inserimento informazioni personali

                x = stream.readLine();
                if(x=="autori")
                {
                    x = stream.readLine();
                    QList<QString> autori;
                    while(x != "end_autori")
                    {
                        autori.append(x);
                        x = stream.readLine();
                    }
                    b->setAutori(autori);
                    x = stream.readLine();
                }
                if(x=="data di pubblicazione")
                {
                    int y = stream.readLine().toInt();
                    int m = stream.readLine().toInt();
                    int d = stream.readLine().toInt();
                    b->setDataPubblicazione(QDate(y, m, d));
                    x = stream.readLine();
                }
                if(x=="lingua")
                {
                    x = stream.readLine();
                    b->setLingua(x);
                    x = stream.readLine();
                }
                if(x=="generi")
                {
                    x = stream.readLine();
                    QList<QString> generi;
                    while(x != "end_generi")
                    {
                        generi.append(x);
                        x = stream.readLine();
                    }
                    b->setGeneri(generi);
                    x = stream.readLine();
                }
                if(x=="descrizione")
                {
                    x = stream.readLine();
                    b->setDescrizione(x);
                    x = stream.readLine();
                }
                if(x=="immagine")
                {
                    x = stream.readLine();
                    b->setImmagine(x);
                    x = stream.readLine();
                }
                if(x=="capitoli tradotti")
                {
                    x = stream.readLine();
                    b->setCapitoliTradotti(x.toInt());
                    x = stream.readLine();
                }
                if(x=="capitoli scritti")
                {
                    x = stream.readLine();
                    b->setCapitoliScritti(x.toInt());
                    x = stream.readLine();
                }
                if(x=="completato")
                {
                    bool t = stream.readLine().toInt();
                    b->setCompletato(t);
                    x = stream.readLine();
                }
                if(x=="traduttori")
                {
                    x = stream.readLine();
                    QList<QString> traduttori;
                    while(x != "end_traduttori")
                    {
                        traduttori.append(x);
                        x = stream.readLine();
                    }
                    b->setTraduttori(traduttori);
                    x = stream.readLine();
                }
                if(x=="lingua originale")
                {
                    x = stream.readLine();
                    b->setLinguaOriginale(x);
                    x = stream.readLine();
                }
                if(x=="capitoli")
                {
                    x = stream.readLine();
                    while(x != "end_capitoli")
                    {
                        if(x== "titolo")
                        {
                            Capitolo* cap = new Capitolo();
                            x = stream.readLine();
                            cap->setTitolo(x);
                            x = stream.readLine();
                            if(x=="testo")
                            {
                                QString y = "";
                                x = stream.readLine();
                                while(x != "end_testo")
                                {
                                    y += x;
                                    x = stream.readLine();
                                }
                                cap->setTesto(y);
                            }
                            b->addCapitolo(cap);
                        }
                        x = stream.readLine();
                    }
                    x = stream.readLine();
                }
                if(x=="end") x = stream.readLine();
            }
        } // fine ciclo while
    }
}

void Database::save()
{
    QFile fileDatabase;
    fileDatabase.setFileName("database.txt");
    fileDatabase.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text);
    QTextStream stream(&fileDatabase);
    QString temp;
    for(int i=0; i<utenti.size(); ++i)
    {
        Utente* usr = utenti.at(i);
        stream << "Begin utente" << "\n";
        if(usr->tipoAccount() == 0) stream << "basic" << "\n";
        if(usr->tipoAccount() == 1) stream << "scrittore" << "\n";
        if(usr->tipoAccount() == 2) stream << "admin" << "\n";

        stream << usr->getUsername() << "\n";
        stream << usr->getPassword() << "\n";

        QList<QString> preferiti = usr->getPreferiti();
        if(preferiti.size() != 0)
        {
            stream << "preferiti" << "\n";
            for(int i=0; i < preferiti.size(); ++i) stream << preferiti.at(i) << "\n";
            stream << "end_preferiti" << "\n";
        }

        if(usr->tipoAccount() == 2)
        {
            QStringList lavori = dynamic_cast<Scrittore*>(usr)->getLavori();
            if(!lavori.isEmpty())
            {
                stream << "lavori" << "\n";
                for(int i=0; i < lavori.size(); ++i) stream << lavori.at(i) << "\n";
                stream << "end_lavori" << "\n";
            }
        }

        stream << "end" << "\n";
    }

    for(int i=0; i<books.size(); ++i)
    {
        Book* b = dynamic_cast<Book*>(books.at(i));
        stream << "Begin book" << "\n";
        stream << b->getTitolo() << "\n";

        QList<QString> autori = b->getAutori();
        if(autori.size() != 0)
        {
            stream << "autori" << "\n";
            for(int i=0; i < autori.size(); ++i) stream << autori.at(i) << "\n";
            stream << "end_autori" << "\n";
        }

        QDate dp = b->getDataPubblicazione();
        if(!dp.isNull())
        {
            stream << "data di pubblicazione" << "\n";
            stream << dp.year() << "\n" << dp.month() << "\n" << dp.day() << "\n";
        }

        temp = b->getLingua();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "lingua" << "\n";
            stream << temp << "\n";
        }

        QList<QString> generi = b->getGeneri();
        if(generi.size() != 0)
        {
            stream << "generi" << "\n";
            for(int i=0; i < generi.size(); ++i) stream << generi.at(i) << "\n";
            stream << "end_generi" << "\n";
        }

        temp = b->getDescrizione();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "descrizione" << "\n";
            stream << temp << "\n";
        }

        temp = b->getImmagine();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "immagine" << "\n";
            stream << temp << "\n";
        }

        if(b->getNumeroPagine()!=0)
        {
            stream << "numero pagine" << "\n";
            stream << b->getNumeroPagine() << "\n";
        }

        QList<QString> curatori = b->getCuratori();
        if(curatori.size() != 0)
        {
            stream << "curatori" << "\n";
            for(int i=0; i < curatori.size(); ++i) stream << curatori.at(i) << "\n";
            stream << "end_curatori" << "\n";
        }

        temp = b->getEditore();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "editore" << "\n";
            stream << temp << "\n";
        }

        temp = b->getCollana();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "collana" << "\n";
            stream << temp << "\n";
        }

        temp = b->getLibro();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "libro" << "\n";
            stream << temp << "\n";
        }

        stream << "end" << "\n";
    }

    for(int i=0; i<lightNovels.size(); ++i)
    {
        Light_novel* b = dynamic_cast<Light_novel*>(lightNovels.at(i));
        stream << "Begin light novel" << "\n";
        stream << b->getTitolo() << "\n";

        QList<QString> autori = b->getAutori();
        if(autori.size() != 0)
        {
            stream << "autori" << "\n";
            for(int i=0; i < autori.size(); ++i) stream << autori.at(i) << "\n";
            stream << "end_autori" << "\n";
        }

        QDate dp = b->getDataPubblicazione();
        if(!dp.isNull())
        {
            stream << "data di pubblicazione" << "\n";
            stream << dp.year() << "\n" << dp.month() << "\n" << dp.day() << "\n";
        }

        temp = b->getLingua();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "lingua" << "\n";
            stream << temp << "\n";
        }

        QList<QString> generi = b->getGeneri();
        if(generi.size() != 0)
        {
            stream << "generi" << "\n";
            for(int i=0; i < generi.size(); ++i) stream << generi.at(i) << "\n";
            stream << "end_generi" << "\n";
        }

        temp = b->getDescrizione();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "descrizione" << "\n";
            stream << temp << "\n";
        }

        temp = b->getImmagine();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "immagine" << "\n";
            stream << temp << "\n";
        }

        int n = b->getCapitoliTradotti();
        if(n != 0)
        {
            stream << "capitoli tradotti" << "\n";
            stream << n << "\n";
        }
        n = b->getCapitoliScritti();
        if(n != 0)
        {
            stream << "capitoli scritti" << "\n";
            stream << n << "\n";
        }

        stream << "completato" << "\n";
        if(b->isCompletato()) stream << 1 << "\n";
        else stream << 0 << "\n";


        QList<QString> traduttori = b->getTraduttori();
        if(!traduttori.isEmpty())
        {
            stream << "traduttori" << "\n";
            for(int i=0; i < traduttori.size(); ++i) stream << traduttori.at(i) << "\n";
            stream << "end_traduttori" << "\n";
        }

        temp = b->getLinguaOriginale();
        if(!(temp.isNull() || temp.isEmpty()))
        {
            stream << "lingua originale" << "\n";
            stream << temp << "\n";
        }

        QList<Capitolo*> capitoli = b->getCapitoli();
        if(!capitoli.isEmpty())
        {
            stream << "capitoli" << "\n";
            for(int i=0; i < capitoli.size(); ++i)
            {
                stream << "titolo" << "\n";
                stream << capitoli.at(i)->getTitolo() << "\n";
                stream << "testo" << "\n";
                stream << capitoli.at(i)->getTesto() << "\n";
                stream << "end_testo" << "\n";
            }
            stream << "end_capitoli" << "\n";
        }

        stream << "end" << "\n";
    }

}

Book* Database::findBook(QString s) const
{
    for(int i=0; i< books.size(); ++i)
        if(books.at(i)->getTitolo() == s)
            return books.at(i);
    return NULL;
}

Light_novel* Database::findLightNovel(QString s) const
{
    for(int i=0; i< lightNovels.size(); ++i)
        if(lightNovels.at(i)->getTitolo() == s)
            return lightNovels.at(i);
    return NULL;
}

Utente* Database::findUtente(QString u) const
{
    for(int i=0; i<utenti.size(); ++i)
        if(utenti.at(i)->getUsername() == u)
            return utenti.at(i);
    return NULL;
}

QStringList Database::findAll(QString x) const
{
    QStringList temp;

    for(int i=0; i< books.size(); ++i)
        if(books.at(i)->contains(x)) temp.append(books.at(i)->getTitolo());

    for(int i=0; i< lightNovels.size(); ++i)
        if(lightNovels.at(i)->contains(x)) temp.append(lightNovels.at(i)->getTitolo());

    return temp;
}

QStringList Database::findLibro(QString title, QString langue, QString author, QString genre) const
{
    QStringList temp;

    for(int i=0; i< books.size(); ++i)
        if(books.at(i)->Libro::find(title, langue, author, genre)) temp.append(books.at(i)->getTitolo());

    for(int i=0; i< lightNovels.size(); ++i)
        if(lightNovels.at(i)->Libro::find(title, langue, author, genre)) temp.append(lightNovels.at(i)->getTitolo());

    return temp;
}

QStringList Database::findBook(QString title, QString langue, QString author, QString genre, QString editor, QString series, QString curator) const
{
    QStringList temp;

    for(int i=0; i< books.size(); ++i)
        if(books.at(i)->find(title, langue, author, genre, editor, series, curator)) temp.append(books.at(i)->getTitolo());

    return temp;
}

QStringList Database::findLightNovel(QString title, QString langue, QString author, QString genre, QString translator, QString orginalLanguage, bool completed) const
{
    QStringList temp;

    for(int i=0; i< lightNovels.size(); ++i)
        if(lightNovels.at(i)->find(title, langue, author, genre, translator, orginalLanguage, completed)) temp.append(lightNovels.at(i)->getTitolo());

    return temp;
}

QStringList Database::listaUtenti() const
{
    QStringList temp;
    for(int i=0; i<utenti.size(); ++i)
    {
        temp.append(utenti.at(i)->getUsername());
    }
    return temp;
}

QList<Book*> Database::listaBooks() const
{
    QList<Book*> temp;
    for(int i=0; i<books.size(); ++i)
    {
        temp.append(books.at(i));
    }
    return temp;
}

QList<Light_novel*> Database::listaLightNovels() const
{
    QList<Light_novel*> temp;
    for(int i=0; i<lightNovels.size(); ++i)
    {
        temp.append(lightNovels.at(i));
    }
    return temp;
}


bool Database::addBook(Book* l)
{
    for(int i=0; i < books.size(); ++i)
        if(books.at(i)->getTitolo() == l->getTitolo())
            return false;
    for(int i=0; i < lightNovels.size(); ++i)
        if(lightNovels.at(i)->getTitolo() == l->getTitolo())
            return false;
    books.append(l);
    return true;
}

bool Database::addLightNovel(Light_novel* l)
{
    for(int i=0; i < books.size(); ++i)
        if(books.at(i)->getTitolo() == l->getTitolo())
            return false;
    for(int i=0; i < lightNovels.size(); ++i)
        if(lightNovels.at(i)->getTitolo() == l->getTitolo())
            return false;
    lightNovels.append(l);
    return true;
}

void Database::removeBook(Book* l)
{
    for(int i=0; i<books.size(); ++i)
    {
        if(l->getTitolo() == books.at(i)->getTitolo())
        {
            delete books.at(i);
            books.removeAt(i);
        }
    }
}

void Database::removeLightNovel(Light_novel* l)
{
    for(int i=0; i<lightNovels.size(); ++i)
    {
        if(l->getTitolo() == lightNovels.at(i)->getTitolo())
        {
            delete lightNovels.at(i);
            lightNovels.removeAt(i);
        }
    }
}

bool Database::updateBook(Book* l)
{
    for(int i=0; i<books.size(); ++i)
    {
        if(l->getTitolo() == books.at(i)->getTitolo())
        {
            delete books.at(i);
            books.replace(i, l);
            return true;
        }
    }
    return false;
}

bool Database::updateLightNovel(Light_novel* l)
{
    for(int i=0; i<lightNovels.size(); ++i)
    {
        if(l->getTitolo() == lightNovels.at(i)->getTitolo())
        {
            delete lightNovels.at(i);
            lightNovels.replace(i, l);
            return true;
        }
    }
    return false;
}

bool Database::addUtente(Utente* u)
{
    for(int i=0; i < utenti.size(); ++i)
        if(utenti.at(i)->getUsername() == u->getUsername())
            return false;
    utenti.append(u);
    return true;
}

void Database::removeUtente(Utente* u)
{
    for(int i=0; i<utenti.size(); ++i)
    {
        if(u->getUsername() == utenti.at(i)->getUsername())
        {
            delete utenti.at(i);
            utenti.removeAt(i);
        }
    }
}
