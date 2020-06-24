#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "header.h"
#define MEMORY 256*1024*1024
#define ASL_size 56

struct ASL_element ASL[ASL_size];
struct Alloc_list allocated_space;
char memory[MEMORY];
float intr_frag;
int no_alloc_req,no_dealloc_req,no_splits,no_recomb,no_alloc;
double sum_request,sum_alloc,current_area,time_alloc,time_free;
void* strt_memory=&memory; 
int n=ASL_size;
double lambda=0.001;


struct node *divide_poly(struct node *h1,struct node *h2)
{
	struct node *header1=h1,*header2=h2,*ptr1,*ptr2,*ptrq,*ptr,*prevq=NULL,*prev,*quotient=NULL;
	int z,j=0;	
	
	while(((header2->i)<=(header1->i))&&(header1!=NULL)&&(header2!=NULL))
	{
		ptr1=header1;
		ptr2=header2;
		ptrq=(struct node*)alloc(sizeof(struct node));
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
								free_alloc(ptr1);
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
							free_alloc(ptr1);
						}
					}
					z=1;
				}
				prev=ptr1;
									
			}

			if(z==0)
			{
				ptr=(struct node*)alloc(sizeof(struct node));
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
		free_alloc(ptr1);
	}

	for(ptr1=quotient;ptr1!=NULL;ptr1=ptr1->right)
	{
		free_alloc(ptr1);
	}

	for(ptr1=header2;ptr1!=NULL;ptr1=ptr1->right)
	{
		free_alloc(ptr1);
	}
}

