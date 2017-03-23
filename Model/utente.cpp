#include "utente.h"

Utente::Utente(QString id, QString pw, QList<QString> p): username(id), password(pw), preferiti(p){}

QString Utente::getUsername() const
{
  return username;
}

QString Utente::getPassword() const
{
  return password;
}

QList<QString> Utente::getPreferiti() const
{
    QList<QString> temp;
    for(int i=0; i<preferiti.length(); ++i)
    {
        temp.append(preferiti.at(i));
    }
    return temp;
}

void Utente::setUsername(QString id)
{
  username = id;
}

void Utente::setPassword(QString pw)
{
  password = pw;
}

bool Utente::addPreferito(QString p)
{
    for(int i=0; i<preferiti.size(); ++i)
        if(preferiti.at(i) == p)
            return false;

    preferiti.append(p);
    return true;
}

void Utente::removePreferito(QString p)
{
    preferiti.removeOne(p);
}

void Utente::setPreferiti(QList<QString> ls)
{
    preferiti.clear();
    for(int i=0; i<ls.size(); i++)
    {
        preferiti.append(ls.at(i));
    }
}

int Utente::tipoAccount() const
{
    return 0;
}

Utente::~Utente()
{

}
