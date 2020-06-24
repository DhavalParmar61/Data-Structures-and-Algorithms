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
  
  newnode->int_data = data;
  newnode->float_data = def;
  newnode->char_data = def;
  newnode->double_data = def;
  
  newnode->identifier = malloc(sizeof(str_size));
  newnode->identifier = "int";
  newnode->node_version = version;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->int_data = def;
  newnode->mod->float_data = def;
  newnode->mod->char_data = def;
  newnode->mod->double_data = def;
  
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


node* float_addNode(float data, int version)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = data;
  newnode->char_data = def;
  newnode->double_data = def;
  
  newnode->identifier = malloc(sizeof(str_size));
  newnode->identifier = "float";
  newnode->node_version = version;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->int_data = def;
  newnode->mod->float_data = def;
  newnode->mod->char_data = def;
  newnode->mod->double_data = def;
  
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


node* char_addNode(char data, int version)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = def;
  newnode->char_data = data;
  newnode->double_data = def;
  
  newnode->identifier = malloc(sizeof(str_size));
  newnode->identifier = "char";
  newnode->node_version = version;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->int_data = def;
  newnode->mod->float_data = def;
  newnode->mod->char_data = def;
  newnode->mod->double_data = def;
  
  newnode->mod->version = unused;
  newnode->mod->next = NULL;
  newnode->mod->prev = NULL;
	
  return newnode;
}


node* double_addNode(double data, int version)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = def;
  newnode->char_data = def;
  newnode->double_data = data;
  
  newnode->identifier = malloc(sizeof(str_size));
  newnode->identifier = "double";
  newnode->node_version = version;
  newnode->next = NULL;
  newnode->prev = NULL;
	
  newnode->mod = (mod*) malloc(sizeof(mod));
  newnode->mod->int_data = def;
  newnode->mod->float_data = def;
  newnode->mod->char_data = def;
  newnode->mod->double_data = def;
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
      printf("Memory allocation error");
      return;
    }

  for(print_ptr = list->head[version]; print_ptr != NULL; )
    {
      if((print_ptr->mod->version <= version) && (print_ptr->mod->version != unused))
	{
	  switch(print_ptr->mod->identifier[0])
	    {
	    case 'i': {
	      printf("%d ", print_ptr->mod->int_data);
	      print_ptr = print_ptr->mod->next;
	      break;
	    }
	    case 'f' : {
	      printf("%f ", print_ptr->mod->float_data);
	      print_ptr = print_ptr->mod->next;
	      break;
	    }
	    case 'c': {
	      printf("%c ", print_ptr->mod->char_data);
	      print_ptr = print_ptr->mod->next;
	      break;
	    }
	    case 'd':{
	      printf("%lf ", print_ptr->mod->double_data);
	      print_ptr = print_ptr->mod->next;
	      break;
	    }
	    default :{
	      print_ptr = print_ptr->mod->next;
	    }
	    }
	}
      else
	{
	  switch(print_ptr->identifier[0])
	    {
	    case 'i': {
	      printf("%d ", print_ptr->int_data);
	      print_ptr = print_ptr->next;
	      break;
	    }
	    case 'f' : {
	      printf("%f ", print_ptr->float_data);
	      print_ptr = print_ptr->next;
	      break;
	    }
	    case 'c': {
	      printf("%c ", print_ptr->char_data);
	      print_ptr = print_ptr->next;
	      break;
	    }
	    case 'd':{
	      printf("%lf ", print_ptr->double_data);
	      print_ptr = print_ptr->next;
	      break;
	    }
	    default :{
	      print_ptr = print_ptr->next;
	    }
	    }
	}
    }
}




