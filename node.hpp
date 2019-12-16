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

    node *insert(T tmp,int pri)
    {
        node *curr=this;
        node *inserted = new node<T>(tmp,pri);
        if(pri==NORMAL)
        {
            /*if normal user go to the end of list and make added node its new end*/
            while(curr->next!=nullptr)
            {
                curr=curr->next;
            }
            curr->next=inserted;
            return this;
        }
        else // if VIP find the last vip message and insert behind it 
        {
            if(curr->priority==NORMAL) // if priority of 1st is normal then vip must be on the beginning
            {
                inserted->next=this;
                return inserted;
            }
            else
            {
                while (curr->next->priority == VIP)
                {
                    curr=curr->next;
                }
                inserted->next=curr->next;
                curr->next=inserted;                
                return this;
            }
        }
    }

    node *insert(node *t)
    {
        node *curr=this;
        if(this==nullptr)
        {
            return t;
        }
        if(t==nullptr)
        {
            return this;
        }
        if(t->priority==NORMAL)
        {
            /*if normal user go to the end of list and make added node its new end*/
            while(curr->next!=nullptr && curr->next!=nullptr)
            {
                curr=curr->next;
            }
            curr->next=t;
            return this;
        }
        else // if VIP find the last vip message and insert behind it 
        {
            if(curr->priority==NORMAL) // if priority of 1st is normal then vip must be on the beginning
            {
                t->next=this;
                return t;
            }
            else
            {
                if(curr->next==nullptr)
                {
                    curr->next=t;
                    return this;
                }
                while (curr->next!=nullptr && curr->next->priority == VIP)
                {
                    curr=curr->next;
                }
                t->next=curr->next;
                curr->next=t;                
                return this;
            }
        }
    }
    node *print()
    {
        if(priority==VIP)
        {
            std::cout<<"(VIP):";
        }
        else
        {
            std::cout<<"(USER):";
        }
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


