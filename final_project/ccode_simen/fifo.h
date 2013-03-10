#ifndef _FIFO_
#define _FIFO_

#include "headers.h"

typedef struct node{
    /// members
	int data;
	struct node *next;
	struct node *prev;
}node;

node *curr, *first, *last;

void init_fifo();
void put_last(int data);
void pop_first();
int get_data_first_element();
int queue_empty();
void print_queue();
void print(node *pointer);	//This function is used by the public function print_queue()


#endif /* QUEUE_H_ */
