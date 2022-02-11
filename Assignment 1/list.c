#include "list.h"
#include "data.h"
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>

//create a new list
struct list *create_empty_list(){
	struct list *list;
	list = malloc(sizeof(*list));
	assert(list);
	list -> head = list -> foot = NULL;
	return list;
}                                                              
                           
//add a new business node to the list
struct list *insert_node(struct list *list){
	struct business *new_business;
	new_business = malloc (sizeof(*new_business));
	assert(new_business && list);
	new_business -> dataptr = NULL;
	new_business -> next = NULL;
	
	
	//if it is the first element to be inserted into the list
	if(list -> head == NULL){
		list -> head = list -> foot = new_business;
	}
	else{
		list -> foot -> next = new_business;
		list -> foot = new_business;
	}
	
	return list;
	
}

//free list
void free_list(struct list* list){
	struct business *current, *prev;
	assert(list);
	current = list -> head;
	while(current != NULL){
		prev = current;
		current = current -> next;
		free_data(prev);
		free(prev);
	}
	free(list);	
} 



   
