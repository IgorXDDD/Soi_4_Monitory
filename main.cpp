#include "my_monitor.hpp"
#include <iostream>
#include <vector>


my_monitor mon;
list<std::string> chat;

struct msg
{
    std::vector<std::string> mes_list;
    int pri;
};




void *producer(void *args)
{
    msg tmp=*((msg *)args);
    std::string mini_buf;

    //assert(!tmp.mes_list.empty());
    tmp.mes_list.front() = std::move(tmp.mes_list.back());
    mini_buf=tmp.mes_list[tmp.mes_list.size()];
    tmp.mes_list.pop_back();

    while(true && mini_buf!="")
    {
        mon.buff_enter(mini_buf,tmp.pri);
        mini_buf="";
    }
}

void * consumer(void *args)
{
    while (true)
    {
        chat.insert(mon.buff_remove());
    }
}



int main()
{

/*
    list<std::string> test_list("1 test nr 1",NORMAL);
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
    pthread_t prodA, consA, prodB,consB;
    msg t1;
    t1.mes_list.push_back("wiadomosc 1");
    t1.pri=NORMAL;
    msg t2;
    t2.mes_list.push_back("DUPAXXD");
    t2.pri=NORMAL;
  pthread_create(&prodA,NULL,producer, &t1);
  pthread_create(&prodB,NULL,producer, &t2); 
  pthread_create(&consA,NULL,consumer,NULL);
  chat.print();

    
    
    

    return 0;
}