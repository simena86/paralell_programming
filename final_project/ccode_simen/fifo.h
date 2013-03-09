#include<stdio.h>
#include<string.h>
#define MAXSIZE 5

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

