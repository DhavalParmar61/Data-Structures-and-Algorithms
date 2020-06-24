#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

node* addNode(char input_key[], char input_value[])
{
  char key[str_size], value[str_size];
  
  node* newnode = (node*) malloc(sizeof(node));
  strcpy(newnode->key, input_key);
  strcpy(newnode->value, input_value);
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  strcpy(newnode->mod->key, def);
  strcpy(newnode->mod->value, def);
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
  
  return newnode;
}



map* initialize()
{
  map* newlist = (map*) malloc(sizeof(map));

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


void find(map* list, char str[])
{
    
  char search_key[str_size];
  int version;

  sscanf(str, "%[^,],%d", search_key, &version);
    
  if(list->current_version < version)
    {
      printf("Entered version does not exist\n");
      return;
    }

  node* list_ptr = (node*) malloc(sizeof(node));

  if(!list_ptr)	
    {
      printf("Memory allocation error");
      return;
    }

	
  for(list_ptr = list->head[version]; list_ptr != NULL; )
    {
      if((list_ptr->mod->version <= version) && (list_ptr->mod->version != unused))
	{
	  if(!strcmp(list_ptr->mod->key, search_key))
	    {
	      printf("\nKey : %s, Value : %s\n", list_ptr->mod->key, list_ptr->mod->value);
	      return;
	    }
	  list_ptr = list_ptr->mod->next;
	}
      else
	{
	  if(!strcmp(list_ptr->key, search_key))
	    {
	      printf("\nKey : %s, Value : %s\n", list_ptr->key, list_ptr->value);
	      return;
	    }

	  list_ptr = list_ptr->next;
	}
    }
  
  printf("Key not found\n");
}



void print(map* list, int version)
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
	  printf("Key : %s, Value : %s\n", print_ptr->mod->key, print_ptr->mod->value);
	  print_ptr = print_ptr->mod->next;
	}
      else
	{
	  printf("Key : %s, Value : %s\n", print_ptr->key, print_ptr->value);
	  print_ptr = print_ptr->next;
	}
    }
}



node* update_left(map* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      strcpy(list_ptr->mod->key, list_ptr->key);
      strcpy(list_ptr->mod->value,  list_ptr->value);
      
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = list_ptr->prev;

      list->head[current_version] = list->head[current_version-1];
      return list_ptr;
    }
  else
    {

      node* newnode_parent = addNode(list_ptr->mod->key, list_ptr->mod->value);
    
      newnode_parent->next = newnode;

      if(list_ptr->mod->prev == NULL)
	{
	  list->head[current_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = update_left(list, list_ptr->mod->prev, newnode_parent, current_version);
    }

}



node* update_right(map* list, node* list_ptr, node* newnode, int current_version)
{

  if(list_ptr == NULL) return NULL;
    
  if(list_ptr->mod->version == unused)
    {
      strcpy(list_ptr->mod->key, list_ptr->key);
      strcpy(list_ptr->mod->value, list_ptr->value);
            
      list_ptr->mod->version = current_version;
      list_ptr->mod->prev = newnode;
      list_ptr->mod->next = list_ptr->next;

      return list_ptr;
    }
  else
    {

      node* newnode_parent = addNode(list_ptr->mod->key, list_ptr->mod->value);
      newnode_parent->prev = newnode;
      newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version);
    }

}



bool insert(map* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int current_version = list->current_version;
  char key[str_size], value[str_size];

  sscanf(str, "%[^,],%[^,]", key,value);
  
  node* newnode = addNode(key, value);
  
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
      
      strcpy(list_ptr->mod->key, list_ptr->key);
      strcpy(list_ptr->mod->value, list_ptr->value);
      
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
	  
	  node* trailNode = addNode(list_ptr->mod->key, list_ptr->mod->value);
	  trailNode->next = list_ptr->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
  return true;
}



