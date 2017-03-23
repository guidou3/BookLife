#ifndef LIGHT_NOVEL_H
#define LIGHT_NOVEL_H
#include "libro.h"
#include "capitolo.h"

class Light_novel: public Libro
{
private:
  unsigned int capitoli_tradotti;
  unsigned int capitoli_scritti;
  bool completato;
  QList<QString> traduttori;
  QString lingua_originale;
  QList<Capitolo*> capitoli;

public:
    Light_novel(QString);
    Light_novel(QString, QList<QString>, QDate, QString, QList<QString>, QString, QString, unsigned int, unsigned int, bool, QList<QString>, QString, QList<Capitolo*>);

    unsigned int getCapitoliTradotti() const;
    unsigned int getCapitoliScritti() const;
    bool isCompletato() const;
    QList<QString> getTraduttori() const;
    QString getLinguaOriginale() const;
    Capitolo* getCapitolo(int) const;
    QList<Capitolo*> getCapitoli() const;
    QStringList getTitoli() const;
    int getCapitoloIndex(QString) const;

    void setCapitoliTradotti(unsigned int);
    void setCapitoliScritti(unsigned int);
    void setCompletato(bool);
    void setTraduttori(QList<QString>);
    void setLinguaOriginale(QString);
    void addCapitolo(Capitolo*);
    void modificaCapitolo(int, Capitolo*);

    //per la descrizione dei metodi seguenti guardare la classe base
    virtual QString getType() const;
    virtual bool contains(QString) const;
    virtual bool find(QString, QString, QString, QString, QString, QString, bool) const;
    ~Light_novel(){}
};

#endif // LIGHT_NOVEL_H
