#ifndef VIEWLIGHTNOVELWIDGET_H
#define VIEWLIGHTNOVELWIDGET_H

#include "Model/light_novel.h"
#include "Controller/client.h"

#include "viewlibrowidget.h"
#include "listacapitoliwidget.h"

class ViewLightNovelWidget : public ViewLibroWidget
{
    Q_OBJECT

public:
    explicit ViewLightNovelWidget(Light_novel*, Client*, QWidget *parent = 0);

private:
    Client* logic;
    Light_novel* lightNovel;

    ListaCapitoliWidget* capitoli;

    QVBoxLayout* layCap;

    QLabel* capitoli_tradottiLabel;
    QLabel* capitoli_scrittiLabel;
    QLabel* completatoLabel;
    QListWidget* traduttoriList;
    QLabel* lingua_originaleLabel;
};

#endif // VIEWLIGHTNOVELWIDGET_H
