#include "book.h"

Book::Book(QString t) : Libro(t), numeroPagine(0) {}

Book::Book(QString t, QList<QString> a, QDate d, QString l, QList<QString> gen, QString dex, QString im, int n, QList<QString> cur, QString ed, QString coll, QString lib):
    Libro(t, a, d, l, gen, dex, im), numeroPagine(n), curatori(cur), editore(ed), collana(coll), libro(lib) {}

Book::~Book()
{
    if(!this->getLibro().isEmpty()) QFile::remove(this->getLibro());
}


int Book::getNumeroPagine() const
{
    return numeroPagine;
}

QList<QString> Book::getCuratori() const
{
    return curatori;
}

QString Book::getEditore() const
{
    return editore;
}

QString Book::getCollana() const
{
    return collana;
}

QString Book::getLibro() const
{
    return libro;
}

// SET

void Book::setNumeroPagine(int n)
{
    numeroPagine = n;
}

void Book::setCuratori(QList<QString> cur)
{
    curatori = cur;
}

void Book::setEditore(QString ed)
{
    editore = ed;
}

void Book::setCollana(QString coll)
{
    collana = coll;
}

void Book::setLibro(QString file)
{
    libro = file;
}

QString Book::getType() const
{
    return "Book";
}

bool Book::contains(QString x) const
{
    if(Libro::contains(x)) return true;
    else {
        if (editore.contains(x, Qt::CaseInsensitive)) return true;
        else if (collana.contains(x, Qt::CaseInsensitive)) return true;
        else {
            for(int i=0; i< curatori.size(); ++i) {
                if(curatori.at(i).contains(x, Qt::CaseInsensitive)) return true;
            }
        }
    }
    return false;
}

bool Book::find(QString title, QString langue, QString author, QString genre, QString editor, QString series, QString curator) const
{
    if(!Libro::find(title, langue, author, genre)) return false;
    else {
        if(editore.contains(editor, Qt::CaseInsensitive) && collana.contains(series, Qt::CaseInsensitive))
        {
            if(curator.isEmpty()) return true;
            else
            {
                for(int i=0; i< curatori.size(); ++i)
                {
                    if(curatori.at(i).contains(curator, Qt::CaseInsensitive)) return true;
                }
            }
        }
    }
    return false;
}
