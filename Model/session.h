#ifndef SESSION_H
#define SESSION_H

#include "Model/database.h"

class Session
{
public:
    Session(QString, QString, Database*);
    Database* db; // database di BookLife
    Utente* utenteLoggato; // utente che ha effettuato il login

    bool isValid() const; // metodo che restituisce true se le credenziali sono esatte e session è valido
    int getAccountType() const; //metodo che resituisce il tipo dell'utente
};

#endif // SESSION_H
