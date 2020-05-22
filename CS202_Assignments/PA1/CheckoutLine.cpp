#ifndef CheckoutLine_CPP
#define CheckoutLine_CPP
#include "CheckoutLine.h"

//base constructor, init
CheckoutLine::CheckoutLine(int size)
{
	line_size=size;
	time = 0;
}

//destructor
CheckoutLine::~CheckoutLine()
{
	while (!(container1.isEmpty()))
	{
		container1.dequeue();
	}
	while (!(container2.isEmpty()))
	{
		container2.dequeue();
	}
	while(!(containerH.isEmpty()))
	{
		containerH.pop();
	}
}

// join the checkout line
// impliment for both waiting systems
/*  (1). I have preffered using 2 queues one for each line. this is so because while implementing a 
	line we have to keep in mind the first in first out (FIFO) order and FIFO order can easily
	implemented with the help of a queue instead of a stack.

	(2). I have preffered using a stack for the history function because in the history function
	we have to check the lastest customers served and we can do so using a stack which implements
	a last in first out LIFO order. Hence, the latest person served will be at the top of the stack
	we will be able to check his name.*/


bool Compare_waits()
{
	person_node customer;
	CheckoutLine z(10);
	char name = 'a';
	string input_name(1,name);
	int wait = 0;
	for (int i = 0; i < 10; i++)
	{
		z.joinCheckoutLine(input_name,1,1);
		name = name +1;
	}
	for (int i = 0; i < 10; i++)
	{
		z.joinCheckoutLine(input_name,2,1);
		name = name +1;
	}
	z.serveCheckoutLine(1);
	int time1 = z.time;
	for (int i = 0; i < 10; i++)
	{
		z.joinCheckoutLine(input_name,1,1);
		name = name +1;
	}
	for (int i = 0; i < 10; i++)
	{
		z.joinCheckoutLine(input_name,2,1);
		name = name +1;
	}
	z.serveCheckoutLine(2);
	int time2 = z.time;
	if (time1 == time2)
	{
		return true;
	}
	else
	{
		return false;
}

bool CheckoutLine::joinCheckoutLine(string name, int line_number, int type)
{
	int wait = container1.length() + container2.length() + 1;
	person_node customer(name,wait,time);
	if (line_number == 1 && (container1.length() < line_size))
	{
		container1.enqueue(customer);
		return true;
	}
	else if (line_number == 2 && (container2.length() < line_size))
	{
		container2.enqueue(customer);
		return true;
	}
	return false;
}

// impliment serving strategy for both waiting systems
void CheckoutLine::serveCheckoutLine(int type)
{
	person_node line1;
	person_node line2;
	person_node served;
	if (type == 1)
	{
		time = 0;
		while(!(container1.isEmpty()) || !(container2.isEmpty()))
		{
			if (container1.isEmpty() && !(container2.isEmpty()))
			{
				served = container2.dequeue();
				served.time_stamp = time++;
				containerH.push(served);
			}
			else if (container2.isEmpty() && !(container1.isEmpty()))
			{
				served = container1.dequeue();
				served.time_stamp = time++;
				containerH.push(served);
			}
			else
			{
				line1 =	container1.front();	
				line2 =	container2.front();
				if (line1.wait_stamp < line2.wait_stamp)
				{
					served = container1.dequeue();
					served.time_stamp = time++;
					containerH.push(served);
				}
				else
				{
					served = container2.dequeue();
					served.time_stamp = time++;
					containerH.push(served);
				}
			}
		}
	}
	else if (type == 2)
	{
		time = 0;
		while(!(container1.isEmpty()) || !(container2.isEmpty()))
		{
			if (container1.isEmpty() && !(container2.isEmpty()))
			{
				served = container2.dequeue();
				served.time_stamp = time++;
				containerH.push(served);
			}
			else if (container2.isEmpty() && !(container1.isEmpty()))
			{
				served = container1.dequeue();
				served.time_stamp = time++;
				containerH.push(served);
			}
			else
			{
				served = container1.dequeue();
				served.time_stamp = time++;
				containerH.push(served);

				served = container2.dequeue();
				served.time_stamp = time++;
				containerH.push(served);
			}
		}
	}
}

// return a vector of strings with the names of last n people served
vector<string> CheckoutLine::history(int n)
{
	vector<string> hist;
	person_node customer;
	while(n)
	{
		customer = containerH.pop();
		hist.push_back(customer.name);
		n--;
	}
	return hist;
}

#endif