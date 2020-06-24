#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "header.h"

void simulate(list* list,int version,int strt_state,int no_transition)
{
	if(list->current_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
    
    node* state_ptr = (node*) malloc(sizeof(node));
    if(state_ptr == NULL)
    {
    	printf("Memory allocation error");
    	return;
    }
  
    state_ptr=list->head[version];
    
    while(state_ptr != NULL)
    {
    	if((state_ptr->mod->version <= version) && (state_ptr->mod->version != unused))
	  	{
	  		if(state_ptr->mod->data == strt_state)
	  			break;
	  		state_ptr = state_ptr->mod->next;
	  	}
      	else
	  	{
	  		if(state_ptr->data == strt_state)
	  			break;	
	  		state_ptr = state_ptr->next;
	  	}
    }
    
    if(state_ptr == NULL)
    {
    	printf("Provided state does not exist in given version of chain.");
    	exit(0);
    }
    else
    	transit(state_ptr,version,no_transition);
}


void transit(node* state_ptr,int version,int no_transition)
{
	srand(time(0));
	int i=0,j=0;
	float x;

	while(i <= no_transition)
	{
		x=(float)rand()/(float)RAND_MAX;
		//printf("\n%f",x);
		if((state_ptr->mod->version <= version) && (state_ptr->mod->version != unused))
			j=0;
		else
			j=1;
			
		if(j==0 ? (x <= state_ptr->mod->fw_prob) : (x <= state_ptr->fw_prob))
		{
			if(j == 0)
	  		{
	  			printf("\nstate : %d",state_ptr->mod->data);
	  			if(state_ptr->mod->next != NULL)
	  				state_ptr = state_ptr->mod->next;
	  		}
      		else
	  		{
				printf("\nstate : %d",state_ptr->data);		  		
	  			if(state_ptr->next != NULL)
	  				state_ptr = state_ptr->next;				  	
	  		}	
		}
		else if(j==0 ? (x <= (state_ptr->mod->fw_prob + state_ptr->mod->bw_prob)) : (x <= (state_ptr->fw_prob + state_ptr->bw_prob)))
		{
			if(j == 0)
	  		{
	  			printf("\nstate : %d",state_ptr->mod->data);
	  			if(state_ptr->mod->prev != NULL)
	  				state_ptr = state_ptr->mod->prev;	
	  		}
      		else
	  		{
				printf("\nstate : %d",state_ptr->data);	  		
	  			if(state_ptr->prev != NULL)
	  				state_ptr = state_ptr->prev;	  			
	  		}	
		}
		else
		{
			if(j == 0)
				printf("\nstate : %d",state_ptr->mod->data);
			else
				printf("\nstate : %d",state_ptr->data);	
		}
		i++;
	}
}

node* addNode(int data,float fw_prob,float bw_prob,float ss_prob)
{
  node* newnode = (node*) malloc(sizeof(node));
  newnode->data = data;
  newnode->fw_prob=fw_prob;
  newnode->bw_prob=bw_prob;
  newnode->ss_prob=ss_prob;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->data = def;
  newnode->mod->version = unused;
  newnode->mod->fw_prob=0;
  newnode->mod->bw_prob=0;
  newnode->mod->ss_prob=0;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}

list* initialize()
{
  int i;
  list* newlist = (list*) malloc(sizeof(list));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->current_version = 0;

  for(i = 0; i < max; i++)
    newlist->head[i] = NULL;
      
  return newlist;
}



void print_list(list* list, int version)
{
  if(list->current_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  node* print_ptr = (node*) malloc(sizeof(node));

  printf("List of version %d\n", version);
	
  if(!print_ptr)	
    {
      printf("Memory allocation error");
      return;
    }

  for(print_ptr = list->head[version]; print_ptr != NULL; )
    {
      if((print_ptr->mod->version <= version) && (print_ptr->mod->version != unused))
	  {
	  	printf("\n%d %f %f %f", print_ptr->mod->data,print_ptr->mod->fw_prob,print_ptr->mod->bw_prob,print_ptr->mod->ss_prob);
	  	print_ptr = print_ptr->mod->next;
	  }
      else
	  {
	  	printf("\n%d %f %f %f", print_ptr->data,print_ptr->fw_prob,print_ptr->bw_prob,print_ptr->ss_prob);
	  	print_ptr = print_ptr->next;
	  }
    }
  printf("\n");
  free(print_ptr);
}




node* updatre_left(list* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) 
  	return NULL;

  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->fw_prob=list_ptr->fw_prob;
      list_ptr->mod->bw_prob=list_ptr->bw_prob;
      list_ptr->mod->ss_prob=list_ptr->ss_prob;
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = list_ptr->prev;

      list->head[current_version] = list->head[current_version-1];
      return list_ptr;
    }
  else
    {
      node* newnode_parent = addNode(list_ptr->mod->data,list_ptr->mod->fw_prob,list_ptr->mod->bw_prob,list_ptr->mod->ss_prob);
    
      newnode_parent->next = newnode;

      if(list_ptr->mod->prev == NULL)
		{
	 	 list->head[current_version] = newnode_parent;
		  return newnode_parent;
		}
      
      newnode_parent->prev = updatre_left(list, list_ptr->mod->prev, newnode_parent, current_version);
    }

}



