#include "node.hpp"
#include <iostream>


template<typename T>
class list
{
private:
    node<T> *head;

public:
    void initialize(T val,int pri=NORMAL)
    {
        head = new node<T>(val,pri);
    }

    void initialize(node<T> *t)
    {
        head = t;
    }

    void insert(T tmp,int pri=NORMAL)
    {
        if(head==nullptr)
            initialize(tmp);
        else
        {
            head=head->insert(tmp,pri);
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
    }

    ~list()
    {
        while(head!=nullptr)
        {
            head=head->destroy();
        }
    }
};
