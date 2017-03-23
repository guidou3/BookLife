#ifndef CAPITOLOWIDGET_H
#define CAPITOLOWIDGET_H

#include "Model/capitolo.h"
#include "Model/light_novel.h"

#include <QTextEdit>
#include <QTextBrowser>
#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>

class CapitoloWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CapitoloWidget(Capitolo*, QWidget *parent = 0);
    explicit CapitoloWidget(Light_novel*, QWidget *parent = 0);
    explicit CapitoloWidget(Light_novel*, int, QWidget *parent = 0);
    ~CapitoloWidget();

private:
    // campi dati logici
    Capitolo* current;
    Light_novel* lightNovel;
    int index;

    QLabel* titoloLabel;
    QLabel* testoLabel;
    QTextBrowser* testoBrowser;

    QLineEdit* titoloEdit;
    QTextEdit* testoEdit;

    QPushButton* esci;
    QPushButton* salva;

    void hide();
    void initialize();

signals:
    void updateCapitoli();
    void updateNomeCapitolo();

public slots:
    void salvaSlot(); // procedura per il salvataggio di un nuovo capitolo all'interno della light novel fornita
    void aggiornaSlot(); // procedura per l'update dei campi di un dato capitolo
};

#endif // CAPITOLOWIDGET_H
