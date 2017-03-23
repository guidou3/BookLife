#ifndef SCRITTORE_H
#define SCRITTORE_H

#include "Utente.h"
#include "amministratore.h"

class Scrittore : public Utente
{
private:
    QStringList lavori;
public:
    Scrittore(QString, QString, QList<QString> = QList<QString>(), QStringList  = QStringList());
    bool isMine(Light_novel*) const; //controlla se la light novel fornita compare tra i lavori dello scrittore
    void setMine(Light_novel*, bool); //imposta la light novel fornita come lavoro dello scrittore
    QStringList getLavori() const; //metodo che restituisce la lista dei lavori

    void addLavoro(QString);
    void removeLavoro(QString);
    void setLavori(QStringList);

    virtual int tipoAccount() const;
};

#endif // SCRITTORE_H
