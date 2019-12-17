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
    m+="]";
    std::string new_msg;
    new_msg=  std::to_string(time_sent.tm_hour)+":"+std::to_string(time_sent.tm_min)+":"+std::to_string(time_sent.tm_sec);
    new_msg+=" -";
    new_msg+=un;
    new_msg+=": ";
    new_msg+=m;
    new_msg+=".\"";
    return new_msg;
}


void *producer(std::string msg_text,int pri,std::string username)
{
    int i=1;
    while(true)
    {
        mon->buff_enter(add_time(msg_text,username,i),pri);
        i++;
        sleep(SLEEP_TIME);
    }
    return nullptr;
}

void * consumer()
{
    while (true)
    {
        sleep(SLEEP_TIME);
        mon->buff_remove()->print();
        printf("\n");
        //chat.insert(mon->buff_remove());
    }
    return nullptr;
}


void scenarios(int i);

int nt,vt;

int main(int argc,char *argv[])
{

    int i;
    if(argc>1)
    {
        i=atoi(argv[1]);
    }

    scenarios(i);

    std::thread *normals = new std::thread[nt];
    std::thread *vips = new std::thread[vt];
    

    for(int i=0;i<nt;++i)
    {
        normals[i]= std::thread(producer,"\"WIADOMOSC ",NORMAL," USER nr: "+std::to_string(i+1));
        usleep(10);
    }

    for(int i=0;i<vt;++i)
    {
        vips[i]= std::thread(producer,"\"WIADOMOSC ",VIP," VIP  nr "+std::to_string(i+1));
        usleep(10);
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


void scenarios(int i)
{
    switch (i)
    {
        case 1: //tyle samo vipow co normalnych
        {   
            puts("----------Scenariusz z tyloma samo vipow co normalnych----------");
            puts("----------Nastepuje przepelnienie bufora (caly czas)----------");
            vt=5;
            nt=5;
            break;
        }
        case 2: // sami normalni
        {
            puts("----------Scenariusz z samymi normalnymi uzytkownikami----------");
            nt=5;
            vt=0;
            break;
        }
        case 3:
        {
            puts("----------Scenariusz z samymi prioretytowymi uzytkownikami----------");
            nt=0;
            vt=5;
            break;
        }
        case 4: // sami normalni
        {
            puts("----------Scenariusz z tyloma samymi Vipami co normalnymi  bez przepelnienia----------");
            nt=1;
            vt=1;
            break;
        }
        case 5: // sami normalni
        {
            puts("----------Scenariusz z samymi normalnymi uzytkownikami bez przepelnienia----------");
            nt=2;
            vt=0;
            break;
        }
        case 6: 
        {
            puts("----------Scenariusz z samymi Vipowymi uzytkownikami bez przepelnienia----------");
            nt=0;
            vt=2;
            break;
        } 
        
        default:
        {   
            puts("----------3 normalnych, 1 vip - uzytkownikow tyle ile wynosi rozmiar bufora----------");
            nt=3;
            vt=1;
            break;
        }
            
    }

}