bool update(map* list, char str[], int index)
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
      insert(list, str, index);
    }
  else
    {     
      if(list_ptr->mod->version == unused)
	{
	  current_version++;

	  char key[str_size], value[str_size];

	  sscanf(str, "%[^,],%[^,]", key,value);
	      
	  strcpy(list_ptr->mod->key, key);
	  strcpy(list_ptr->mod->value, value);
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
	      char key[str_size], value[str_size];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      node* newnode = addNode(key, value);

	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version);
	      newnode->prev = update_left(list, list_ptr->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      char key[str_size], value[str_size];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      node* newnode = addNode(key, value);

	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version);
	      list->head[current_version] = newnode;
	    }
	}

      list->current_version = current_version;
    }
  return true;
}





bool delete_map(map* list, int index)
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
      if(index == 0)
	{
	  if(list_ptr->mod->version == unused)
	    {
	      if(list_ptr->next->mod->version == unused)
		{  
		  current_version++;
		
		  strcpy(list_ptr->next->mod->key, list_ptr->next->key);
		  strcpy(list_ptr->next->mod->value, list_ptr->next->value);
		  
		  list_ptr->next->mod->version = current_version;

		  list_ptr->next->mod->next = list_ptr->next->next;
		  list_ptr->next->mod->prev = list_ptr->prev;

		  list->head[current_version] = list_ptr->next;
		}
	      else
		{
		  current_version++;

		  node* newnode = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value);

		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version);
	  	  
		  list->head[current_version] = newnode;
		}
	    }
	  else
	    {
	      if(list_ptr->mod->next->mod->version == unused)
		{  
		  current_version++;
		
		  strcpy(list_ptr->mod->next->mod->key, list_ptr->mod->next->key);
		  strcpy(list_ptr->mod->next->mod->value, list_ptr->mod->next->value);
		  
		  list_ptr->mod->next->mod->version = current_version;

		  list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
		  list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

		  list->head[current_version] = list_ptr->mod->next;
		}
	      else
		{
		  current_version++;

		  node* newnode = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value);

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

	      strcpy(list_ptr->prev->mod->key, list_ptr->prev->key);
	      strcpy(list_ptr->prev->mod->value, list_ptr->prev->value);
	      
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->prev->mod->key,list_ptr->prev->mod->value);
	      
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

	      strcpy(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->key);
	      strcpy(list_ptr->mod->prev->mod->value, list_ptr->mod->prev->value);

	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value);
	      
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

	      strcpy(list_ptr->prev->mod->key, list_ptr->prev->key);
	      strcpy(list_ptr->prev->mod->value, list_ptr->prev->value);
	      
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      strcpy(list_ptr->next->mod->key, list_ptr->next->key);
	      strcpy(list_ptr->next->mod->value, list_ptr->next->value);
	       
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = list_ptr->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;

	      node* newnode = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value);
	      
	      strcpy(list_ptr->prev->mod->key, list_ptr->prev->key);
	      strcpy(list_ptr->prev->mod->value, list_ptr->prev->value);
	      
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

	      node* newnode = addNode(list_ptr->prev->mod->key, list_ptr->prev->mod->value);
	      
	      strcpy(list_ptr->next->mod->key, list_ptr->next->key);
	      strcpy(list_ptr->next->mod->value, list_ptr->next->value);
	      
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      newnode->next = list_ptr->next;
	      newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
        
	      node* newnode_prev = addNode(list_ptr->prev->mod->key, list_ptr->prev->mod->value);
	      node* newnode_next = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value);

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

	      strcpy(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->key);
	      strcpy(list_ptr->mod->prev->mod->value, list_ptr->mod->prev->value);
	      
	      list_ptr->mod->prev->mod->version = current_version;

	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      strcpy(list_ptr->mod->next->mod->key, list_ptr->mod->next->key);
	      strcpy(list_ptr->mod->next->mod->value, list_ptr->mod->next->value);
	      
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;
	      	  
	      node* newnode = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value);
	  
	      strcpy(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->key);
	      strcpy(list_ptr->mod->prev->mod->value, list_ptr->mod->prev->value);

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
	      
	      node* newnode = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value);       

	      strcpy(list_ptr->mod->next->mod->key, list_ptr->mod->next->key);
	      strcpy(list_ptr->mod->next->mod->value, list_ptr->mod->next->value);
	      
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      newnode->next = list_ptr->mod->next;

	      newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
	      
	      node* newnode_prev = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value);
	      node* newnode_next = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value);

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

