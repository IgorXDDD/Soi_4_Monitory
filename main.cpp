#include "my_monitor.hpp"
#include <iostream>
#include <vector>
#include <unistd.h> 
#include <thread>
#include <list>
#include <ctime>
#define SLEEP_TIME 1


list<std::string> chat;

struct msg
{
    std::string mes;
    int pri;
};
my_monitor *mon = new my_monitor();


std::string add_time(std::string m, std::string un,int i)
{
    tm time_sent;
    time_t t = time(NULL);
    time_sent = *localtime(&t);
    m+="nr: [";
    m+=std::to_string(i);
    m+="] - ";
    std::string new_msg;
    new_msg=  std::to_string(time_sent.tm_hour)+":"+std::to_string(time_sent.tm_min)+":"+std::to_string(time_sent.tm_sec);
    new_msg+=" ";
    new_msg+=m;
    new_msg+=un;
    new_msg+=".";
    return new_msg;
}


void *producer(std::string msg_text,int pri,std::string username)
{
    int i=1;
    while(true)
    {
        mon->buff_enter(add_time(msg_text,username,i),pri);
        i++;
        sleep(1);
    }
    return nullptr;
}

void * consumer()
{
    while (true)
    {
        sleep(1);
        mon->buff_remove()->print();
        puts("\n");
        //chat.insert(mon->buff_remove());
    }
    return nullptr;
}


int main(int argc,char *argv[])
{

    int vt=6,nt=5;
    if(argc>1)
    {
        nt=atoi(argv[1]);
        vt=atoi(argv[2]);
    }


    std::thread normals[nt];
    std::thread vips[vt];

    for(int i=0;i<nt;++i)
    {
        normals[i]= std::thread(producer,"WIADOMOSC zwykla ",NORMAL," NORMALNY UZYTKOWNIK nr "+std::to_string(i+1));
    }

    for(int i=0;i<vt;++i)
    {
        vips[i]= std::thread(producer,"VIP WIADOMOSC ",VIP," VIPOWY UZYTKOWNIK nr "+std::to_string(i+1));
        //vips[i].join();
    }


    std::thread reader_thread(consumer);
    reader_thread.join();



    for(int i=0;i<nt;++i)
    {
        normals[i].join();
    }
    
    for(int i=0;i<vt;++i)
    {
        vips[i].join();
    }
    


    return 0;
}