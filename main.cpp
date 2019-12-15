#include "my_monitor.hpp"
#include <iostream>


my_monitor mon;

struct msg
{
    std::string mes;
    int pri;
};




void *producer(void *args)
{
    msg tmp=*((msg *)args);
    
    while(true)
    {
        mon.buff_enter(tmp.mes,tmp.pri);
    }
}

void * consumer(void *args)
{



}



int main()
{

/*
    list<std::string> test_list("dupa",NORMAL);
    list<std::string> rlist;

    test_list.insert("test msg",VIP);
    test_list.insert("test msg 1",VIP);
    test_list.insert("test msg3",NORMAL);
    test_list.insert("test msg4",VIP);
    test_list.print();
    try
    {
    rlist.insert(test_list.pop());
    rlist.insert(test_list.pop());
    rlist.insert(test_list.pop());
    rlist.insert(test_list.pop());
    rlist.insert(test_list.pop());
    std::cout<<"RLIST:\n";
    rlist.print();
    rlist.insert(test_list.pop());
    }
    catch(const char* error)
    {
        std::cout<<error<<"\n";
    }
    */
   
    
    
    

    return 0;
}