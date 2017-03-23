#ifndef BOOK_H
#define BOOK_H
#include "libro.h"
#include <QFile>

class Book: public Libro
{
private:
  int numeroPagine;
  QList<QString> curatori;
  QString editore;
  QString collana;
  QString libro;

public:
    Book(QString);
    Book(QString, QList<QString>, QDate, QString, QList<QString>, QString, QString, int, QList<QString>, QString, QString, QString);

    int getNumeroPagine() const;
    QList<QString> getCuratori() const;
    QString getEditore() const;
    QString getCollana() const;
    QString getLibro() const;

    void setNumeroPagine(int);
    void setCuratori(QList<QString>);
    void setEditore(QString);
    void setCollana(QString);
    void setLibro(QString);

    //per la descrizione dei metodi seguenti guardare la classe base
    virtual QString getType() const;
    virtual bool contains(QString) const;
    virtual bool find(QString, QString, QString, QString, QString, QString, QString) const;
    ~Book();
};

#endif // BOOK_H
