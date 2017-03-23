#ifndef AMMINISTRATORE_H
#define AMMINISTRATORE_H

#include "utente.h"

class Amministratore : public Utente
{
public:
    Amministratore(QString, QString, QList<QString> = QList<QString>());

    virtual int tipoAccount() const;
};

#endif // AMMINISTRATORE_H
