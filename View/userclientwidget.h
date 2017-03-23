#ifndef USERCLIENTWIDGET_H
#define USERCLIENTWIDGET_H

#include "clientwidget.h"
#include "listalibriwidget.h"
#include "listapreferitiwidget.h"

class UserClientWidget : public ClientWidget
{
    Q_OBJECT

public:
    explicit UserClientWidget(Session*, QWidget *parent = 0);
    ~UserClientWidget();

private:
    ListaLibriWidget* book;
    ListaLibriWidget* ln;
    ListaPreferitiWidget* preferiti;

public slots:
    void hideSlot(); // procedura per nascondere tutti i widget (QLabel, QPushButton) che normalmente dovrebbero essere nascosti

};

#endif // USERCLIENTWIDGET_H
