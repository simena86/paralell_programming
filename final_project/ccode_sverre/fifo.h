#ifndef _FIFO_
#define _FIFO_

#include "headers.h"
#include<string.h>
#define MAXSIZE 100000000

struct st
{
	int front;
	int rear;
	int queue[MAXSIZE];
};

struct st s;



int empty();
int full();
void add(int x);
void delete();
void display();

#endif
