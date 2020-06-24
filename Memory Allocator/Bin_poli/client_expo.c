#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "header.h"
main()
{
	int t=0,S,T,j=0;
	srand(time(0));
	void* temp_ptr;
	struct request_node* dellocation_list_head=NULL;
	struct request_node* newnode;
	struct request_node* prev;
	while(t<20)
	{
		S=((rand_expo()%bin_size)+1);
		T=((rand_expo()%20)+1);
		temp_ptr=alloc_bin(S);
		newnode=(struct request_node*)malloc(sizeof(struct request_node));
		newnode->next=dellocation_list_head;
		dellocation_list_head=newnode;
		newnode->time=t+T;
		newnode->ptr=temp_ptr;
		for(struct request_node* i=dellocation_list_head;i != NULL;i=i->next)
		{
			if((i->time) == t)
			{
				free_bin(i->ptr);
				if(i==dellocation_list_head)
					dellocation_list_head=i->next;
				else				
					prev->next=i->next;
				free(i);
			}
			prev=i;
		}
		t=t+1;
	}
}
