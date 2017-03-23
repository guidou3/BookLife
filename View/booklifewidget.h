#ifndef BOOKLIFEWIDGET_H
#define BOOKLIFEWIDGET_H

#include "Model/session.h"

#include "signupwidget.h"
#include "adminclientwidget.h"
#include "userclientwidget.h"
#include "writerclientwidget.h"

class BookLifeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BookLifeWidget(QWidget *parent = 0);
    ~BookLifeWidget();
private:
    // campi dati logici
    Database* db; //puntatore al database
    Session* session; //classe privata per la gestione delle informazioni della sessione

    // campi dati grafici
    QVBoxLayout* mainLayout; // layout principale
    QGroupBox* mainBox; // contenitore dei widget

    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLabel* messaggio;

    //widget esterni
    ClientWidget* client; //puntatore polimorfo al client
    SignUpWidget* signup; //widget per la registrazione

public slots:
    void effettuaLogin(); // procedura per il login dell'utente e chiamata al rispettivo client
    void sessioneTerminata(); // procedura di ripristino della schermata di login al termine di una sessione utente
    void sessioneScrittoreTerminata(); // procedura per il passaggio da client scrittore a client utente
    void signupSlot(); // procedura per la visualizzazione del widget di signup
    void annullaSignUp(); // procedura di ripristino della schermata di login al termine di un signup
};

#endif // BOOKLIFEWIDGET_H
