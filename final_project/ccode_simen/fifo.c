#include "fifo.h"

void init_fifo(){
	
	first = (node*)malloc(sizeof(node));
	last = (node*)malloc(sizeof(node));
	first->next = NULL;
	first->prev = NULL;
	last->next = NULL;
	last->prev = NULL;
}

void pop_first(){
	
	if(first->next == NULL){
		puts("ERROR: Queue is empty");
		return;
	}
	curr = first->next;
	first->next = curr->next;
 	free(curr);
}

void put_last(int data){

	last->next = (node *)malloc(sizeof(node));
	
	curr = last->next;
	curr->prev = last;
	last = last->next;
	last->data = data;
	last->next = NULL;

	if(first->next == NULL)
		first->next = last; 
}

int get_data_first_element(){

	curr = first->next;
	return curr->data;
}

int queue_empty(){
	
	if(first->next == NULL){
		return 1;
	}
	else{
		return 0;
	}
}

void print_queue(){
	
	if(first->next == NULL){
                puts("Can't print queue. Queue is empty");
		return;
        }
        print(first->next);
}

void print(node *pointer){

        if(pointer == NULL){
                return;
        }
        printf("%d \n",pointer->data);
        print(pointer->next);
}


