#include "client.h"

Client::Client(Session* s)
{
    current = s;
    utenteSelezionato = 0;
    libroSelezionato = 0;
}

Libro* Client::getLibroSelezionato() const
{
    return libroSelezionato;
}

Utente* Client::getUtenteSelezionato() const
{
    return utenteSelezionato;
}

void Client::resetSelezionati()
{
    libroSelezionato = 0;
    utenteSelezionato = 0;
}

Session* Client::getSession() const
{
    return current;
}

bool Client::libroExists() const
{
    if(libroSelezionato == 0) return false;
    else return true;
}

bool Client::utenteExists() const
{
    if(utenteSelezionato == 0) return false;
    else return true;
}

void Client::setTipoClient(int i)
{
    tipoClient = i;
}

int Client::getTipoClient() const
{
    return tipoClient;
}

void Client::rimuoviUtente()
{
    if(utenteSelezionato && utenteSelezionato->getUsername() != current->utenteLoggato->getUsername())
    {
        current->db->removeUtente(utenteSelezionato);
        utenteSelezionato = 0;
        libroSelezionato = 0;
    }
}

bool Client::addPreferito()
{
    if(libroSelezionato)
    {
        return current->utenteLoggato->addPreferito(libroSelezionato->getTitolo());
    }
    else return false;
}

void Client::removePreferito()
{
    if(libroSelezionato)
    {
        current->utenteLoggato->removePreferito(libroSelezionato->getTitolo());
    }
}

void Client::removePreferito(QString s)
{
    current->utenteLoggato->removePreferito(s);
}

void Client::rimuoviLibro()
{
    if(libroSelezionato)
    {
        Book* temp = dynamic_cast<Book*>(libroSelezionato);
        if(temp != NULL) current->db->removeBook(temp);
        else current->db->removeLightNovel(dynamic_cast<Light_novel*>(libroSelezionato));
        libroSelezionato = 0;
        utenteSelezionato = 0;
    }
}

QStringList Client::getListaUtenti() const
{
    return current->db->listaUtenti();
}

QStringList Client::getListaPreferiti() const
{
    return current->utenteLoggato->getPreferiti();
}

QList<Book*> Client::getListaBook() const
{
    return current->db->listaBooks();
}

QList<Light_novel*> Client::getListaLightNovel() const
{
    return current->db->listaLightNovels();
}

QList<Libro*> Client::getListaBookStandard() const
{
    QList<Book*> temp = current->db->listaBooks();
    QList<Libro*> newList;
    for(int i=0; i<temp.size(); i++)
    {
        newList.append(temp.at(i));
    }
    return newList;
}

QList<Libro*> Client::getListaLightNovelStandard() const
{
    QList<Light_novel*> temp = current->db->listaLightNovels();
    QList<Libro*> newList;
    for(int i=0; i<temp.size(); i++)
    {
        newList.append(temp.at(i));
    }
    return newList;
}

QStringList Client::getLavori()
{
    Scrittore* u = dynamic_cast<Scrittore*>(current->utenteLoggato);
    QStringList temp = u->getLavori();
    for(int i=0; i<temp.size(); ++i)
    {
        findLightNovel(temp.at(i));
        if(!libroSelezionato)
        {
            u->removeLavoro(temp.at(i));
        }
    }
    return u->getLavori();
}

void Client::updateListaLavori()
{
    Scrittore* u = dynamic_cast<Scrittore*>(current->utenteLoggato);
    QStringList  temp = current->db->findLightNovel("", "", "", "", u->getUsername(), "", false);
    temp += current->db->findLightNovel("", "", "", "", u->getUsername(), "", true);
    u->setLavori(temp);
}

void Client::findUtente(QString u)
{
    utenteSelezionato = current->db->findUtente(u);
    libroSelezionato = 0;
}

bool Client::findPreferito(QString s)
{
    QStringList temp = getListaPreferiti();
    for(int i=0; i<temp.size(); ++i)
    {
        if(temp.at(i) == s)
        {
            findBook(s);
            if(libroSelezionato) return true;
            else
            {
                findLightNovel(s);
                if(libroSelezionato) return true;
                else return false;
            }
        }
    }
    return false;
}

void Client::findBook(QString u)
{
    libroSelezionato = current->db->findBook(u);
    utenteSelezionato = 0;
}

void Client::findLightNovel(QString u)
{
    libroSelezionato = current->db->findLightNovel(u);
    utenteSelezionato = 0;
}

QStringList Client::findAll(QString x) const
{
    return current->db->findAll(x);
}

QStringList Client::findLibro(QString title, QString langue, QString author, QString genre) const
{
    return current->db->findLibro(title, langue, author, genre);
}

QStringList Client::findBook(QString title, QString langue, QString author, QString genre, QString editor, QString series, QString curator) const
{
    return current->db->findBook(title, langue, author, genre, editor, series, curator);
}

QStringList Client::findLightNovel(QString title, QString langue, QString author, QString genre, QString translator, QString orginalLanguage, bool completed) const
{
    return current->db->findLightNovel(title, langue, author, genre, translator, orginalLanguage, completed);
}

bool Client::addBook(Book* b)
{
    return current->db->addBook(b);
}

bool Client::updateBook(Book* b)
{
    return current->db->updateBook(b);
}

bool Client::addLightNovel(Light_novel* ln)
{
    return current->db->addLightNovel(ln);
}

bool Client::updateLightNovel(Light_novel* ln)
{
    return current->db->updateLightNovel(ln);
}

