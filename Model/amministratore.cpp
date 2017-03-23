#include "amministratore.h"


Amministratore::Amministratore(QString id, QString pw, QList<QString> p): Utente(id, pw, p){}

int Amministratore::tipoAccount() const
{
    return 2;
}
