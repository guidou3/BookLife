#ifndef VIEWLIBROWIDGET_H
#define VIEWLIBROWIDGET_H

#include "Model/libro.h"

#include <QBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFormLayout>
#include <QListWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QDateEdit>
#include <QWidget>
#include <QScrollArea>
#include <QPixmap>
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>

class ViewLibroWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewLibroWidget(Libro*, QWidget *parent = 0);

protected:
    // campi dati grafici
    QVBoxLayout* mainLayout;
    QVBoxLayout* parallelLayout;
    QHBoxLayout* centralLayout;
    QFormLayout* rowLayout;
    QFormLayout* listLayout;
    QGroupBox* visualizzaBox;

    // campi dati grafici per la visualizzazione dei dati
    QLabel* titoloLabel;
    QListWidget* autoriList;
    QLabel* dataPubblicazioneLabel;
    QLabel* linguaLabel;
    QListWidget* generiList;
    QLabel* descrizioneLabel;
    QLabel* fileImmagine;
    QLabel* immagineLabel;
};

#endif // VIEWLIBROWIDGET_H
