#ifndef dbList_H
#define dbList_H

#include<QList>

#include <iostream>

template<class T>
class dbList{
friend class iteratore;
private:
    class nodo
    {
    public:
        T info;
        nodo* prox;
        nodo(const T& t, nodo* n) : info(t), prox(n) {}
        ~nodo()
        {
            if(prox) delete prox;
        }
    };

    nodo *primo, *ultimo; //puntatori al primo e all'ultimo nodo della dbList
    //dbList vuota if primo == ultimo == 0

    //ritorna il puntatore primo ad una copia della lista
    //puntata da f, dove il ultimo è da mettere a posto
    static nodo* copia(nodo* f)
    {
        if(!f) return 0;
        nodo* tempPrimo = new nodo*(f->info, 0);
        nodo* p = tempPrimo;
        while(f->prox){
            p->prox = new nodo(f->prox->info, 0);
            p = p->prox;
            f = f->prox;
        }
        return tempPrimo;
    }

    static nodo* getUltimo(nodo* f){
        if(!f) return 0;
        while(f->prox) f = f->prox;
        return f;
        // per farlo ricorsivamente, prima delle chiamate ricorsive si dovrebbe
        //aggiungere il caso base if(!f->prox) return f;
    }

public:
    class iteratore
    {
    friend class dbList;
    private:
        dbList::nodo* punt;
    public:
        iteratore& operator++()
        {
            if(punt)
                punt = punt->prox;
            return *this;
        }
        iteratore operator++(int)
        {
            iteratore aux = *this;
            if(punt)
                punt = punt->prox;
            return aux;
        }
        iteratore& operator=(const iteratore& it)
        {
            if(this != &it)
                punt = it.punt;
        }
        bool operator==(const iteratore& it) const
        {
            return punt == it.punt;
        }
        bool operator!=(const iteratore& it) const
        {
            return punt != it.punt;
        }

        T& operator*() const
        {
            return punt->info;
        }
    };

    dbList() : primo(0), ultimo(0) {}

    dbList(const dbList& l) : primo(copia(l.primo)), ultimo(getultimo(primo)) {}

    dbList(int k, const T& t) : primo(0), ultimo(0)
    {
        for(int i = 0; i<k; ++i) append(t);
    }

    ~dbList()
    {
        delete primo;
    }

    T& operator[](const iteratore& it) const
    {
        return it.punt->info;
    }

    dbList& operator=(const dbList& l)
    {
        if(this != &l){
            if(primo) delete primo;
            primo = copia(l.primo);
            ultimo = getultimo(primo);
        }
    }

    iteratore begin() const
    {
        iteratore aux;
        aux.punt = primo;
        return aux;
    }

    iteratore end() const
    {
        iteratore aux;
        aux.punt = 0;
        return aux;
    }

    T& front() const
    {
        return primo->info;
    }

    T& back() const
    {
        return ultimo->info;
    }

    bool insert(int i, const T& t)
    {
        if(i==0)
        {
            push_front(t);
            return true;
        }
        nodo* aux = primo;
        for(int j=0; j<i-1; j++)
        {
            if(aux) aux = aux->prox; //scorre in avanti i nodi fino a raggiungere la posizione desiderata o ad arrivare alla fine della lista
            else return false;
        }
        if(aux)
        {
            aux->prox = new nodo(t, aux->prox);
            return true;
        }
        else return false;
    }

    void push_front(const T& t)
    {
        if(primo){
            primo = new nodo(t, primo);
        }
        else
            ultimo = primo = new nodo(t, 0);
    }

    void append(const T& t)
    {
        if(primo){
            ultimo->prox = new nodo(t,0);
            ultimo = ultimo->prox;
        }
        else
            ultimo = primo = new nodo(t,0);
    }

    void replace(int i, const T& t)
    {
        if(i==0)
        {
            primo->info = t;
            return;
        }
        nodo* aux = primo;
        for(int j=0; j<i; j++)
        {
            if(aux) aux = aux->prox;
            else return;
        }
        if(aux) aux->info = t;
    }

    void removeFirst()
    {
        if(primo)
        {
            nodo* aux = primo;
            primo = primo->prox;
            delete aux;
        }
    }

    void removeLast()
    {
        nodo* aux = ultimo;
        ultimo = ultimo->prec;
        if(ultimo)
            ultimo->prox = 0;
        else
            primo = ultimo = 0;

        delete aux;
    }

    void removeAt(int i)
    {
        if(i==0)
        {
            removeFirst();
            return;
        }
        nodo* aux = primo;
        for(int j=0; j<i-1; j++)
        {
            if(aux) aux = aux->prox;
            else return;
        }
        if(aux)
        {
            nodo* temp = aux->prox;
            aux->prox = aux->prox->prox;
            delete temp;
        }
    }

    bool contains(const T& t) const
    {
        nodo* aux = primo;
        while(aux != ultimo)
        {
            if(aux->info == t) return true;
            else aux = aux->prox;
        }
        return false;
    }

    const T& at(int i) const
    {
        nodo* aux = primo;
        for(int j=0; j<i; j++)
        {
            if(aux) aux = aux->prox;
            else return NULL;
        }
        if(aux) return aux->info;
        else return NULL;
    }

    int size() const
    {
        int i = 0;
        nodo* aux = primo;
        while(aux){
            i++;
            aux = aux->prox;
        }
        return i;
    }

    bool isEmpty() const
    {
        if(!primo) return true;
        else return false;
    }

    void clear()
    {
        while(primo)
        {
            removeFirst();
        }
    }
};

#endif //dbList_H