node* update_parentright(list* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) return NULL;
    
  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->fw_prob=list_ptr->fw_prob;
      list_ptr->mod->bw_prob=list_ptr->bw_prob;
      list_ptr->mod->ss_prob=list_ptr->ss_prob;
      list_ptr->mod->version = current_version;
      list_ptr->mod->prev = newnode;
      list_ptr->mod->next = list_ptr->next;

      return list_ptr;
    }
  else
    {
      node* newnode_parent = addNode(list_ptr->mod->data,list_ptr->mod->fw_prob,list_ptr->mod->bw_prob,list_ptr->mod->ss_prob);
 
      newnode_parent->prev = newnode;
	
      newnode_parent->next = update_parentright(list, list_ptr->mod->next, newnode_parent, current_version);
    }

}


bool insert(list* list, int data, int index,float fw_prob,float bw_prob,float ss_prob)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  if((fw_prob+bw_prob+ss_prob) != 1)
  	{
  		printf("Entered probabilties are not correct. Sum of transition probability at perticular node shold be 1.");
  		return false;
  	}	
  
  int index_count = 0;
  int current_version = list->current_version;
  node* newnode = addNode(data,fw_prob,bw_prob,ss_prob);
  
  node* list_ptr = (node*) malloc(sizeof(node));
  node* list_ptr_prev = (node*) malloc(sizeof(node));
  
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(!list_ptr_prev)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(list_ptr = list->head[current_version], list_ptr_prev = list->head[current_version]; list_ptr != NULL; index_count++)
    {
      if(list_ptr != list->head[current_version])
		list_ptr_prev = list_ptr->prev;
      
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= current_version) && list_ptr->mod->version != unused)
		list_ptr = list_ptr->mod->next;
      else
		list_ptr = list_ptr->next;
    }
  
  if(list->head[current_version] == NULL)
    {
      list->head[current_version] = newnode;
      return true;
    }

  if(index != index_count) 
    {
      printf("Index greater than length of the list. The element will be appended at the end of the list\n");
    }
  
  if(list_ptr_prev == list->head[current_version] && index == 1)
    list_ptr = list_ptr_prev;
  else if((list_ptr == NULL) && (list_ptr_prev->mod->version == unused))
    list_ptr = list_ptr_prev->next;
  else if((list_ptr == NULL) && (list_ptr_prev->mod->version != unused))
    list_ptr = list_ptr_prev->mod->next;
  else
    list_ptr = list_ptr_prev;  

  if(list_ptr->mod->version == unused)
    {      
      current_version++;
      
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->fw_prob = list_ptr->fw_prob;
      list_ptr->mod->bw_prob = list_ptr->bw_prob;
      list_ptr->mod->ss_prob = list_ptr->ss_prob;
      list_ptr->mod->version = current_version;

      if(index != 0)
		{
	  	  list_ptr->mod->next = newnode;
	 	  list_ptr->mod->prev = list_ptr->prev;

		  newnode->next = update_parentright(list, list_ptr->next, newnode, current_version);
		  newnode->prev = updatre_left(list, list_ptr, newnode, current_version);
		}
      else
		{
	      newnode->next = list_ptr;
  	      list_ptr->mod->next = list_ptr->next;
	      list_ptr->mod->prev = newnode;

	      list->head[current_version] = newnode;
      	}
    }
  else
    {
      current_version++;

      if(index !=0)
	{
	  newnode->next = update_parentright(list, list_ptr->mod->next, newnode, current_version);
	  newnode->prev = updatre_left(list, list_ptr, newnode, current_version);
	}
      else
	{
	  node* trailNode = addNode(list_ptr->mod->data,list_ptr->mod->fw_prob,list_ptr->mod->bw_prob,list_ptr->mod->ss_prob);
	  trailNode->next = list_ptr->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
  return true;
}


bool update(list* list, int data, int index,float fw_prob,float bw_prob,float ss_prob)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  if((fw_prob+bw_prob+ss_prob) != 1)
  	{
  		printf("Entered probabilties are not correct. Sum of transition probability at perticular node shold be 1.");
  		return false;
  	}
  
  int index_count = 0;
  int current_version = list->current_version;

  node* list_ptr = (node*) malloc(sizeof(node));
  
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(list_ptr = list->head[current_version]; list_ptr != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= current_version) && list_ptr->mod->version != unused)
		list_ptr = list_ptr->mod->next;
      else
		list_ptr = list_ptr->next;
    }

  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      insert(list, data, index,fw_prob,bw_prob,ss_prob);
    }
  else
    {     
      if(list_ptr->mod->version == unused)
		{  
	   	  current_version++;
      
		  list_ptr->mod->data = data;
		  list_ptr->mod->fw_prob=fw_prob;
      	  list_ptr->mod->bw_prob=bw_prob;
          list_ptr->mod->ss_prob=ss_prob;
		  list_ptr->mod->version = current_version;

	      list_ptr->mod->next = list_ptr->next;
	   	  list_ptr->mod->prev = list_ptr->prev;

	      list->head[current_version] = list->head[current_version-1];
		}
      else
		{
	  	  current_version++;
	      if(index != 0)
	       {
	      	node* newnode = addNode(data,fw_prob,bw_prob,ss_prob);
	  
	      	newnode->next = update_parentright(list, list_ptr->mod->next, newnode, current_version);
	      	newnode->prev = updatre_left(list, list_ptr->mod->prev, newnode, current_version);
	       }
	  	 else
	      {
	       node* newnode = addNode(data,fw_prob,bw_prob,ss_prob);
	  
	       newnode->next = update_parentright(list, list_ptr->mod->next, newnode, current_version);
	       list->head[current_version] = newnode;
	      }
	}

      list->current_version = current_version;
    }
  return true;
}



