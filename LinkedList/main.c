#include <stdio.h>
#include <stdlib.h>


/*******************************************************/
/*******************************************************/
/* LinkedList Implementation */

/*************
* [STRUCTS]  *
* LinkedList *
* Node       *
**************/

struct Node{
	int data;
	struct Node *next;
};

struct LinkedList{
	struct Node *root;
	int length;
};

void add_to_node(struct Node *r, struct Node *n){
	r->next = n;
}

void list_add(struct LinkedList *list, struct Node *n){
	
	struct Node *ptr;
	
	ptr = list->root;
	
	while( ptr->next != NULL){
		ptr = ptr->next;
	}
	
	add_to_node(ptr,n);
	
	list->length++;
}

struct Node *list_get(struct LinkedList *list, int n){
	
	struct Node *ptr;
	
	ptr = list->root;
	
	int i=0;
	while(ptr->next != NULL){
		if(i==n){
			return ptr;
		}else{
			i++;
			ptr = ptr->next;
		}
	}
	
	if(i==n)
		return ptr;
	
	return NULL;
}

int list_remove(struct LinkedList *list, int n){
	struct Node *ptr;
	struct Node *last;
	
	ptr = list_get(list,n);
	last = list_get(list,n-1);
	
	if(ptr != NULL && last != NULL){
		last->next = ptr->next;
		list->length--;
		return 1;
	}else{
		return 0;
	}
}

struct Node *create_node(int data){
	struct Node *ptr = malloc(sizeof(struct Node)); 
	ptr->data = data;
	ptr->next = NULL;
	return ptr;
}


struct LinkedList *CreateLinkedList(){
	struct LinkedList *list = malloc(sizeof(struct LinkedList));
	struct Node *root = create_node(0);
	
	list->root = root;
	list->length = 0;
	
	return list;
}

/*******************************************************/
/*******************************************************/

void print_nodes(struct Node *n){
	printf("    %d\n",n->data);
	if(n->next == NULL){
		printf("    end\n");
	}else{
		print_nodes(n->next);
	}
}

void print_node(struct Node *n){
	if(n != NULL){
		printf("Node:\n");
		printf("  data = %d\n", n->data);
		if(n->next != NULL){
			printf("  next = *Node\n");
		}else{
			printf("  next = NULL\n");
		}		
	}else{
		printf("Node:\n");
		printf("  NULL\n");
	}
}

void print_ll(struct LinkedList *list){
	printf("LinkedList\n");
	printf("  length: %d\n",list->length);
	printf("  nodes:\n");
	print_nodes(list->root);
}

int main( int argc, char *argv[] )
{
	
	struct LinkedList *list = CreateLinkedList();
	
	list_add(list,create_node(33));
	list_add(list,create_node(66));
	list_add(list,create_node(99));
	
	print_ll(list);
	
	list_remove(list,3);
	
	print_ll(list);
	
	list_add(list,create_node(31));
	
	print_ll(list);
	
    return 0;
}