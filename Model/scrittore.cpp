#include "scrittore.h"
#include <iostream>
using namespace std;

Scrittore::Scrittore(QString id, QString pw, QList<QString> p, QStringList  s)
                        : Utente(id, pw, p), lavori(s)
{

}

bool Scrittore::isMine(Light_novel* l) const
{
    for(int i=0; i<lavori.size(); ++i)
    {
        if(lavori.at(i) == l->getTitolo())
            return true;
    }
    return false;
}

void Scrittore::setMine(Light_novel* l, bool b)
{
    if(b)
    {
        if(isMine(l))
            return;
        else
            lavori.append(l->getTitolo());
    }
    else{
        for(int i=0; i<lavori.size(); ++i)
        {
            if(lavori.at(i) == l->getTitolo())
            {
                lavori.removeAt(i);
            }
        }
    }
}

QStringList Scrittore::getLavori() const
{
    QStringList temp;
    for(int i=0; i<lavori.size(); ++i)
    {
        temp.append(lavori.at(i));
    }
    return temp;
}

void Scrittore::addLavoro(QString la)
{
    lavori.append(la);
}

void Scrittore::removeLavoro(QString la)
{
    for(int i=0; i<lavori.size();++i)
        if(lavori.at(i) == la)
        {
            lavori.removeAt(i);
            return;
        }
}

void Scrittore::setLavori(QStringList nuovi)
{
    lavori = nuovi;
}

int Scrittore::tipoAccount() const
{
    return 1;
}
