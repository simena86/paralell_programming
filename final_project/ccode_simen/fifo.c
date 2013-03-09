/*
 * fifo.c
 *
 *  Created on: Dec 1, 2012
 *      Author: sverre
 */


/******** C Program For Impelmetation Of Queue ***********/


#include "fifo.h"

int full()
{
	if (s.rear == MAXSIZE)
		return(1);
	else
		return(0);
}
int empty()
{
	if (s.front == s.rear + 1)
		return(1);
	else
		return(0);
}

void add(int x)
{

	if(full() == 1)
	{
		printf("\n\nQueue Full\n");
	}
	else
	{
		s.rear = s.rear + 1;
		s.queue[s.rear] = x;
		if(s.rear == 1)
			s.front ++;
	}
}

void delete()
{
char ch;
	{
	if(empty() == 1)
	{
	//printf("\n\nQueue Empty\n");
	}
	else
	{
	//	printf("% d Has Been Deleted!\n",s.queue[s.front]);
		s.front = s.front +1;
	}
	}
}

void display()
{
	int i;
	//clrscr();
	if(empty () == 1)
	printf("\nQueue Empty!!");
	else
	{
		printf("\nDisplaying Queue\n");
		for(i = s.front;i<=s.rear;i++){
			printf("%d\n",s.queue[i]);
		}
	}
}