node* update_left(list* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;

  if(list_ptr->mod->version == unused)
    {
      switch(list_ptr->identifier[0])
	{
	case 'i': {
	  list_ptr->mod->int_data = list_ptr->int_data;
	  list_ptr->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  list_ptr->mod->float_data = list_ptr->float_data;
	  list_ptr->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  list_ptr->mod->char_data = list_ptr->char_data;
	  list_ptr->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  list_ptr->mod->double_data = list_ptr->double_data;
	  list_ptr->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      list_ptr->mod->version = current_version;
      list_ptr->mod->next = newnode;
      newnode->prev = list_ptr;
      list_ptr->mod->prev = update_left(list, list_ptr->prev, list_ptr, current_version, version);
      
      list->head[current_version] = list->head[version];
      return list_ptr;
    }
  else
    {
      node* newnode_parent;
                
      if(list_ptr->mod->version <= version)
	{
	  switch(list_ptr->mod->identifier[0])
	    {
	    case 'i': {
	      newnode_parent = addNode(list_ptr->mod->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      newnode_parent = float_addNode(list_ptr->mod->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      newnode_parent = char_addNode(list_ptr->mod->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      newnode_parent = double_addNode(list_ptr->mod->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }
       
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
	  switch(list_ptr->identifier[0])
	    {
	    case 'i': {
	      newnode_parent = addNode(list_ptr->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      newnode_parent = float_addNode(list_ptr->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      newnode_parent = char_addNode(list_ptr->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      newnode_parent = double_addNode(list_ptr->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }
	  
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





node* update_right(list* list, node* list_ptr, node* newnode, int current_version, int version)
{

  if(list_ptr == NULL) return NULL;
  
  if(list_ptr->node_version > version) return NULL;
    
  if(list_ptr->mod->version == unused)
    {
      switch(list_ptr->identifier[0])
	{
	case 'i': {
	  list_ptr->mod->int_data = list_ptr->int_data;
	  list_ptr->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  list_ptr->mod->float_data = list_ptr->float_data;
	  list_ptr->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  list_ptr->mod->char_data = list_ptr->char_data;
	  list_ptr->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  list_ptr->mod->double_data = list_ptr->double_data;
	  list_ptr->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

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
	  
	  switch(list_ptr->mod->identifier[0])
	    {
	    case 'i': {
	      newnode_parent = addNode(list_ptr->mod->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      newnode_parent = float_addNode(list_ptr->mod->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      newnode_parent = char_addNode(list_ptr->mod->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      newnode_parent = double_addNode(list_ptr->mod->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->mod->next, newnode_parent, current_version, version);
	}
      else
	{

	  switch(list_ptr->identifier[0])
	    {
	    case 'i': {
	      newnode_parent = addNode(list_ptr->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      newnode_parent = float_addNode(list_ptr->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      newnode_parent = char_addNode(list_ptr->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      newnode_parent = double_addNode(list_ptr->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }
	  
	  newnode_parent->prev = newnode;
	  newnode_parent->next = update_right(list, list_ptr->next, newnode_parent, current_version, version);
	}
      
      
      return newnode_parent;
    }

}




bool insert(list* list, char str[], int index, int version)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int current_version = list->current_version;

  node* newnode;
  switch(str[0])
    {
    case 'i': {
      int int_data;
      sscanf(str, "%*[^','],%d", &int_data);
      newnode = addNode(int_data, unused);
      break;
    }
    case 'f': {
      float float_data;
      sscanf(str, "%*[^','],%f", &float_data);
      newnode = float_addNode(float_data, unused);
      break;
    }
    case 'c': {
      char char_data;
      sscanf(str, "%*[^','],%c", &char_data);
      newnode = char_addNode(char_data, unused);
      break;
    }
    case 'd': {
      double double_data;
      sscanf(str, "%*[^','],%lf", &double_data);
      newnode = double_addNode(double_data, unused);
      break;
    }
    default: {
      printf("Invalid datatype\n");
    }
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

  if(list_ptr == NULL) index_count--;

  if(list->head[current_version] == NULL)
    {
      list->head[current_version] = newnode;
      newnode->node_version = current_version;
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

  if(list_ptr == NULL) index_count--;
  
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
	  switch(list_ptr->mod->identifier[0])
	    {
	    case 'i': {
	      trailNode = addNode(list_ptr->mod->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      trailNode = float_addNode(list_ptr->mod->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      trailNode = char_addNode(list_ptr->mod->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      trailNode = double_addNode(list_ptr->mod->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }
	      
	      trailNode->next = update_right(list, list_ptr->mod->next, trailNode, current_version, version);	
	    }
	  else
	    {
	      switch(list_ptr->mod->identifier[0])
	    {
	    case 'i': {
	      trailNode = addNode(list_ptr->int_data, current_version);
	      break;
	    }
	    case 'f': {
	      trailNode = float_addNode(list_ptr->float_data, current_version);
	      break;
	    }
	    case 'c': {
	      trailNode = char_addNode(list_ptr->char_data, current_version);
	      break;
	    }
	    case 'd': {
	      trailNode = double_addNode(list_ptr->double_data, current_version);
	      break;
	    }
	    default: {
	      ;
	    }
	    }
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




bool update(list* list, char str[], int index, int version)
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
    }
  else
    {
      char type[str_size];
      
      if(list_ptr->mod->version == unused)
	{  
	  current_version++;

	  switch(str[0])
	    {
	    case 'i': {
	      int int_data;
	      sscanf(str, "%*[^','],%d", &int_data);
	      list_ptr->mod->int_data = int_data;
	      list_ptr->mod->identifier = "int";
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      list_ptr->mod->float_data = float_data;
	      list_ptr->mod->identifier = "float";
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data);
	      list_ptr->mod->char_data = char_data;
	      list_ptr->mod->identifier = "char";
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      list_ptr->mod->double_data = double_data;
	      list_ptr->mod->identifier = "double";
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  list_ptr->mod->version = current_version;
	  list_ptr->mod->next = list_ptr->next;
	  list_ptr->mod->prev = list_ptr->prev;

	  list->head[current_version] = list->head[version];
	}
      else
	{
	  current_version++;
	  
	  node* newnode;
	  switch(str[0])
	    {
	    case 'i': {
	      int int_data;
	      sscanf(str, "%*[^','],%d", &int_data);
	      newnode = addNode(int_data, current_version);
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      newnode = float_addNode(float_data, current_version);
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data); 
	      newnode = char_addNode(char_data, current_version);
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      newnode = double_addNode(double_data, current_version);
	      break;
	    }
	    default: {
	      printf("Invalid datatype\n");
	    }
	    }  
  
	  
	  if(index != 0)
	    {
	      if(list_ptr->mod->version <= version)
		{
		  newnode->next = update_right(list, list_ptr->mod->next, newnode, current_version, version);
		  newnode->prev = update_left(list, list_ptr->mod->prev, newnode, current_version, version);
		}
	      else
		{
		  newnode->next = update_right(list, list_ptr->next, newnode, current_version, version);
		  newnode->prev = update_left(list, list_ptr->prev, newnode, current_version, version);
		}
	    }
	  else
	    {
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
	
		  switch(list_ptr->next->identifier[0])
		    {
		    case 'i': {
		      list_ptr->next->mod->int_data = list_ptr->next->int_data;
		      list_ptr->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_ptr->next->mod->float_data = list_ptr->next->float_data;
		      list_ptr->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_ptr->next->mod->char_data = list_ptr->next->char_data;
		      list_ptr->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_ptr->next->mod->double_data = list_ptr->next->double_data;
		      list_ptr->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

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
		      switch(list_ptr->next->mod->identifier[0])
			{
			case 'i': {
			  newnode = addNode(list_ptr->next->mod->int_data, current_version);
			  break;
			}
			case 'f': {
			  newnode = float_addNode(list_ptr->next->mod->float_data, current_version);
			  break;
			}
			case 'c': {
			  newnode = char_addNode(list_ptr->next->mod->char_data, current_version);
			  break;
			}
			case 'd': {
			  newnode = double_addNode(list_ptr->next->mod->double_data, current_version);
			  break;
			}
			default: {
			  ;
			}
			}
		      newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      switch(list_ptr->next->identifier[0])
			{
			case 'i': {
			  newnode = addNode(list_ptr->next->int_data, current_version);
			  break;
			}
			case 'f': {
			  newnode = float_addNode(list_ptr->next->float_data, current_version);
			  break;
			}
			case 'c': {
			  newnode = char_addNode(list_ptr->next->char_data, current_version);
			  break;
			}
			case 'd': {
			  newnode = double_addNode(list_ptr->next->double_data, current_version);
			  break;
			}
			default: {
			  ;
			}
			}
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

		  switch(list_ptr->mod->next->identifier[0])
		    {
		    case 'i': {
		      list_ptr->mod->next->mod->int_data = list_ptr->mod->next->int_data;
		      list_ptr->mod->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_ptr->mod->next->mod->float_data = list_ptr->mod->next->float_data;
		      list_ptr->mod->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_ptr->mod->next->mod->char_data = list_ptr->mod->next->char_data;
		      list_ptr->mod->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_ptr->mod->next->mod->double_data = list_ptr->mod->next->double_data;
		      list_ptr->mod->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  list_ptr->mod->next->mod->version = current_version;
		  list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
		  list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

		  list->head[current_version] = list_ptr->mod->next;
		}
	      else
		{
		  current_version++;

		  node* newnode;
		  if(list_ptr->mod->next->mod->version <= version)
		    {
		      switch(list_ptr->mod->next->mod->identifier[0])
			{
			case 'i': {
			  newnode = addNode(list_ptr->mod->next->mod->int_data, current_version);
			  break;
			}
			case 'f': {
			  newnode = float_addNode(list_ptr->mod->next->mod->float_data, current_version);
			  break;
			}
			case 'c': {
			  newnode = char_addNode(list_ptr->mod->next->mod->char_data, current_version);
			  break;
			}
			case 'd': {
			  newnode = double_addNode(list_ptr->mod->next->mod->double_data, current_version);
			  break;
			}
			default: {
			  ;
			}
			}
		      newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		    }
		  else
		    {
		      switch(list_ptr->mod->next->identifier[0])
			{
			case 'i': {
			  newnode = addNode(list_ptr->mod->next->int_data, current_version);
			  break;
			}
			case 'f': {
			  newnode = float_addNode(list_ptr->mod->next->float_data, current_version);
			  break;
			}
			case 'c': {
			  newnode = char_addNode(list_ptr->mod->next->char_data, current_version);
			  break;
			}
			case 'd': {
			  newnode = double_addNode(list_ptr->mod->next->double_data, current_version);
			  break;
			}
			default: {
			  ;
			}
			}
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

	      switch(list_ptr->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->prev->mod->int_data = list_ptr->prev->int_data;
		  list_ptr->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->prev->mod->float_data = list_ptr->prev->float_data;
		  list_ptr->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->prev->mod->char_data = list_ptr->prev->char_data;
		  list_ptr->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->prev->mod->double_data = list_ptr->prev->double_data;
		  list_ptr->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
 
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
		  switch(list_ptr->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      
		  newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{
		  switch(list_ptr->prev->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      
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

	      switch(list_ptr->mod->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->mod->prev->mod->int_data = list_ptr->mod->prev->int_data;
		  list_ptr->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->mod->prev->mod->float_data = list_ptr->mod->prev->float_data;
		  list_ptr->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->mod->prev->mod->char_data = list_ptr->mod->prev->char_data;
		  list_ptr->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->mod->prev->mod->double_data = list_ptr->mod->prev->double_data;
		  list_ptr->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      list_ptr->mod->prev->mod->version = current_version;
	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else
	    {
	      current_version++;

	      node* newnode;
	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  switch(list_ptr->mod->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	      
		  newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL) list->head[current_version] = newnode;
		}
	      else
		{
		  switch(list_ptr->mod->prev->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	      
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

	      switch(list_ptr->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->prev->mod->int_data = list_ptr->prev->int_data;
		  list_ptr->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->prev->mod->float_data = list_ptr->prev->float_data;
		  list_ptr->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->prev->mod->char_data = list_ptr->prev->char_data;
		  list_ptr->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->prev->mod->double_data = list_ptr->prev->double_data;
		  list_ptr->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_ptr->prev->mod->version = current_version;
	      list_ptr->prev->mod->next = list_ptr->next;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;

	      switch(list_ptr->next->identifier[0])
		{
		case 'i': {
		  list_ptr->next->mod->int_data = list_ptr->next->int_data;
		  list_ptr->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->next->mod->float_data = list_ptr->next->float_data;
		  list_ptr->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->next->mod->char_data = list_ptr->next->char_data;
		  list_ptr->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->next->mod->double_data = list_ptr->next->double_data;
		  list_ptr->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_ptr->next->mod->version = current_version;
	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = list_ptr->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version == unused) && (list_ptr->next->mod->version != unused))
	    {
	      current_version++;
	      
	      switch(list_ptr->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->prev->mod->int_data = list_ptr->prev->int_data;
		  list_ptr->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->prev->mod->float_data = list_ptr->prev->float_data;
		  list_ptr->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->prev->mod->char_data = list_ptr->prev->char_data;
		  list_ptr->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->prev->mod->double_data = list_ptr->prev->double_data;
		  list_ptr->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      node* newnode; 

	      list_ptr->prev->mod->version = current_version;
	      list_ptr->prev->mod->next = newnode;
	      list_ptr->prev->mod->prev = list_ptr->prev->prev;
	      newnode->prev = list_ptr->prev;
	      
	      if(list_ptr->next->mod->version <= version)
		{
		  switch(list_ptr->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->next->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->next->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->next->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->next->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		
		  newnode->next = update_right(list, list_ptr->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  switch(list_ptr->next->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->next->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->next->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->next->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->next->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		
		  newnode->next = update_right(list, list_ptr->next->next, newnode, current_version, version);
		}
	       
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->prev->mod->version != unused) && (list_ptr->next->mod->version == unused))
	    {
	      current_version++;

	      switch(list_ptr->next->identifier[0])
		{
		case 'i': {
		  list_ptr->next->mod->int_data = list_ptr->next->int_data;
		  list_ptr->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->next->mod->float_data = list_ptr->next->float_data;
		  list_ptr->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->next->mod->char_data = list_ptr->next->char_data;
		  list_ptr->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->next->mod->double_data = list_ptr->next->double_data;
		  list_ptr->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      node* newnode;
	      list_ptr->next->mod->version = current_version;
	      list_ptr->next->mod->next = list_ptr->next->next;
	      list_ptr->next->mod->prev = newnode;

	      if(list_ptr->prev->mod->version <= version)
		{
		  switch(list_ptr->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      
		  newnode->prev = update_left(list, list_ptr->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  switch(list_ptr->prev->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      
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
		  switch(list_ptr->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode_prev = addNode(list_ptr->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_prev = float_addNode(list_ptr->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_prev = char_addNode(list_ptr->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_prev = double_addNode(list_ptr->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		  newnode_prev->prev = update_left(list, list_ptr->prev->mod->prev, newnode_prev, current_version, version);

		  if(list_ptr->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  switch(list_ptr->prev->identifier[0])
		    {
		    case 'i': {
		      newnode_prev = addNode(list_ptr->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_prev = float_addNode(list_ptr->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_prev = char_addNode(list_ptr->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_prev = double_addNode(list_ptr->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		  newnode_prev->prev = update_left(list, list_ptr->prev->prev, newnode_prev, current_version, version);

		  if(list_ptr->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}

	      if(list_ptr->next->mod->version <= version)
		{
		  switch(list_ptr->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode_next = addNode(list_ptr->next->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_next = float_addNode(list_ptr->next->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_next = char_addNode(list_ptr->next->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_next = double_addNode(list_ptr->next->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	      
		  newnode_next->next = update_right(list, list_ptr->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  switch(list_ptr->next->identifier[0])
		    {
		    case 'i': {
		      newnode_next = addNode(list_ptr->next->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_next = float_addNode(list_ptr->next->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_next = char_addNode(list_ptr->next->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_next = double_addNode(list_ptr->next->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	      
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
	     
	      switch(list_ptr->mod->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->mod->prev->mod->int_data = list_ptr->mod->prev->int_data;
		  list_ptr->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->mod->prev->mod->float_data = list_ptr->mod->prev->float_data;
		  list_ptr->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->mod->prev->mod->char_data = list_ptr->mod->prev->char_data;
		  list_ptr->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->mod->prev->mod->double_data = list_ptr->mod->prev->double_data;
		  list_ptr->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_ptr->mod->prev->mod->version = current_version;
	      list_ptr->mod->prev->mod->next = list_ptr->mod->next;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      switch(list_ptr->mod->next->identifier[0])
		{
		case 'i': {
		  list_ptr->mod->next->mod->int_data = list_ptr->mod->next->int_data;
		  list_ptr->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->mod->next->mod->float_data = list_ptr->mod->next->float_data;
		  list_ptr->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->mod->next->mod->char_data = list_ptr->mod->next->char_data;
		  list_ptr->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->mod->next->mod->double_data = list_ptr->mod->next->double_data;
		  list_ptr->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_ptr->mod->next->mod->version = current_version;

	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = list_ptr->mod->prev;

	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version == unused) && (list_ptr->mod->next->mod->version != unused))
	    {
	      current_version++;
	      
	      switch(list_ptr->mod->prev->identifier[0])
		{
		case 'i': {
		  list_ptr->mod->prev->mod->int_data = list_ptr->mod->prev->int_data;
		  list_ptr->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->mod->prev->mod->float_data = list_ptr->mod->prev->float_data;
		  list_ptr->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->mod->prev->mod->char_data = list_ptr->mod->prev->char_data;
		  list_ptr->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->mod->prev->mod->double_data = list_ptr->mod->prev->double_data;
		  list_ptr->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	 
	      node* newnode;
	      list_ptr->mod->prev->mod->version = current_version;
	      list_ptr->mod->prev->mod->next = newnode;
	      list_ptr->mod->prev->mod->prev = list_ptr->mod->prev->prev;

	      if(list_ptr->mod->next->mod->version <= version)
		{
		  switch(list_ptr->mod->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->next->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->next->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->next->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->next->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	 
		  newnode->next = update_right(list, list_ptr->mod->next->mod->next, newnode, current_version, version);
		}
	      else
		{
		  switch(list_ptr->mod->next->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->next->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->next->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->next->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->next->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      	 
		  newnode->next = update_right(list, list_ptr->mod->next->next, newnode, current_version, version);
		}
	       
	      newnode->prev = list_ptr->mod->prev;
			      
	      list->head[current_version] = list->head[version];
	    }
	  else if((list_ptr->mod->prev->mod->version != unused) && (list_ptr->mod->next->mod->version == unused))
	    {
	      current_version++;

	      switch(list_ptr->mod->next->identifier[0])
		{
		case 'i': {
		  list_ptr->mod->next->mod->int_data = list_ptr->mod->next->int_data;
		  list_ptr->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_ptr->mod->next->mod->float_data = list_ptr->mod->next->float_data;
		  list_ptr->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_ptr->mod->next->mod->char_data = list_ptr->mod->next->char_data;
		  list_ptr->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_ptr->mod->next->mod->double_data = list_ptr->mod->next->double_data;
		  list_ptr->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      node* newnode;
	      list_ptr->mod->next->mod->version = current_version;
	      list_ptr->mod->next->mod->next = list_ptr->mod->next->next;
	      list_ptr->mod->next->mod->prev = newnode;

	      if(list_ptr->mod->prev->mod->version <= version)
		{
		  switch(list_ptr->mod->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  newnode->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode;
		}
	      else
		{
		  switch(list_ptr->mod->prev->identifier[0])
		    {
		    case 'i': {
		      newnode = addNode(list_ptr->mod->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_ptr->mod->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_ptr->mod->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_ptr->mod->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

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
		  switch(list_ptr->mod->prev->mod->identifier[0])
		    {
		    case 'i': {
		      newnode_prev = addNode(list_ptr->mod->prev->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_prev = float_addNode(list_ptr->mod->prev->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_prev = char_addNode(list_ptr->mod->prev->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_prev = double_addNode(list_ptr->mod->prev->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		  newnode_prev->prev = update_left(list, list_ptr->mod->prev->mod->prev, newnode_prev, current_version, version);

		  if(list_ptr->mod->prev->mod->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	      else
		{
		  switch(list_ptr->mod->prev->identifier[0])
		    {
		    case 'i': {
		      newnode_prev = addNode(list_ptr->mod->prev->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_prev = float_addNode(list_ptr->mod->prev->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_prev = char_addNode(list_ptr->mod->prev->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_prev = double_addNode(list_ptr->mod->prev->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		  newnode_prev->prev = update_left(list, list_ptr->mod->prev->prev, newnode_prev, current_version, version);

		  if(list_ptr->mod->prev->prev == NULL)  list->head[current_version] = newnode_prev;
		}
	    
	      
	      if(list_ptr->mod->prev->mod->prev == NULL)
	      	list->head[current_version] = newnode_prev;
	      

	      if(list_ptr->mod->next->mod->version <= version)
		{
		  switch(list_ptr->mod->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode_next = addNode(list_ptr->mod->next->mod->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_next = float_addNode(list_ptr->mod->next->mod->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_next = char_addNode(list_ptr->mod->next->mod->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_next = double_addNode(list_ptr->mod->next->mod->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
		  newnode_next->next = update_right(list, list_ptr->mod->next->mod->next, newnode_next, current_version, version);
		}
	      else
		{
		  switch(list_ptr->mod->next->identifier[0])
		    {
		    case 'i': {
		      newnode_next = addNode(list_ptr->mod->next->int_data, current_version);
		      break;
		    }
		    case 'f': {
		      newnode_next = float_addNode(list_ptr->mod->next->float_data, current_version);
		      break;
		    }
		    case 'c': {
		      newnode_next = char_addNode(list_ptr->mod->next->char_data, current_version);
		      break;
		    }
		    case 'd': {
		      newnode_next = double_addNode(list_ptr->mod->next->double_data, current_version);
		      break;
		    }
		    default: {
		      ;
		    }
		    }
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

