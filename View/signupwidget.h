#ifndef SIGNUPWIDGET_H
#define SIGNUPWIDGET_H

#include "Model/database.h"

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QLayout>
#include <QGroupBox>
#include <QWidget>


class SignUpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SignUpWidget(Database*, QWidget *parent = 0);
    ~SignUpWidget();

private:
    // campi dati logici
    Database* db;
    // campi dati grafici
    QVBoxLayout* SignUpLayout;
    QGroupBox* SignUpBox;
    QLineEdit* usernameEdit; // campo di modifica dello username
    QLineEdit* passwordEdit; // campo di modifica del nome
    QLabel* message;
signals:
    void indietro();
public slots:
    void creaUtente(); // procedura per la registrazione di un utente
    void creaScrittore(); // procedura per la registrazione di uno scrittore
    void creaAmministratore(); // procedura per la registrazione di un admin
};

#endif // SIGNUPWIDGET_H
