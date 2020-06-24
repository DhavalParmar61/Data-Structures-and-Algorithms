#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


dequeue* initialize()
{
  dequeue* newlist = (dequeue*) malloc(sizeof(dequeue));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->current_version = 0;
  int i;
  for(i = 0; i < max; i++)
    newlist->head[i] = NULL;

  newlist->num_el = 0;
      
  return newlist;
}

node* addNode(int data)
{
  node* newnode = (node*) malloc(sizeof(node));
  newnode->data = data;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->data = def;
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


void print_dequeue(dequeue* list, int version)
{
  if(list->current_version < version)
    {
      printf("\nEntered version does not exist");
      return;
    }
  
  node* print_ptr = (node*) malloc(sizeof(node));

  printf("\nList of version %d", version);
	
  if(!print_ptr)	
    {
      printf("Memory allocation error");
      return;
    }

  printf("\n");
  for(print_ptr = list->head[version]; print_ptr != NULL; )
    {
      if((print_ptr->mod->version <= version) && (print_ptr->mod->version != unused))
	{
	  printf("%d ", print_ptr->mod->data);
	  print_ptr = print_ptr->mod->next;
	}
      else
	{
	  printf("%d ", print_ptr->data);
	  print_ptr = print_ptr->next;
	}
    }
  
}



node* update_left(dequeue* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = list_ptr->prev;

      list->head[current_version] = list->head[current_version-1];
      return list_ptr;
    }
  else
    {
      node* newnode_parent = addNode(list_ptr->mod->data);
    
      newnode_parent->next = newnode;

      if(list_ptr->mod->prev == NULL)
	{
	  list->head[current_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = update_left(list, list_ptr->mod->prev, newnode_parent, current_version);
    }

}



node* update_right(dequeue* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) return NULL;
    
  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;
      list_ptr->mod->prev = newnode;
      list_ptr->mod->next = list_ptr->next;

      return list_ptr;
    }
  else
    {
      node* newnode_parent = addNode(list_ptr->mod->data);
 
      newnode_parent->prev = newnode;

      // if(list_ptr->mod->next == NULL) return newnode_parent;
	
      newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version);
    }

}



bool insert_list(dequeue* list, int data, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int current_version = list->current_version;
  node* newnode = addNode(data);
  
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
	list_ptr_prev = list_ptr;
      
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= current_version) && list_ptr->mod->version != unused)
	  list_ptr = list_ptr->mod->next;
      else
	  list_ptr = list_ptr->next;


    }

  list->num_el++;
  
  if(list->head[current_version] == NULL)
    {
      list->head[current_version] = newnode;
      return true;
    }
  
  list_ptr = list_ptr_prev;

  if(list_ptr->mod->version == unused)
    {      
      current_version++;
      
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;

      if(index != 0)
	{
	  list_ptr->mod->next = newnode;
	  list_ptr->mod->prev = list_ptr->prev;

	  newnode->next = update_right(list, list_ptr->next, newnode, current_version);
	  newnode->prev = update_left(list, list_ptr, newnode, current_version);
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
	  newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version);
	  newnode->prev = update_left(list, list_ptr, newnode, current_version);
	}
      else
	{
	  node* trailNode = addNode(list_ptr->mod->data);
	  trailNode->next = list_ptr->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
  return true;
}





int delete_list(dequeue* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int element;
  int current_version = list->current_version;

  node* list_ptr = (node*) malloc(sizeof(node));
  
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[current_version] == NULL)
   {
     printf("List is empty. Cannot delete from empty list");
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
      list->num_el--;
           
      if(index == 0)
	{
	  if(list_ptr->mod->version == unused)
	    {
	      if(list_ptr->next->mod->version == unused)
		{  
		  current_version++;
		
		  list_ptr->next->mod->data = list_ptr->next->data;
		  list_ptr->next->mod->version = current_version;

		  list_ptr->next->mod->next = list_ptr->next->next;
		  list_ptr->next->mod->prev = list_ptr->prev;

		  list->head[current_version] = list_ptr->next;
		}
	      else
		{
		  current_version++;

		  node* newnode = addNode(list_ptr->next->mod->data);

		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version);
	  	  
		  list->head[current_version] = newnode;
		}
	      
	      element = list_ptr->data;
	    }
	  else
	    {
	      if(list_ptr->mod->next->mod->version == unused)
		{  
		  current_version++;
		
		  list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
		  list_ptr->mod->next->mod->version = current_version;

		  list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
		  list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

		  list->head[current_version] = list_ptr->mod->next;
		}
	      else
		{
		  current_version++;

		  node* newnode = addNode(list_ptr->mod->next->mod->data);

		  newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version);
	  	  
		  list->head[current_version] = newnode;
		}

	      element = list_ptr->mod->data;
	    }
	  
	  list->current_version = current_version;
	  return element;
	}

      if((list_ptr->next == NULL) && (list_ptr->mod->version == unused))
	{
	  if(list_ptr->prev->mod->version == unused)
	    {  
	      current_version++;

	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->data);
	      
	      newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version);
	    }
	  
	  element = list_ptr->data;

	  list->current_version = current_version;
	  return element;
	}
      
      if((list_ptr->mod->next == NULL) && (list_ptr->mod->version != unused))
	{
	  if(list_ptr->mod->prev->mod->version == unused)
	    {  
	      current_version++;

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->mod->prev->mod->data);
	      
	      newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version);
	    }

	  element = list_ptr->mod->data;
	  
	  list->current_version = current_version;
	  return element;
	}
      

      if(list_ptr->mod->version == unused)
	{
	  if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version == unused))
	    {  
	      current_version++;

	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = list_ptr->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->next->mod->data);
	      
	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      newnode->prev = list_ptr->prev;		
	      newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->data);
	      
	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      newnode->next = list_ptr->next;
	      newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
        
	      node* newnode_prev = addNode(list_ptr->prev->mod->data);
	      node* newnode_next = addNode(list_ptr->next->mod->data);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_ptr->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_right(list, list_ptr->next->mod->next, newnode_next, current_version);
 	    }
	  
	  element = list_ptr->data;
	}
      else
	{
	  if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version == unused))
	    {  
	      current_version++;

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;
	      	  
	      node* newnode = addNode(list_ptr->mod->next->mod->data);
	  
	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = newnode;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;
	      
	      newnode->prev = list_ptr->mod->prev;
	      newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;
	      
	      node* newnode = addNode(list_ptr->mod->prev->mod->data);       

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      newnode->next = list_ptr->mod->next;

	      newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
	      
	      node* newnode_prev = addNode(list_ptr->mod->prev->mod->data);
	      node* newnode_next = addNode(list_ptr->mod->next->mod->data);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_right(list, list_ptr->mod->next->mod->next, newnode_next, current_version);
	    }

	}

      element = list_ptr->mod->data;
      list->current_version = current_version;
    }
  return element;
}



bool isempty(dequeue* deque)
{
  if(deque->num_el == 0) return true;
  else false;
}


bool insert_front(dequeue* deque, int data)
{
  if(insert_list(deque, data, 0)) return true;
  else false;
}


bool insert_rear(dequeue* deque, int data)
{ 
  if(insert_list(deque, data, deque->num_el)) true;
  return true;
}


int delete_front(dequeue* deque)
{
  return delete_list(deque, 0);
}
  
int delete_rear(dequeue* deque)
{
  return delete_list(deque, deque->num_el-1);
}
