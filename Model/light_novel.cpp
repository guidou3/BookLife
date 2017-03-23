#include "light_novel.h"

Light_novel::Light_novel(QString t) : Libro(t), capitoli_tradotti(0), capitoli_scritti(0), completato(false) {}

Light_novel::Light_novel(QString t, QList<QString> a, QDate d, QString l, QList<QString> gen, QString dex, QString im, unsigned int ct, unsigned int cs, bool c, QList<QString> tr, QString lo, QList<Capitolo *> cap):
                        Libro(t, a, d, l, gen, dex, im), capitoli_tradotti(ct), capitoli_scritti(cs), completato(c), traduttori(tr), lingua_originale(lo), capitoli(cap) {}

unsigned int Light_novel::getCapitoliTradotti() const
{
    return capitoli_tradotti;
}

unsigned int Light_novel::getCapitoliScritti() const
{
    return capitoli_scritti;
}

bool Light_novel::isCompletato() const
{
    return completato;
}

QList<QString> Light_novel::getTraduttori() const
{
    return traduttori;
}

QString Light_novel::getLinguaOriginale() const
{
    return lingua_originale;
}

Capitolo* Light_novel::getCapitolo(int index) const
{
    return capitoli.at(index);
}

QList<Capitolo*> Light_novel::getCapitoli() const
{
    QList<Capitolo*> temp;
    for(int i=0; i<capitoli.length(); ++i)
    {
        temp.append(capitoli.at(i));
    }
    return temp;
}

QStringList Light_novel::getTitoli() const
{
    QStringList temp;
    for(int i=0; i<capitoli.length(); ++i)
    {
        temp.append(capitoli.at(i)->getTitolo());
    }
    return temp;
}

int Light_novel::getCapitoloIndex(QString s) const
{
    for(int i=0; i<capitoli.size(); ++i)
    {
        if(capitoli.at(i)->getTitolo() == s)
        {
            return i;
        }
    }
    return -1;
}

// SET

void Light_novel::setCapitoliTradotti(unsigned int ct)
{
    capitoli_tradotti = ct;
}

void Light_novel::setCapitoliScritti(unsigned int cs)
{
    capitoli_scritti = cs;
}

void Light_novel::setCompletato(bool c)
{
    completato = c;
}

void Light_novel::setTraduttori(QList<QString> t)
{
    traduttori = t;
}

void Light_novel::setLinguaOriginale(QString lo)
{
    lingua_originale = lo;
}

void Light_novel::addCapitolo(Capitolo * s)
{
    capitoli.append(s);
}

void Light_novel::modificaCapitolo(int index, Capitolo *s)
{
    capitoli.replace(index, s);
}

QString Light_novel::getType() const
{
    return "LightNovel";
}

bool Light_novel::contains(QString x) const
{
    if(Libro::contains(x)) return true;
    else {
        if (lingua_originale.contains(x, Qt::CaseInsensitive)) return true;
        else {
            for(int i=0; i< traduttori.size(); ++i) {
                if(traduttori.at(i).contains(x, Qt::CaseInsensitive)) return true;
            }
            for(int i=0; i< capitoli.size(); ++i) {
                if(capitoli.at(i)->contains(x)) return true;
            }
        }
    }
    return false;
}

bool Light_novel::find(QString title, QString langue, QString author, QString genre, QString translator, QString orginalLanguage, bool completed) const
{
    if(!Libro::find(title, langue, author, genre)) return false;
    else {
        if(lingua_originale.contains(orginalLanguage, Qt::CaseInsensitive) && completato == completed)
        {
            if(translator.isEmpty()) return true;
            else
            {
                for(int i=0; i< traduttori.size(); ++i)
                {
                    if(traduttori.at(i).contains(translator, Qt::CaseInsensitive)) return true;
                }
            }
        }
    }
    return false;
}
