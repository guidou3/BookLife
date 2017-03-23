#ifndef CAPITOLO_H
#define CAPITOLO_H

#include <QString>

class Capitolo
{
private:
    QString titolo;
    QString testo;
public:
    Capitolo();
    Capitolo(QString, QString);

    QString getTitolo() const;
    QString getTesto() const;

    void setTitolo(QString);
    void setTesto(QString);

    bool contains(QString) const; //controlla se il titolo o il testo del capitolo contiene la stringa
};

#endif // CAPITOLO_H
