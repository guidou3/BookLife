#include <QApplication>
#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "View/booklifewidget.h"


using namespace std;

/* Da fare:
 *
 * 1. lightNovelWidget e bookWidget gestire le informazioni tramite client
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BookLifeWidget w;
    w.show();

    return a.exec();
}

