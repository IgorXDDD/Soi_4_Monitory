#include "list.hpp"
#define MAX_BUFER 5


class my_monitor : Monitor
{
private:
	list<std::string> buffer;
	int count;
	Condition full,empty;

public:
	node<std::string> *buff_remove() // take a string from buffer
	{
		if(count == 0)
			wait(empty);
		count--;
		node<std::string> *tmp=buffer.pop();
		if(count==MAX_BUFER)
			signal(full);
        leave();
        return tmp;		
	}

	void buff_enter(std::string s,int p) // enter value to the buffer
	{
        if (count==MAX_BUFER)
            wait(full);
        buffer.insert(s,p);
        count++;
        if(count==1)
            signal(empty);
        leave();
	}

	my_monitor()
	{
		count=0;
	}


};
