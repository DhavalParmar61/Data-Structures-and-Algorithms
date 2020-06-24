#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "header.h"

void main()
{	
	initialize_SPheap_allocator();

	int t=0,S,T,j=0;
	srand(time(0));
	void* temp_ptr;
	struct request_node* dellocation_list_head=NULL;
	struct request_node* newnode;
	struct request_node* prev;
	while(t<2000)
	{
		S=((rand_expo()%1900)+100);
		//printf("\n %d ",S);
		T=((rand_expo()%2000)+1);
		//printf(" %d ",T);
		temp_ptr=alloc(S);
		newnode=(struct request_node*)malloc(sizeof(struct request_node));
		newnode->next=dellocation_list_head;
		dellocation_list_head=newnode;
		newnode->time=t+T;
		newnode->ptr=temp_ptr;
		prev=dellocation_list_head;
		/*for(struct request_node* i=dellocation_list_head;i != NULL;i=i->next)
		{
			printf("\n %p %d",i->ptr,i->time);
		}*/
		for(struct request_node* i=dellocation_list_head;i != NULL;i=i->next)
		{
			if((i->time) == t)
			{
				free_alloc(i->ptr);
				if(i==dellocation_list_head)
				{
					dellocation_list_head=i->next;
					prev=i->next;
				}
				else				
					prev->next=i->next;
				free(i);
			}
			else
				prev=i;
		}
		t=t+1;
		if(t%200 ==0)
		{
			printf("\ntime %d",t);
			print_sheap_data();
		}
	}
}


