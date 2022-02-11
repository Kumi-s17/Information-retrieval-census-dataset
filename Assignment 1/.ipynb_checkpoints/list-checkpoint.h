#ifndef LISTH
#define LISTH


struct list{
	struct business *head;
	struct business *foot; 
};                 

struct list *create_empty_list();
struct list *insert_node(struct list *list);
void free_list(struct list* list);


#endif