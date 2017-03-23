#ifndef UTENTE_H
#define UTENTE_H
#include "book.h"
#include "light_novel.h"
#include <QString>
using namespace std;

class Utente
{
private:
  QString username;
  QString password;
  QList<QString> preferiti;

public:
  Utente(QString, QString, QList<QString> = QList<QString>());

  QString getUsername() const;
  QString getPassword() const;
  QList<QString> getPreferiti() const;

  void setUsername(QString);
  void setPassword(QString);
  bool addPreferito(QString);
  void removePreferito(QString);
  void setPreferiti(QList<QString>);

  virtual int tipoAccount() const; //metodo virtuale con lo scopo di ottenere un numero corrispondente al tipo dinamico di un puntatore di tipo Utente
  virtual ~Utente();
};

#endif // UTENTE_H
