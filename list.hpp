#include "node.hpp"
#include <iostream>


template<typename T>
class list
{
private:
    node<T> *head;
    node<T> *last; //wstawianie normalnych
    node<T> *last_pri; //wstawianie vipow

public:
    void initialize(T val,int pri=NORMAL)
    {
        head = new node<T>(val,pri);
        last=head;
        if(pri ==VIP)
            last_pri=head;

    }

    void initialize(node<T> *t)
    {
        head = t;
        last_pri=t;
        last=t;
    }

    void insert(T tmp,int pri=NORMAL)
    {
        if(head==nullptr)
            initialize(tmp,pri);
        else
        {
            if(pri==NORMAL)
            {
                last=last->insert_node(tmp,pri);
            }
            else // jezeli vip
            {
                if(last_pri==nullptr) // jezeli nie ma vipa w kolejce
                {
                    head=head->insert_to_the_beggining(tmp,pri);
                    last_pri=head;
                }
                else
                {
                    last_pri=last_pri->insert_node(tmp,pri);
                }
            }
        }
    }

    void insert(node<T> *t)
    {
        if(head==nullptr)
            initialize(t);
        else
        {
            head=head->insert(t);
        }
        
    }

    void print()
    {
        node<T> *t;
        t=head;
        while(t)
        {
            t=t->print();
            std::cout<<"\n";
        }
    }

    node<T> *pop()
    {
        node<T> *tmp;
        if(head==nullptr)
        {
            throw("Error! Popping from empty list!");
            return nullptr;
        }
        if(head==last_pri)
        {
            last_pri=nullptr; // jezeli ostatni vip jest pierwsza wiadomoscia to dajemy znac ze bedzie trzeba go spowrotem ustawic
        }
        head=head->pop(&tmp);
        
        return tmp;
    }

    list(T val,int pri=NORMAL)
    {
        initialize(val,pri);
    }
    
    list()
    {
        head=nullptr;
        last_pri=nullptr;
        last=nullptr;
    }

    ~list()
    {
        while(head!=nullptr)
        {
            head=head->destroy();
        }
    }
};
