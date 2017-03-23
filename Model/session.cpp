#include "session.h"

Session::Session(QString user, QString pw, Database* data)
{
    db = data;
    Utente* temp = db->findUtente(user);
    if(temp && temp->getPassword() == pw)
    {
        utenteLoggato = temp;
    }
    else
    {
        utenteLoggato = NULL;
    }
}

bool Session::isValid() const
{
    if(utenteLoggato != NULL)
        return true;
    return false;
}

int Session::getAccountType() const
{
    return utenteLoggato->tipoAccount();
}