bool delete_node(list* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int current_version = list->current_version;

    node* list_ptr = (node*) malloc(sizeof(node));
  
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[current_version] == NULL)
   {
     printf("List is empty. Cannot delete_node from empty list");
     return false;
   }
  
  if(list->head[current_version]->next == NULL)
   {
     current_version++;
     list->head[current_version] = NULL;
       
     list->current_version = current_version;
     return true;
   }
  
  for(list_ptr = list->head[current_version]; list_ptr != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= current_version) && list_ptr->mod->version != unused)
	list_ptr = list_ptr->mod->next;
      else
	list_ptr = list_ptr->next;
    }
  
  if(list_ptr == NULL) index_count--;

  if(index != index_count) 
    {
      printf("Index not found in the list\n");
      return false;
    }
  else
    {
      if(index == 0)
		{
	      if(list_ptr->mod->version == unused)
	      {
	      	if(list_ptr->next->mod->version == unused)
			{  
		  		current_version++;
		
		  		list_ptr->next->mod->data = list_ptr->next->data;
		  		list_ptr->next->mod->fw_prob=list_ptr->fw_prob;
      	  		list_ptr->next->mod->bw_prob=list_ptr->bw_prob;
       		   	list_ptr->next->mod->ss_prob=list_ptr->ss_prob;
		  		list_ptr->next->mod->version = current_version;

		  		list_ptr->next->mod->next = list_ptr->next->next;
		  		list_ptr->next->mod->prev = list_ptr->prev;

		  		list->head[current_version] = list_ptr->next;
			}
	      else
			{
		  		current_version++;

		  		node* newnode = addNode(list_ptr->next->mod->data,list_ptr->next->mod->fw_prob,list_ptr->next->mod->bw_prob,list_ptr->next->mod->ss_prob);

		  		newnode->next = update_parentright(list, list_ptr->next->mod->next, newnode, current_version);
	  	  
		  		list->head[current_version] = newnode;
			}
	    }
	  else
	    {
	      if(list_ptr->mod->next->mod->version == unused)
			{  
		  		current_version++;
		
		  		list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
		  		list_ptr->next->mod->fw_prob=list_ptr->fw_prob;
      	  		list_ptr->next->mod->bw_prob=list_ptr->bw_prob;
       		   	list_ptr->next->mod->ss_prob=list_ptr->ss_prob;
		  		list_ptr->mod->next->mod->version = current_version;

		  		list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
		  		list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

		  		list->head[current_version] = list_ptr->mod->next;
			}
	      else
			{
		  		current_version++;

		  		node* newnode = addNode(list_ptr->mod->next->mod->data,list_ptr->mod->next->mod->fw_prob,list_ptr->mod->next->mod->bw_prob,list_ptr->mod->next->mod->ss_prob);

		  		newnode->next = update_parentright(list, list_ptr->mod->next->mod->next, newnode, current_version);
	  	  
		  		list->head[current_version] = newnode;
			}
	    }
	  
	  list->current_version = current_version;
	  return true;
	}

   if((list_ptr->next == NULL) && (list_ptr->mod->version == unused))
	{
	  	if(list_ptr->prev->mod->version == unused)
	   	{  
    		current_version++;

      		list_ptr->prev->mod->data = list_ptr->prev->data;
      		list_ptr->prev->mod->fw_prob = list_ptr->prev->fw_prob;
      		list_ptr->prev->mod->bw_prob = list_ptr->prev->bw_prob;
      		list_ptr->prev->mod->ss_prob = list_ptr->prev->ss_prob;
      		list_ptr->prev->mod->version = current_version;

      		list_ptr->prev->mod->next = list_ptr->next;
      		list_ptr->prev->mod->prev = list_ptr->prev->prev;

      		list->head[current_version] = list->head[current_version-1];
    	}
  		else
    	{
      		current_version++;

      		node* newnode = addNode(list_ptr->prev->mod->data,list_ptr->prev->mod->fw_prob,list_ptr->prev->mod->bw_prob,list_ptr->prev->mod->ss_prob);
	      
      		newnode->prev = updatre_left(list, list_ptr->prev->mod->prev, newnode, current_version);
    	}
 
	    list->current_version = current_version;
	    return true;
	}
      
   if((list_ptr->mod->next == NULL) && (list_ptr->mod->version != unused))
	{
	  if(list_ptr->mod->prev->mod->version == unused)
	    {  
	      current_version++;

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->fw_prob = list_ptr->mod->prev->fw_prob;
	      list_ptr->mod->prev->mod->bw_prob = list_ptr->mod->prev->bw_prob;
	      list_ptr->mod->prev->mod->ss_prob = list_ptr->mod->prev->ss_prob;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->mod->prev->mod->data,list_ptr->mod->prev->mod->fw_prob,list_ptr->mod->prev->mod->bw_prob,list_ptr->mod->prev->mod->ss_prob);
	      
	      newnode->prev = updatre_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version);
	    }

	  list->current_version = current_version;
	  return true;
	}
      

      if(list_ptr->mod->version == unused)
	{
	  if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version == unused))
	    {  
	      current_version++;

	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->fw_prob = list_ptr->prev->fw_prob;
	      list_ptr->prev->mod->bw_prob = list_ptr->prev->bw_prob;
	      list_ptr->prev->mod->ss_prob = list_ptr->prev->ss_prob;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->fw_prob = list_ptr->next->fw_prob;
	      list_ptr->next->mod->bw_prob = list_ptr->next->bw_prob;
	      list_ptr->next->mod->ss_prob = list_ptr->next->ss_prob;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = list_ptr->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->next->mod->data,list_ptr->next->mod->fw_prob,list_ptr->next->mod->bw_prob,list_ptr->next->mod->ss_prob);
	      
	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->fw_prob = list_ptr->prev->fw_prob;
	      list_ptr->prev->mod->bw_prob = list_ptr->prev->bw_prob;
	      list_ptr->prev->mod->ss_prob = list_ptr->prev->ss_prob;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      newnode->prev = list_ptr->prev;		
	      newnode->next = update_parentright(list, list_ptr->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->data,list_ptr->mod->prev->mod->fw_prob,list_ptr->mod->prev->mod->bw_prob,list_ptr->mod->prev->mod->ss_prob);
	      
	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->fw_prob = list_ptr->next->fw_prob;
	      list_ptr->next->mod->bw_prob = list_ptr->next->bw_prob;
	      list_ptr->next->mod->ss_prob = list_ptr->next->ss_prob;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      newnode->next = list_ptr->next;
	      newnode->prev = updatre_left(list, list_ptr->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
        
	      node* newnode_prev = addNode(list_ptr->prev->mod->data,list_ptr->mod->prev->mod->fw_prob,list_ptr->mod->prev->mod->bw_prob,list_ptr->mod->prev->mod->ss_prob);
	      node* newnode_next = addNode(list_ptr->next->mod->data,list_ptr->mod->next->mod->fw_prob,list_ptr->mod->next->mod->bw_prob,list_ptr->mod->next->mod->ss_prob);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = updatre_left(list, list_ptr->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_parentright(list, list_ptr->next->mod->next, newnode_next, current_version);
 	    }
	}
      else
	{
	  if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version == unused))
	    {  
	      current_version++;

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->fw_prob = list_ptr->mod->prev->fw_prob;
	      list_ptr->mod->prev->mod->bw_prob = list_ptr->mod->prev->bw_prob;
	      list_ptr->mod->prev->mod->ss_prob = list_ptr->mod->prev->ss_prob;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->fw_prob = list_ptr->mod->next->fw_prob;
	      list_ptr->mod->next->mod->bw_prob = list_ptr->mod->next->bw_prob;
	      list_ptr->mod->next->mod->ss_prob = list_ptr->mod->next->ss_prob;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;
	      	  
	      node* newnode = addNode(list_ptr->mod->next->mod->data,list_ptr->mod->next->mod->fw_prob,list_ptr->mod->next->mod->bw_prob,list_ptr->mod->next->mod->ss_prob);
	  
	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->fw_prob = list_ptr->mod->prev->fw_prob;
	      list_ptr->mod->prev->mod->bw_prob = list_ptr->mod->prev->bw_prob;
	      list_ptr->mod->prev->mod->ss_prob = list_ptr->mod->prev->ss_prob;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = newnode;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;
	      
	      newnode->prev = list_ptr->mod->prev;
	      newnode->next = update_parentright(list, list_ptr->mod->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;
	      
	      node* newnode = addNode(list_ptr->mod->prev->mod->data,list_ptr->mod->prev->mod->fw_prob,list_ptr->mod->prev->mod->bw_prob,list_ptr->mod->prev->mod->ss_prob);       

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->fw_prob = list_ptr->mod->next->fw_prob;
	      list_ptr->mod->next->mod->bw_prob = list_ptr->mod->next->bw_prob;
	      list_ptr->mod->next->mod->ss_prob = list_ptr->mod->next->ss_prob;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      newnode->next = list_ptr->mod->next;

	      newnode->prev = updatre_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
	      
	      node* newnode_prev = addNode(list_ptr->mod->prev->mod->data,list_ptr->mod->prev->mod->fw_prob,list_ptr->mod->prev->mod->bw_prob,list_ptr->mod->prev->mod->ss_prob);
	      node* newnode_next = addNode(list_ptr->mod->next->mod->data,list_ptr->mod->next->mod->fw_prob,list_ptr->mod->next->mod->bw_prob,list_ptr->mod->next->mod->ss_prob);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = updatre_left(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_parentright(list, list_ptr->mod->next->mod->next, newnode_next, current_version);
	    }

	}
      
      list->current_version = current_version;
    }
  return true;
}