struct node *input_poly()
{
	struct node *ptr1,*header,*prev=NULL;
	char c='0';
	int j=0;
	while(c != '\n')
	{
		ptr1=(struct node*)alloc(sizeof(struct node));
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
			free_alloc(ptr1);
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







void initialize_SPheap_allocator()
{
	int i;
	ASL[n-1].size=1;
	ASL[n-2].size=2;
	for(i=n-3;i>=0;i=i-2)
	{
		if (i == n-3)
			ASL[i].size=3*ASL[i+2].size;
		else
			ASL[i].size=3*ASL[i+3].size;
		ASL[i].head=NULL;
		ASL[i].tail=NULL;
		ASL[i-1].size=2*ASL[i+1].size;
		ASL[i-1].head=NULL;
		ASL[i-1].tail=NULL;
	}

	for(i=0;i<n;i++)
	{
		ASL[i].head=NULL;
		ASL[i].tail=NULL;
		if(i%2 == 0)
			ASL[i].kval=(int)(log(ASL[i].size)/log(2));
		else
			ASL[i].kval=(int)(log((ASL[i].size)/3)/log(2));
	}
	
	struct ASL_node* new_node=(struct ASL_node*)malloc(sizeof(struct ASL_node));
	ASL[0].head=new_node;
	ASL[0].tail=new_node;
	new_node->next=NULL;
	new_node->prev=NULL;
	new_node->strt=0;
	new_node->buddy_indx=-1;
	new_node->parent_indx=-1;
	new_node->type=-1;
	new_node->tag=0;	
	
	(allocated_space).head=NULL;
	(allocated_space).tail=NULL;

	no_alloc_req=0;
	no_dealloc_req=0;
	no_alloc=0;
	no_splits=0;
	no_recomb=0;
	sum_request=0;
	sum_alloc=0;
}

void* alloc(int size)
{
	int k=(int)ceil((log(size)/log(2)));
	float per_area;
	struct ASL_node* i;
	int indx=(n)-(2*k)+1;
	void* ptr=NULL;
	no_alloc_req++;

	while(indx>=0)
	{	
		if(ASL[indx].head == NULL)		
		{
			indx=indx-1;
		}
		else
		{
			i=ASL[indx].head;
			while(i!=NULL)
			{
				if(i->tag == 0)
					break;
				else
					i=i->next;			
			}
			if(i!=NULL)
				break;
			else
				indx=indx-1;
		}
	}
	if((indx == -1) && ((ASL[0].head)->tag!=0))
	{	
		printf("Allocation Failed.");
		per_area=(current_area/(256*1024*1024));
		printf("(%d,%f),size,per_area");
		exit(0);
	}
	while(1)
	{
		//printf("\n%d %d %d %d\n",indx,ASL[indx].size,(ASL[indx].head)->strt,size);
		if(indx%2 == 0)
		{	
			if(((ASL[indx].size)/4) >= size || ((ASL[indx].size)*3/4) >= size)
			{
				indx=split1(indx,size,i);
				no_splits++;
				i->tag=1;
				i=ASL[indx].head;
				while(i!=NULL)
				{
					if(i->tag == 0)
						break;
					else
						i=i->next;			
				}
			}
			else
			{
				ptr=asign(indx,i);
				i->tag=1;
				no_alloc++;
				sum_request=sum_request+size;
				sum_alloc=sum_alloc+ASL[indx].size;
				current_area=current_area+ASL[indx].size;
				break;
			}
		}
		else
		{
			if(((ASL[indx].size)/3) >= size || ((ASL[indx].size)*2/3) >= size)
			{
				indx=split2(indx,size,i);
				no_splits++;
				i->tag=1;
				i=ASL[indx].head;
				while(i!=NULL)
				{
					if(i->tag == 0)
						break;
					else
						i=i->next;			
				}
			}
			else
			{
				ptr=asign(indx,i);
				i->tag=1;
				no_alloc++;
				sum_request=sum_request+size;
				sum_alloc=sum_alloc+ASL[indx].size;
				current_area=current_area+ASL[indx].size;
				break;
			}
		}
		
	}

	return(ptr);	
}

void* asign(int indx,struct ASL_node* i)
{
	void* ptr=&memory[i->strt];
	add_allocated_space(indx,ptr,i);
	return(ptr);
}

int split1(int indx,int size,struct ASL_node* i)
{
	int strt=i->strt;
	struct ASL_node* new_node1=(struct ASL_node*)malloc(sizeof(struct ASL_node));
	new_node1->strt=strt;
	new_node1->type=3;
	new_node1->next=NULL;
	new_node1->buddy_indx=indx+4;
	new_node1->parent_indx=indx;
	new_node1->tag=0;
	new_node1->prev=ASL[indx+1].tail;
	ASL[indx+1].tail=new_node1;
	if(new_node1->prev != NULL)
		(new_node1->prev)->next=new_node1;
	if(ASL[indx+1].head == NULL)
		ASL[indx+1].head=new_node1;

	struct ASL_node* new_node2=(struct ASL_node*)malloc(sizeof(struct ASL_node));
	new_node2->strt=strt+((ASL[indx].size)*3/4);
	new_node2->type=3;
	new_node2->next=NULL;
	new_node2->buddy_indx=indx+1;
	new_node2->parent_indx=indx;
	new_node2->tag=0;
	new_node2->prev=ASL[indx+4].tail;
	ASL[indx+4].tail=new_node2;
	if(new_node2->prev != NULL)
		(new_node2->prev)->next=new_node2;
	if(ASL[indx+4].head == NULL)
		ASL[indx+4].head=new_node2;
	
	
	if((ASL[indx+4].size) >= size)
		return(indx+4);
	else
		return(indx+1);
}

int split2(int indx,int size,struct ASL_node* i)
{
	int strt=i->strt;
	struct ASL_node* new_node1=(struct ASL_node*)malloc(sizeof(struct ASL_node));
	new_node1->strt=strt;
	new_node1->type=1;
	new_node1->next=NULL;
	new_node1->buddy_indx=indx+3;
	new_node1->parent_indx=indx;
	new_node1->tag=0;
	new_node1->prev=ASL[indx+1].tail;
	ASL[indx+1].tail=new_node1;
	if(new_node1->prev != NULL)
		(new_node1->prev)->next=new_node1;
	if(ASL[indx+1].head == NULL)
		ASL[indx+1].head=new_node1;

	struct ASL_node* new_node2=(struct ASL_node*)malloc(sizeof(struct ASL_node));
	new_node2->strt=strt+((ASL[indx].size)*2/3);
	new_node2->type=2;
	new_node2->next=NULL;
	new_node2->buddy_indx=indx+1;
	new_node2->parent_indx=indx;
	new_node2->tag=0;
	new_node2->prev=ASL[indx+3].tail;
	ASL[indx+3].tail=new_node2;
	if(new_node2->prev != NULL)
		(new_node2->prev)->next=new_node2;
	if(ASL[indx+3].head == NULL)
		ASL[indx+3].head=new_node2;

	if((ASL[indx+3].size) >= size)
		return(indx+3);
	else
		return(indx+1);
}

void add_allocated_space(int indx,void* ptr,struct ASL_node* i)
{
	struct Alloc_node* new_node=(struct Alloc_node*)malloc(sizeof(struct Alloc_node));
	if(allocated_space.head == NULL)
	{
		allocated_space.head =new_node;
		allocated_space.tail =new_node;
	}
	else
	{
		(allocated_space.tail)->next =new_node;
		allocated_space.tail =new_node;	
	}

	new_node->addr=i->strt;	
	new_node->indx=indx;
	new_node->next=NULL;	
	new_node->ptr=ptr;
}

void free_alloc(void* ptr)
{
	int indx;
	struct Alloc_node* prev;
	struct Alloc_node* i;
	struct Alloc_node* j;
	no_dealloc_req++;
	i = allocated_space.head;
	while(i != NULL && i->ptr != ptr)
	{
		prev=i;
		i=i->next;		
	}
	current_area=current_area-(ASL[i->indx].size);
	if(i != NULL)
	{
		dealloc(i->indx,i->addr);	
		no_alloc--;
	}
	else
	{
		printf("Allocation does not exist");
	}
	if(i == allocated_space.head)
		allocated_space.head=i->next;	
	else
		prev->next=i->next;
}

void dealloc(int indx,int addr)
{
	if(indx != 0)
	{
	struct ASL_node* i;
	struct ASL_node* j;
	int B_addr;
	i=find(indx,addr);
	if(i->type == 3)
	{
		if((ASL[indx].kval) == (int)(log(ASL[indx].size)/log(2)))
		{
			B_addr=(addr-(3*(ASL[indx].size)));		
		}
		else if((ASL[indx].kval) == (int)(log(ASL[indx].size/3)/log(2)))
		{
			B_addr=(addr+(ASL[indx].size));
		}	
		else
		{
			printf("\nwrong\n");
		}
	}
	else if(i->type == 1)
	{
		B_addr=(addr+(ASL[indx].size));
	}
	else if(i->type == 2)
	{
		B_addr=(addr-(2*(ASL[indx].size)));	
	}
	j=find(i->buddy_indx,B_addr);
	if(j->tag == 0)
	{
		merge(i,indx,j,i->buddy_indx);
	}
	}
}
struct ASL_node* find(int indx,int addr)
{
	struct ASL_node* j;
	j=ASL[indx].head;
	while(j->strt != addr)
	{
		j=j->next;
	}
	return(j);
}
void merge(struct ASL_node* i,int indx_i,struct ASL_node* j,int indx_j)
{	
	no_recomb++;
	struct ASL_node* k;
	struct ASL_node* l;
	struct ASL_node* prev;
	if(ASL[indx_i].size > ASL[indx_j].size)
		k=find(i->parent_indx,i->strt);
	else
		k=find(j->parent_indx,j->strt);
	k->tag=0;
	int k_indx=i->parent_indx;
	l=ASL[indx_i].head;
	while(l != i)
	{		
		prev=l;
		l=l->next;
	}
	if(l == ASL[indx_i].head)
		ASL[indx_i].head=l->next;
	else
		prev->next=l->next;
	if(l == ASL[indx_i].tail)
		ASL[indx_i].tail=l->prev;
	free(l);

	l=ASL[indx_j].head;
	while(l != j)
	{		
		prev=l;
		l=l->next;
	}
	if(l == ASL[indx_j].head)
		ASL[indx_j].head=l->next;
	else
		prev->next=l->next;
	if(l == ASL[indx_j].tail)
		ASL[indx_j].tail=l->prev;	
	free(l);
	dealloc(k_indx,k->strt);
}


void print_sheap_data()
{
	intr_frag=(sum_alloc-sum_request)/sum_request;
	printf("\nNumber of allocation requests : %d",no_alloc_req);
	printf("\nNumber of deallocation request : %d",no_dealloc_req);
	printf("\nNumber of area splits : %d",no_splits);
	printf("\nNumber of buddy recombination : %d",no_recomb);
	printf("\nInternal Fragmentation : %f",intr_frag);
	printf("\nTime for allocation : %lf seconds",time_alloc);
	printf("\nTime for free : %lf seconds",time_free);
}

