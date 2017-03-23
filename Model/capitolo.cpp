#include "capitolo.h"

Capitolo::Capitolo()
{

}

Capitolo::Capitolo(QString t, QString text): titolo(t), testo(text) {}

QString Capitolo::getTitolo() const
{
    return titolo;
}

QString Capitolo::getTesto() const
{
    return testo;
}

void Capitolo::setTitolo(QString t)
{
    titolo = t;
}

void Capitolo::setTesto(QString t)
{
    testo = t;
}

bool Capitolo::contains(QString x) const
{
    if(titolo.contains(x, Qt::CaseInsensitive)) return true;
    else if (testo.contains(x, Qt::CaseInsensitive)) return true;
    return false;
}
