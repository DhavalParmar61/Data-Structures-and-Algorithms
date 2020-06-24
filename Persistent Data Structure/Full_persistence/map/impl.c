#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"



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


node* addNode(char input_key[], char input_value[], int version)
{
  node* newnode = (node*) malloc(sizeof(node));
  strcpy(newnode->key, input_key);
  strcpy(newnode->value, input_value);
  newnode->next = NULL;
  newnode->prev = NULL;
  newnode->node_version = version;
  
  newnode->mod = (mod*) malloc(sizeof(mod));
  strcpy(newnode->mod->key, def);
  strcpy(newnode->mod->value, def);
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
  
  return newnode;
}

void find(map* list,char find_key[],int version)
{
    
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
	  if(!strcmp(list_ptr->mod->key, find_key))
	    {
	      printf("\nKey : %s, Value : %s\n", list_ptr->mod->key, list_ptr->mod->value);
	      return;
	    }
	  list_ptr = list_ptr->mod->next;
	}
      else
	{
	  if(!strcmp(list_ptr->key, find_key))
	    {
	      printf("\nKey : %s, Value : %s\n", list_ptr->key, list_ptr->value);
	      return;
	    }

	  list_ptr = list_ptr->next;
	}
    }
  
  printf("Key not found\n");
}




void print_map(map* list, int version)
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
      printf("Memory allocation error\n");
      return;
    }

  for(print_ptr = list->head[version]; print_ptr != NULL;)
    {
      if(print_ptr->node_version > version)
      	break;
      
      if((print_ptr->mod->version <= version) && (print_ptr->mod->version > unused))
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


node* update_parentleft(map* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      strcpy(list_ptr->mod->key, list_ptr->key);
      strcpy(list_ptr->mod->value,  list_ptr->value);
      
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = update_parentleft(list, list_ptr->prev, list_ptr, current_version, version);
 
      list->head[current_version] = list->head[version];
      return list_ptr;
    }
  else
    {
      node* newnode_parent;
                      
      if(list_ptr->mod->version <= version)
	{
	  newnode_parent = addNode(list_ptr->mod->key, list_ptr->mod->value, current_version);
	  newnode_parent->next = newnode;

	  if(list_ptr->mod->prev == NULL)
	    {
	      list->head[current_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = update_parentleft(list, list_ptr->mod->prev, newnode_parent, current_version, version);
	}
      else
	{
	  newnode_parent = addNode(list_ptr->key, list_ptr->value, current_version);
	  newnode_parent->next = newnode;

	  if(list_ptr->prev == NULL)
	    {
	      list->head[current_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = update_parentleft(list, list_ptr->prev, newnode_parent, current_version, version);
	}
      return newnode_parent;
    }

}



node* update_right(map* list, node* list_ptr, node* newnode, int current_version, int version)
{
  if(list_ptr == NULL) return NULL;

  if(list_ptr->node_version > version) return NULL;
  
  if(list_ptr->mod->version == unused)
    {
      strcpy(list_ptr->mod->key, list_ptr->key);
      strcpy(list_ptr->mod->value, list_ptr->value);
            
      list_ptr->mod->version = current_version;
      list_ptr->mod->prev = newnode;
      newnode->next = list_ptr;
      list_ptr->mod->next =  update_right(list, list_ptr->next, list_ptr, current_version, version);
      
      return list_ptr;
    }
  else
    {
      node* newnode_parent;

      if(list_ptr->mod->version <= version)
	{	  
	  newnode_parent = addNode(list_ptr->mod->key, list_ptr->mod->value, current_version);
	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version, version);
	}
      else
	{
	  newnode_parent = addNode(list_ptr->mod->key, list_ptr->mod->value, current_version);

	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->next, newnode_parent, current_version, version);
	}
      
      return newnode_parent;
    }

}



bool insert(map* list, char str[], int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }

  int index_count = 0;
  int current_version = list->current_version;

  if(version > current_version)
    {
      printf("Version does not exist\n");
      return false;
    }

  char key[str_size], value[str_size];

  sscanf(str, "%[^,],%[^,]", key,value);
  
  node* newnode = addNode(key, value, unused);
      
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

  if(list_ptr == NULL) index_count--;
  
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
	  newnode->prev = update_parentleft(list, list_ptr, newnode, current_version, version);
	}
      else
	{
	  newnode->next = list_ptr;
	  
	  strcpy(list_ptr->mod->key, list_ptr->key);
	  strcpy(list_ptr->mod->value, list_ptr->value);
      
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
	  if(list_ptr->mod->version <= version)
	    {
	      newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
	      newnode->prev = update_parentleft(list, list_ptr, newnode, current_version, version);
	    }
	  else
	    {
	      newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
	      newnode->prev = update_parentleft(list, list_ptr, newnode, current_version, version);
	    }
	}
      else
	{
	  node* trailNode;
	  if(list_ptr->mod->version <= version)
	    {
	      trailNode = addNode(list_ptr->mod->key, list_ptr->mod->value, current_version);
	      trailNode->next = update_right(list, list_ptr->mod->next, trailNode, current_version, version);	
	    }
	  else
	    {
	      trailNode = addNode(list_ptr->key, list_ptr->value, current_version);
	      trailNode->next = update_right(list, list_ptr->next, trailNode, current_version, version);	
	    }

	  trailNode->prev = newnode;
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
  return true;
}



bool update(map* list, char str[], int index, int version)
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

  if(list_ptr == NULL) index_count--;
  
  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      insert(list, str, index, version);
      return true;
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

	  list->head[current_version] = list->head[version];
	}
      else
	{
	  current_version++;


	  if(index != 0)
	    {
	      char key[str_size], value[str_size];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      node* newnode = addNode(key, value, current_version);

	      if(list_ptr->mod->version <= version)
		{
		  newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
		  newnode->prev = update_parentleft(list, list_ptr->mod->prev, newnode, current_version, version);
		}
	      else
		{
		  newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
		  newnode->prev = update_parentleft(list, list_ptr->prev, newnode, current_version, version);
		}
	    }
	  else
	    {
	      char key[str_size], value[str_size];

	      sscanf(str, "%[^,],%[^,]", key,value);
	      node* newnode = addNode(key, value, current_version);

	      if(list_ptr->mod->version <= version)
		newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
	      else
		newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
		
	      list->head[current_version] = newnode;
	    }
	}

      list->current_version = current_version;
    }
  return true;
}




