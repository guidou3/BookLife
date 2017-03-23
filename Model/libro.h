#ifndef LIBRO_H
#define LIBRO_H

#include <QString>
#include <QList>
#include <QDate>
#include <QImage>

//IDEA: il libro intero non viene effettivamente scritto all'interno di un campo dati, ma viene semplicemente chiamato il file che lo contiene

class Libro
{
private:
  QString titolo;
  QList<QString> autori;
  QDate dataPubblicazione;
  QString lingua;
  QList<QString> generi;
  QString descrizione;
  QString immagine;

public:
  Libro(QString);
  Libro(const Libro&);
  Libro(QString, QList<QString>, QDate, QString, QList<QString>, QString, QString);

  QString getTitolo() const;
  QStringList getAutori() const;
  QDate getDataPubblicazione() const;
  QString getLingua() const;
  QList<QString> getGeneri() const;
  QString getDescrizione() const;
  QString getImmagine() const;

  void setTitolo(QString);
  void setAutori(QList<QString>);
  void setDataPubblicazione(QDate);
  void setLingua(QString);
  void setGeneri(QList<QString>);
  void setDescrizione(QString);
  void setImmagine(QString);

  virtual QString getType() const =0; // metodo virtuale che restituisce il tipo di questo libro sotto forma di stringa
  virtual bool contains(QString) const; //metodo virtuale che ha il compito di verificare se uno qualsiasi dei campi del libro contiene la stringa fornita
  virtual bool find(QString, QString, QString, QString) const; //metodo virtuale che ha il compito di verificare se gli attributi di libro contengono i valori corrispondenti forniti
  virtual ~Libro() {}
};

#endif // LIBRO_H
