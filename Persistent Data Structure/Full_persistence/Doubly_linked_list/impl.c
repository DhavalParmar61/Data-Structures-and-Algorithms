#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


list* initialize()
{
  list* newlist = (list*) malloc(sizeof(list));

  if(!newlist)
    {
      printf("Error in list creation\n");
      return NULL;
    }

  newlist->current_version = 0;
  int i;
  for(i = 0; i < max; i++)
    newlist->head[i] = NULL;
      
  return newlist;
}

node* addNode(int data, int version)
{
  node* newnode = (node*) malloc(sizeof(node));
  newnode->data = data;
  newnode->next = NULL;
  newnode->prev = NULL;
  newnode->node_version = version;
  
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
  
  node* print_ptr = (node*) malloc(sizeof(node));
  
  printf("\nList of version %d\n", version);
	
  if(!print_ptr)	
    {
      printf("Memory allocation error\n");
      return;
    }

  for(print_ptr = list->head[version]; print_ptr != NULL;)
    {
       if(print_ptr->node_version > version)
      	break;
      
      if((print_ptr->mod->version <= version) && (print_ptr->mod->version > unused))
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


node* update_left(list* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = list_ptr->prev;

      list->head[current_version] = list->head[version];
      return list_ptr;
    }
  else
    {
      node* newnode_parent = addNode(list_ptr->mod->data, current_version);
    
      newnode_parent->next = newnode;

      if(list_ptr->mod->prev == NULL)
	{
	  list->head[current_version] = newnode_parent;
	  return newnode_parent;
	}

      newnode_parent->prev = update_left(list, list_ptr->mod->prev, newnode_parent, current_version, version);
    }

}



node* update_right(list* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;
  if(list_ptr->node_version > version) return NULL;
  
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
      node* newnode_parent = addNode(list_ptr->mod->data, current_version);

      newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version, version);

      newnode_parent->prev = newnode;
    }

}



bool insert(list* list, int data, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }

  int index_count = 0;
  int current_version = list->current_version;
  node* newnode = addNode(data, unused);

  if(version > current_version)
    {
      printf("Version does not exist\n");
      return false;
    }
      
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
 
  for(list_ptr = list->head[version], list_ptr_prev = list->head[version]; list_ptr != NULL; index_count++)
    {
      if(list_ptr != list->head[version])
	list_ptr_prev = list_ptr->prev;
      
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= version) && list_ptr->mod->version != unused)
	list_ptr = list_ptr->mod->next;
      else
	list_ptr = list_ptr->next;
    }
  
  if(list->head[current_version] == NULL)
    {
      list->head[current_version] = newnode;
      newnode->node_version = current_version;
      return true;
    }

  if(index != index_count) 
    {
      printf("Index greater than length of the list. The element will be appended at the end of the list\n");
    }
  
  if(list_ptr_prev == list->head[version] && index == 1)
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
      

      newnode->node_version = current_version;
      
      if(index != 0)
	{
	  list_ptr->mod->next = newnode;
	  list_ptr->mod->prev = list_ptr->prev;

	  newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
	  newnode->prev = update_left(list, list_ptr, newnode, current_version, version);
	}
      else
	{
	  newnode->next = list_ptr;
  	  list_ptr->mod->next = list_ptr->next;
	  list_ptr->mod->prev = newnode;
	  list_ptr->mod->version = current_version;
	  
	  list->head[current_version] = newnode;
      	}
    }
    else
    {
      current_version++;
      
      newnode->node_version = current_version;

      if(index !=0)
	{
	   newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
	   newnode->prev = update_left(list, list_ptr, newnode, current_version, version);
	}
      else
	{
	  node* trailNode = addNode(list_ptr->mod->data, current_version);
	 
	  trailNode->prev = newnode;
	  trailNode->next = update_right(list, list_ptr->mod->next, trailNode, current_version, version);	
	  
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
   return true;
}



bool update(list* list, int data, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int current_version = list->current_version;

  node* list_ptr = (node*) malloc(sizeof(node));

  if(version > current_version)
    {
      printf("Version does not exist\n");
      return false;
    }
    
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(list_ptr = list->head[version]; list_ptr != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= version) && list_ptr->mod->version != unused)
	list_ptr = list_ptr->mod->next;
      else
	list_ptr = list_ptr->next;
    }

  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      insert(list, data, index, version);
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

	  list->head[current_version] = list->head[version];
	}
      else
	{
	  current_version++;
	  
	  if(index != 0)
	    {
	      node* newnode = addNode(data, current_version);
	  
	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
	      newnode->prev = update_left(list, list_ptr->mod->prev, newnode, current_version, version);
	    }
	  else
	    {
	      node* newnode = addNode(data, current_version);
	  
	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
	      list->head[current_version] = newnode;
	    }
	}

      list->current_version = current_version;
    }
  return true;
}




bool delete_list(list* list, int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int current_version = list->current_version;

  node* list_ptr = (node*) malloc(sizeof(node));

  if(version > current_version)
    {
      printf("Version does not exist\n");
      return false;
    }
     
  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(list->head[version] == NULL)
   {
     printf("List is empty. Cannot delete from empty list");
     return false;
   }
   
  if((list->head[version]->next == NULL) && (list->head[version]->mod->next == NULL))
   {
     current_version++;
     list->head[current_version] = NULL;

     list->current_version = current_version;
     return true;
     }
  
  for(list_ptr = list->head[version]; list_ptr != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= version) && list_ptr->mod->version != unused)
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

		  node* newnode = addNode(list_ptr->next->mod->data, current_version);

		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
	  	  
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

		  node* newnode = addNode(list_ptr->mod->next->mod->data, current_version);

		  newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
	  	  
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

	      list->head[current_version] = list->head[version];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->data, current_version);
	      
	      newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);
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

	      list->head[current_version] = list->head[version];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->mod->prev->mod->data, current_version);
	      
	      newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);
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

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->next->mod->data, current_version);
	      
	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      newnode->prev = list_ptr->prev;		
	      newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
	  	  
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->data, current_version);
	      
	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      newnode->next = list_ptr->next;
	      newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);
	    }
	  else
	    {
	      current_version++;
        
	      node* newnode_prev = addNode(list_ptr->prev->mod->data, current_version);
	      node* newnode_next = addNode(list_ptr->next->mod->data, current_version);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_ptr->prev->mod->prev, newnode_prev, current_version, version);
	      newnode_next->next = update_right(list, list_ptr->next->mod->next, newnode_next, current_version, version);
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

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;
    	      	  
	      node* newnode = addNode(list_ptr->mod->next->mod->data, current_version);
	  
	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = newnode;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;
	      
	      newnode->prev = list_ptr->mod->prev;
	      newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
	  	  
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;
	      	      
	      node* newnode = addNode(list_ptr->mod->prev->mod->data, current_version);       

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      newnode->next = list_ptr->mod->next;

	      newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);
	    }
	  else
	    {
	      current_version++;
	        
	      node* newnode_prev = addNode(list_ptr->mod->prev->mod->data, current_version);
	      node* newnode_next = addNode(list_ptr->mod->next->mod->data, current_version);

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version, version);
	      if(list_ptr->mod->prev->mod->prev == NULL)
	      	list->head[current_version] = newnode_prev;

	      newnode_next->next = update_right(list, list_ptr->mod->next->mod->next, newnode_next, current_version, version);
	    }

	}
      
      list->current_version = current_version;
    }
  return true;
}

