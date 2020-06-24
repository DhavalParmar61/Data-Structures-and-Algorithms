#include <stdio.h>
#include <stdlib.h>
#include "header.h"

struct bin_node* allocated_bin_head; 
struct bin_node* deleted_bin_head;
int bin_size;
int max_no_bins;
int no_allocated_bin,bin_alloc_request,bin_dealloc_request;
int total_request_size;
char bin[256*1024*1024];
double time_alloc,time_free;


struct node *divide_poly(struct node *h1,struct node *h2)
{
	struct node *header1=h1,*header2=h2,*ptr1,*ptr2,*ptrq,*ptr,*prevq=NULL,*prev,*quotient=NULL;
	int z,j=0;	
	
	while(((header2->i)<=(header1->i))&&(header1!=NULL)&&(header2!=NULL))
	{
		ptr1=header1;
		ptr2=header2;
		ptrq=(struct node*)alloc_bin(sizeof(struct node));
		ptrq->left=prevq;
		if(prevq != NULL)
			prevq->right=ptrq;
		if(prevq == NULL)
			quotient=ptrq;
		prevq=ptrq;
		ptrq->i=((ptr1->i)-(ptr2->i));
		ptrq->a=((ptr1->a)/(ptr2->a));
		
		for(ptr2=header2;ptr2!=NULL;ptr2=(ptr2->right))
		{
			z=0;
			for(ptr1=header1;(ptr1!=NULL)&&((ptr1->i)>=((ptrq->i)+(ptr2->i)));ptr1=(ptr1->right))
			{
				if(((ptrq->i)+(ptr2->i))==(ptr1->i))
				{
					(ptr1->a)=(ptr1->a)-((ptrq->a)*(ptr2->a));
					if((ptr1->a)==0)
					{
						if(ptr1==header1)
						{
							if((header1->right)!=NULL)
							{
								header1=ptr1->right;
								header1->left=NULL;
								free_bin(ptr1);
							}
							else
							{
								header1->i=-1;
								header1->a=0;
							}
						}
						else
						{
							(ptr1->left)->right=ptr1->right;
							(ptr1->right)->left=ptr1->left;
							free_bin(ptr1);
						}
					}
					z=1;
				}
				prev=ptr1;
									
			}

			if(z==0)
			{
				ptr=(struct node*)alloc_bin(sizeof(struct node));
				if(ptr1!=header1)
				{
					ptr->right=prev->right;
					ptr->left=prev;
					prev->right=ptr;
					if((ptr->right)!=NULL)
						(ptr->right)->left=ptr;
				}
				else			
				{
					header1=ptr;
					ptr->right=ptr1;
					ptr->left=NULL;
					ptr1->left=ptr;
				}
				ptr->i=((ptrq->i)+(ptr2->i));
				ptr->a=-((ptrq->a)*(ptr2->a));
			}	
		}
		j=1;
	}
	if(j==1)
	{
		ptrq->right=NULL;
	}

	printf("\nQuotient");
	output_poly(quotient);

	printf("\n\nReminder");
	output_poly(header1);

	for(ptr1=header1;ptr1!=NULL;ptr1=ptr1->right)
	{
		free_bin(ptr1);
	}

	for(ptr1=quotient;ptr1!=NULL;ptr1=ptr1->right)
	{
		free_bin(ptr1);
	}

	for(ptr1=header2;ptr1!=NULL;ptr1=ptr1->right)
	{
		free_bin(ptr1);
	}
}

struct node *input_poly()
{
	struct node *ptr1,*header,*prev=NULL;
	char c='0';
	int j=0;
	while(c != '\n')
	{
		ptr1=(struct node*)alloc_bin(sizeof(struct node));
		if(j==0)
			header=ptr1;
		scanf(" (%d,%f)%c",&(ptr1->i),&(ptr1->a),&c);
		if((ptr1->a)!=0)
		{
			ptr1->left=prev;
			if(j!=0)
				prev->right=ptr1;
			prev=ptr1;
			if(c == '\n')
				ptr1->right=NULL;
		}
		else
		{
			free_bin(ptr1);
			if(c == '\n')
				prev->right=NULL;
		}
		j=1;
	}
	return(header);
}

void output_poly(struct node *header)
{
	struct node *ptr1;
	for(ptr1=header;ptr1!=NULL;ptr1=ptr1->right)
	{
		printf("\n(%d,%f)",(ptr1->i),(ptr1->a));
	}
}


void initialize_bin(int size)
{
	bin_size=size;
	max_no_bins=(256*1024*1024/size);
	allocated_bin_head=NULL;
	struct bin_node* deleted_bin_head=NULL;
	no_allocated_bin=0;
	bin_alloc_request=0;
	bin_dealloc_request=0;
	total_request_size=0;
}

void* alloc_bin(int size)
{
	static int indx=0;
	struct bin_node* temp;
	bin_alloc_request++;
	total_request_size += size;
	if(no_allocated_bin == max_no_bins)
	{
		printf("Memory Full");
		return(NULL);
	}
	if (size>bin_size)
	{
		printf("Demanded Memory size is more than bin size");
		return(NULL);
	} 
	if(deleted_bin_head != NULL)
	{
		temp=deleted_bin_head->next;
		deleted_bin_head->next=allocated_bin_head;
		allocated_bin_head=deleted_bin_head;
		deleted_bin_head=temp;
		no_allocated_bin++;
		return(allocated_bin_head->ptr);	
	}
	else
	{
		struct bin_node* newnode=(struct bin_node*)malloc(sizeof(struct bin_node));
		newnode->next=allocated_bin_head;
		allocated_bin_head=newnode;
		newnode->addr=indx;
		newnode->ptr=&bin[indx];
		indx=indx+bin_size;
		no_allocated_bin++;
		return(newnode->ptr);
	}
}

void free_bin(struct node* ptr1)
{
	struct bin_node* ptr=(struct bin_node*)ptr1;
	struct bin_node* i=allocated_bin_head;
	struct bin_node* prev;
	bin_dealloc_request++;
	while(i!=NULL && ((i->ptr)!= ptr))
	{
		prev=i;
		i=i->next;
	}
	if(i == NULL)
	{
		printf("No such bin exist");
	}
	else
	{
		if(i == allocated_bin_head)
			allocated_bin_head=i->next;
		else
			prev->next=i->next;
		i->next=deleted_bin_head;
		deleted_bin_head=i;
		no_allocated_bin--;
	} 
}
void print_bin_data()
{
	float int_frag;
	int_frag=((float)(bin_alloc_request*bin_size)-total_request_size)/(total_request_size);
	printf("\nInternal Fragmentation : %f",int_frag);
	printf("\nNumber of allocated bins : %d",no_allocated_bin,bin_dealloc_request);	
	printf("\nNumber of bin allocation request : %d",bin_alloc_request);
	printf("\nNumber of bin deallocation request : %d",bin_dealloc_request);
}

