#include "libro.h"

Libro::Libro(QString t) : titolo(t) {}

Libro::Libro(const Libro& l): titolo(l.titolo), autori(l.autori), dataPubblicazione(l.dataPubblicazione), lingua(l.lingua), generi(l.generi), descrizione(l.descrizione), immagine(l.immagine){}

Libro::Libro(QString t, QList<QString> a, QDate d, QString l, QList<QString> gen, QString dex, QString im):
    titolo(t), autori(a), dataPubblicazione(d), lingua(l), generi(gen), descrizione(dex), immagine(im){}

QString Libro::getTitolo() const
{
    return titolo;
}

QStringList Libro::getAutori() const
{
    return autori;
}

QDate Libro::getDataPubblicazione() const
{
    return dataPubblicazione;
}

QString Libro::getLingua() const
{
    return lingua;
}

QList<QString> Libro::getGeneri() const
{
    return generi;
}

QString Libro::getDescrizione() const
{
    return descrizione;
}

QString Libro::getImmagine() const
{
    return immagine;
}

// SET

void Libro::setTitolo(QString t)
{
    titolo = t;
}

void Libro::setAutori(QList<QString> a)
{
    autori = a;
}

void Libro::setDataPubblicazione(QDate d)
{
    dataPubblicazione = d;
}

void Libro::setLingua(QString l)
{
    lingua = l;
}

void Libro::setGeneri(QList<QString> gen)
{
    generi = gen;
}

void Libro::setDescrizione(QString dex)
{
    descrizione = dex;
}

void Libro::setImmagine(QString im)
{
    immagine = im;
}

bool Libro::contains(QString x) const
{
    if(titolo.contains(x, Qt::CaseInsensitive)) return true;
    else if (lingua.contains(x, Qt::CaseInsensitive)) return true;
    else if (descrizione.contains(x, Qt::CaseInsensitive)) return true;
    else {
        for(int i=0; i< autori.size(); ++i) {
            if(autori.at(i).contains(x, Qt::CaseInsensitive)) return true;
        }
        for(int i=0; i< generi.size(); ++i) {
            if(generi.at(i).contains(x, Qt::CaseInsensitive)) return true;
        }
    }
    return false;
}

bool Libro::find(QString title, QString langue, QString author, QString genre) const
{
    if(titolo.contains(title, Qt::CaseInsensitive) && lingua.contains(langue, Qt::CaseInsensitive))
    {
        if(author.isEmpty())
        {
            if(genre.isEmpty()) return true;
            else
            {
                for(int j=0; j< generi.size(); ++j)
                {
                    if(genre.isEmpty() || generi.at(j).contains(genre, Qt::CaseInsensitive)) return true;
                }
                return false;
            }
        }
        else
        {
            for(int i=0; i< autori.size(); ++i)
            {
                if(autori.at(i).contains(author, Qt::CaseInsensitive))
                {
                    if(genre.isEmpty()) return true;
                    else
                    {
                        for(int j=0; j< generi.size(); ++j)
                        {
                            if(generi.at(j).contains(genre, Qt::CaseInsensitive)) return true;
                        }
                        return false;
                    }
                }
            }
        }
    }
    return false;
}
