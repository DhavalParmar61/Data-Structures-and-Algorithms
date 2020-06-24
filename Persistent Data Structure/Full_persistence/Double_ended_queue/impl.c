#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "header.h"


deque* initialize()
{
  deque* newlist = (deque*) malloc(sizeof(deque));

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

void print_dequeue(deque* list, int version)
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


node* update_left(deque* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      list_ptr->mod->prev = update_left(list, list_ptr->prev, list_ptr, current_version, version);
	
      list->head[current_version] = list->head[version];
      return list_ptr;
    }
  else
    {
       node* newnode_parent;

    if(list_ptr->mod->version <= version)
	{
	  newnode_parent = addNode(list_ptr->mod->data, current_version);
	  newnode_parent->next = newnode;

	  if(list_ptr->mod->prev == NULL)
	    {
	      list->head[current_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = update_left(list, list_ptr->mod->prev, newnode_parent, current_version, version);
	}
      else
	{
	  newnode_parent = addNode(list_ptr->data, current_version);
	  newnode_parent->next = newnode;

	  if(list_ptr->prev == NULL)
	    {
	      list->head[current_version] = newnode_parent;
	      return newnode_parent;
	    }

	  newnode_parent->prev = update_left(list, list_ptr->prev, newnode_parent, current_version, version);
	}
      return newnode_parent;
    }

}



node* update_right(deque* list, node* list_ptr, node* newnode, int current_version, int version)
{
  if(list_ptr == NULL) return NULL;

  if(list_ptr->node_version > version) return NULL;
  
  if(list_ptr->mod->version == unused)
    {
      list_ptr->mod->data = list_ptr->data;
      list_ptr->mod->version = current_version;
      list_ptr->mod->prev = newnode;
      list_ptr->mod->next =  update_right(list, list_ptr->next, list_ptr, current_version, version);

      return list_ptr;
    }
  else
    {
      node* newnode_parent;
      
      if(list_ptr->mod->version <= version)
	{	  
	  newnode_parent = addNode(list_ptr->mod->data, current_version);
	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version, version);
	}
      else
	{
	  newnode_parent = addNode(list_ptr->data, current_version);

	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->next, newnode_parent, current_version, version);
	}
      return newnode_parent;
    }

}



