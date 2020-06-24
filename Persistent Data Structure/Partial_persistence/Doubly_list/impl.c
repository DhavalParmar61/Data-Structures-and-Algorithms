#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


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


void print_list(list* list, int version)
{
  if(list->current_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }
  
  node* ptr = (node*) malloc(sizeof(node));

  printf("\nList of version %d\n", version);
	
  if(!ptr)	
    {
      printf("Memory allocation error");
      return;
    }

  for(ptr = list->head[version]; ptr != NULL; )
    {
      if((ptr->mod->version <= version) && (ptr->mod->version != unused))
	{
	  printf("%d ", ptr->mod->data);
	  ptr = ptr->mod->next;
	}
      else
	{
	  printf("%d ", ptr->data);
	  ptr = ptr->next;
	}
    }
  
}



node* update_left(list* list, node* list_ptr, node* newnode, int current_version)
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


node* update_right(list* list, node* list_ptr, node* newnode, int current_version)
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



bool insert(list* list, int data, int index)
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


bool update(list* list, int data, int index)
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
      insert(list, data, index);
    }
  else
    {     
      if(list_ptr->mod->version == unused)
	{  
	  current_version++;
      
	  list_ptr->mod->data = data;
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
	      node* newnode = addNode(data);
	  
	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version);
	      newnode->prev = update_left(list, list_ptr->mod->prev, newnode, current_version);
	    }
	  else
	    {
	       node* newnode = addNode(data);
	  
	       newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version);
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
 
	  list->current_version = current_version;
	  return true;
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

	  list->current_version = current_version;
	  return true;
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
      
      list->current_version = current_version;
    }
  return true;
}