bool delete_map(map* list, int index, int version)
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
   
  if((list->head[version]->next == NULL) && (list->head[version]->mod->next == NULL) || (version == 0))
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
	  if((list_ptr->mod->version == unused) || (list_ptr->mod->version > version))
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
		  node* newnode;
		  
		  if(list_ptr->next->mod->version <= version)
		    {
		      newnode = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value, current_version);
		      newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      newnode = addNode(list_ptr->next->key, list_ptr->next->value, current_version);
		      newnode->next = update_right(list, list_ptr->next->next, newnode, current_version, version);
		    }
		  
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

		  node* newnode;;

		  if(list_ptr->mod->next->mod->version <= version)
		    {
		      newnode = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value, current_version);
		      newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      newnode = addNode(list_ptr->mod->next->key, list_ptr->mod->next->value, current_version);
		      newnode->next = update_right(list, list_ptr->mod->next->next, newnode, current_version, version);
		    }
		  
		  list->head[current_version] = newnode;
		}
	    }
	  
	  list->current_version = current_version;
	  return true;
	}
      
      if((list_ptr->next == NULL) && (list_ptr->mod->version == unused) || (list_ptr->mod->version > version))
	{
	  if(list_ptr->prev->mod->version == unused)
	    {  
	      current_version++;

	      strcpy(list_ptr->prev->mod->key, list_ptr->prev->key);
	      strcpy(list_ptr->prev->mod->value, list_ptr->prev->value);

	      list_ptr->prev->mod->version = current_version;
	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else
	    {
	      current_version++;

	      node* newnode;
	      
	      if(list_ptr->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->prev->mod->key, list_ptr->prev->mod->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->prev->key, list_ptr->prev->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->prev->prev, newnode, current_version, version);

		  if(list_ptr->prev->prev == NULL) list->head[current_version] = newnode;
		}
	    }
 
	  list->current_version = current_version;
	  return true;
	}
      
      if((list_ptr->mod->next == NULL) && (list_ptr->mod->version != unused) && (list_ptr->mod->version <= version))
	{
	  if(list_ptr->mod->prev->mod->version == unused)
	    {  
	      current_version++;

	      strcpy(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->key);
	      strcpy(list_ptr->mod->prev->mod->value, list_ptr->mod->prev->value);

	      list_ptr->mod->prev->mod->version = current_version;
	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else
	    {
	      current_version++;

	      node* newnode;;

	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->prev->key, list_ptr->mod->prev->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->mod->prev->prev, newnode, current_version, version);

		    if(list_ptr->mod->prev->prev == NULL) list->head[current_version] = newnode;
		}
	    }

	  list->current_version = current_version;
	  return true;
	}
         

      if((list_ptr->mod->version == unused) || (list_ptr->mod->version > version))
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

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;
	      node* newnode;
	      
	      strcpy(list_ptr->prev->mod->key, list_ptr->prev->key);
	      strcpy(list_ptr->prev->mod->value, list_ptr->prev->value);
	      
	      list_ptr->prev->mod->version = current_version;
	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      if(list_ptr->next->mod->version <= version)
		{
		  newnode = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value, current_version);
		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  newnode = addNode(list_ptr->next->key, list_ptr->next->value, current_version);
		  newnode->next = update_right(list, list_ptr->next->next, newnode, current_version, version);
		}
	      
	      newnode->prev = list_ptr->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;
	      node* newnode;
	      
	      strcpy(list_ptr->next->mod->key, list_ptr->next->key);
	      strcpy(list_ptr->next->mod->value, list_ptr->next->value);
	      
	      list_ptr->next->mod->version = current_version;
	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      if(list_ptr->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->prev->mod->key, list_ptr->prev->mod->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->prev->key, list_ptr->prev->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->prev->prev, newnode, current_version, version);

		   if(list_ptr->prev->prev == NULL)  list->head[current_version] = newnode;
		}

	      newnode->next = list_ptr->next;
	    }
	  else
	    {
	      current_version++;     
	      node* newnode_prev;
	      node* newnode_next;

	      if(list_ptr->prev->mod->version <= version)
		{
		  newnode_prev = addNode(list_ptr->prev->mod->key, list_ptr->prev->mod->value, current_version);
		  newnode_prev->prev = update_parentleft(list, list_ptr->prev->mod->prev, newnode_prev, current_version, version);

		   if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(list_ptr->prev->key, list_ptr->prev->value, current_version);
		  newnode_prev->prev = update_parentleft(list, list_ptr->prev->prev, newnode_prev, current_version, version);

		   if(list_ptr->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      
	      if(list_ptr->next->mod->version <= version)
		{
		  newnode_next = addNode(list_ptr->next->mod->key, list_ptr->next->mod->value,current_version);
		  newnode_next->next = update_right(list, list_ptr->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  newnode_next = addNode(list_ptr->next->key, list_ptr->next->value, current_version);
		  newnode_next->next = update_right(list, list_ptr->next->next, newnode_next, current_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

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

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;    	  
	      node* newnode;

	      strcpy(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->key);
	      strcpy(list_ptr->mod->prev->mod->value, list_ptr->mod->prev->value);

	      list_ptr->mod->prev->mod->version = current_version;
	      
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;
	      list_ptr->mod->prev->mod->next = newnode; 
	     
	      
	      if(list_ptr->mod->next->mod->version <= version)
		{
		  newnode = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value, current_version);
		  newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->next->key, list_ptr->mod->next->value, current_version);
		  newnode->next = update_right(list, list_ptr->mod->next->next, newnode, current_version, version);
		}

	      newnode->prev = list_ptr->mod->prev;
	      
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;      	      
	      node* newnode;       

	      strcpy(list_ptr->mod->next->mod->key, list_ptr->mod->next->key);
	      strcpy(list_ptr->mod->next->mod->value, list_ptr->mod->next->value);
	     
	      list_ptr->mod->next->mod->version = current_version;
	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->prev->key, list_ptr->mod->prev->value, current_version);
		  newnode->prev = update_parentleft(list, list_ptr->mod->prev->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->prev == NULL)  list->head[current_version] = newnode;
		}

	      newnode->next = list_ptr->mod->next;
	    }
	   else
	    {
	      current_version++;	        
	      node* newnode_prev;
	      node* newnode_next;

	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  newnode_prev = addNode(list_ptr->mod->prev->mod->key, list_ptr->mod->prev->mod->value,current_version);
		  newnode_prev->prev = update_parentleft(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version, version);

		   if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(list_ptr->mod->prev->key, list_ptr->mod->prev->value, current_version);
		  newnode_prev->prev = update_parentleft(list, list_ptr->mod->prev->prev, newnode_prev, current_version, version);

		  if(list_ptr->mod->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      
	      if(list_ptr->mod->next->mod->version <= version)
		{
		  newnode_next = addNode(list_ptr->mod->next->mod->key, list_ptr->mod->next->mod->value, current_version);
		  newnode_next->next = update_right(list, list_ptr->mod->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  newnode_next = addNode(list_ptr->mod->next->key, list_ptr->mod->next->value, current_version);
		  newnode_next->next = update_right(list, list_ptr->mod->next->next, newnode_next, current_version, version);
		}

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;
	    }
	  	  
	}
      
      list->current_version = current_version;
    }
  return true;
}