bool insert(deque* list, int data, int index, int version)
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
	list_ptr_prev = list_ptr;
	    
      if(index_count == index) break;
      
      if((list_ptr->mod->version <= version) && list_ptr->mod->version != unused)
	list_ptr = list_ptr->mod->next;
      else
	list_ptr = list_ptr->next;

    }

  if(list_ptr == NULL) index_count--;
    
  if(list->head[current_version] == NULL)
    {
      list->head[current_version] = newnode;
      newnode->node_version = current_version;
      return true;
    }
  
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
	  list_ptr->mod->data = list_ptr->data;
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
	      newnode->prev = update_left(list, list_ptr, newnode, current_version, version);
	    }
	  else
	    {
	      newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
	      newnode->prev = update_left(list, list_ptr, newnode, current_version, version);
	    }
	}
      else
	{
	  node* trailNode;
	  if(list_ptr->mod->version <= version)
	    {
	      trailNode = addNode(list_ptr->mod->data, current_version);
	      trailNode->next = update_right(list, list_ptr->mod->next, trailNode, current_version, version);	
	    }
	  else
	    {
	      trailNode = addNode(list_ptr->data, current_version);
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




bool delete_list(deque* list, int index, int version)
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
		
		  list_ptr->next->mod->data = list_ptr->next->data;
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
		      newnode = addNode(list_ptr->next->mod->data, current_version);
		      newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      newnode = addNode(list_ptr->next->data, current_version);
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
		
		  list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
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
		      newnode = addNode(list_ptr->mod->next->mod->data, current_version);
		      newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      newnode = addNode(list_ptr->mod->next->data, current_version);
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

	      list_ptr->prev->mod->data = list_ptr->prev->data;
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
		  newnode = addNode(list_ptr->prev->mod->data, current_version);
		  newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{ 
		  newnode = addNode(list_ptr->prev->data, current_version);
		  newnode->prev = update_left(list, list_ptr->prev->prev, newnode, current_version, version);

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

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
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
		  newnode = addNode(list_ptr->mod->prev->mod->data, current_version);
		  newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->prev->data, current_version);
		  newnode->prev = update_left(list, list_ptr->mod->prev->prev, newnode, current_version, version);

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
	      node* newnode;
	      
	      list_ptr->prev->mod->data = list_ptr->prev->data;
	      list_ptr->prev->mod->version = current_version;

	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      if(list_ptr->next->mod->version <= version)
		{
		  newnode = addNode(list_ptr->next->mod->data, current_version);
		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  newnode = addNode(list_ptr->next->data, current_version);
		  newnode->next = update_right(list, list_ptr->next->next, newnode, current_version, version);
		}
	      
	      newnode->prev = list_ptr->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;
	      node* newnode;
	      
	      list_ptr->next->mod->data = list_ptr->next->data;
	      list_ptr->next->mod->version = current_version;

	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      if(list_ptr->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->prev->mod->data, current_version);
		  newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->prev->data, current_version);
		  newnode->prev = update_left(list, list_ptr->prev->prev, newnode, current_version, version);

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
		  newnode_prev = addNode(list_ptr->prev->mod->data, current_version);
		  newnode_prev->prev = update_left(list, list_ptr->prev->mod->prev, newnode_prev, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(list_ptr->prev->data, current_version);
		  newnode_prev->prev = update_left(list, list_ptr->prev->prev, newnode_prev, current_version, version);

		  if(list_ptr->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      
	      if(list_ptr->next->mod->version <= version)
		{
		  newnode_next = addNode(list_ptr->next->mod->data, current_version);
		  newnode_next->next = update_right(list, list_ptr->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  newnode_next = addNode(list_ptr->next->data, current_version);
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
	      node* newnode;

	      list_ptr->mod->prev->mod->data = list_ptr->mod->prev->data;
	      list_ptr->mod->prev->mod->version = current_version;
	      
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;
	      list_ptr->mod->prev->mod->next = newnode; 
	     
	      
	      if(list_ptr->mod->next->mod->version <= version)
		{
		  newnode = addNode(list_ptr->mod->next->mod->data, current_version);
		  newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->next->data, current_version);
		  newnode->next = update_right(list, list_ptr->mod->next->next, newnode, current_version, version);
		}

	      newnode->prev = list_ptr->mod->prev;
	      
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;  	      
	      node* newnode;       

	      list_ptr->mod->next->mod->data = list_ptr->mod->next->data;
	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  newnode = addNode(list_ptr->mod->prev->mod->data, current_version);
		  newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  newnode = addNode(list_ptr->mod->prev->data, current_version);
		  newnode->prev = update_left(list, list_ptr->mod->prev->prev, newnode, current_version, version);

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
		  newnode_prev = addNode(list_ptr->mod->prev->mod->data, current_version);
		  newnode_prev->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  newnode_prev = addNode(list_ptr->mod->prev->data, current_version);
		  newnode_prev->prev = update_left(list, list_ptr->mod->prev->prev, newnode_prev, current_version, version);

		  if(list_ptr->mod->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      
	      if(list_ptr->mod->next->mod->version <= version)
		{
		  newnode_next = addNode(list_ptr->mod->next->mod->data, current_version);
		  newnode_next->next = update_right(list, list_ptr->mod->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  newnode_next = addNode(list_ptr->mod->next->data, current_version);
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


bool isempty(deque* deque, int version)
{
  if(deque->head[version] == NULL) return true;
  else false;
}


bool insert_front(deque* deque, int data, int version)
{
  return (insert(deque, data, 0, version));
}


bool insert_rear(deque* deque, int data, int version)
{
  node* list_ptr;
  int last_index = 0;

  for(list_ptr = deque->head[version]; list_ptr != NULL; last_index++)
    {
     if(list_ptr->node_version > version)
      	break;
      
     if((list_ptr->mod->version <= version) && (list_ptr->mod->version > unused))
       list_ptr = list_ptr->mod->next;
     else
       list_ptr = list_ptr->next;
    }
    
  return (insert(deque, data, last_index, version));
}


bool delete_front(deque* deque, int version)
{
  return delete_list(deque, 0, version);
}
  
bool delete_rear(deque* deque, int version)
{  
  node* list_ptr;
  int last_index = 0;

  for(list_ptr = deque->head[version]; list_ptr != NULL; last_index++)
    {
     if(list_ptr->node_version > version)
      	break;
      
     if((list_ptr->mod->version <= version) && (list_ptr->mod->version > unused))
       list_ptr = list_ptr->mod->next;
     else
       list_ptr = list_ptr->next;
    }
  
  return delete_list(deque, last_index-1, version);
}
