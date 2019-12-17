#include "monitor.h"
#include <iostream>
#define NORMAL 0
#define VIP 1


template<typename T>
class node
{
private:
    T value;
    int priority;
    node *next;

public:

    node(T tmp, int pri=NORMAL)
    {
        value=tmp;
        priority=pri;
        next=nullptr;
    }

    node *insert_node(T tmp, int pri)
    {
        node *new_node=new node<T>(tmp,pri);
        if(next==nullptr)
        {
            next=new_node;
        }
        else
        {
            node *t= next;
            next=new_node;
            new_node->next=t;
        }
        return new_node;
        
    }
    node *insert_to_the_beggining(T tmp, int pri)
    {
        node *new_node=new node<T>(tmp,pri);
        new_node->next=this;
        return new_node;
    }

    node *print()
    {
        std::cout<<value;
        return next;
    }

    node *pop(node **desired)
    {
        node *ret=this->next;

        this->next=nullptr;

        *desired=this;

        return ret;
    }

    node *destroy()
    {
        node *tmp=this->next;
        delete this;
        return tmp;
    }

};


