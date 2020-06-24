#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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


node* int_addNode(int data)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = data;
  newnode->float_data = def;
  newnode->char_data = def;
  newnode->double_data = def;
 
  newnode->identifier = "int";
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


node* float_addNode(float data)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = data;
  newnode->char_data = def;
  newnode->double_data = def;
 
  newnode->identifier = "float";
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


node* char_addNode(char data)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = def;
  newnode->char_data = data;
  newnode->double_data = def;

  newnode->identifier = "char";
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


node* double_addNode(double data)
{
  node* newnode = (node*) malloc(sizeof(node));
  
  newnode->int_data = def;
  newnode->float_data = def;
  newnode->char_data = def;
  newnode->double_data = data;
  
  newnode->identifier = "double";
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
  
  node* print_list = (node*) malloc(sizeof(node));

  printf("List of version %d\n", version);
	
  if(!print_list)	
    {
      printf("Memory allocation error");
      return;
    }

  for(print_list = list->head[version]; print_list != NULL; )
    {
       if((print_list->mod->version <= version) && (print_list->mod->version != unused))
	{
	  switch(print_list->mod->identifier[0])
	    {
	    case 'i': {
	      printf("%d ", print_list->mod->int_data);
	      print_list = print_list->mod->next;
	      break;
	    }
	    case 'f' : {
	      printf("%f ", print_list->mod->float_data);
	      print_list = print_list->mod->next;
	      break;
	    }
	    case 'c': {
	      printf("%c ", print_list->mod->char_data);
	      print_list = print_list->mod->next;
	      break;
	    }
	    case 'd':{
	      printf("%lf ", print_list->mod->double_data);
	      print_list = print_list->mod->next;
	      break;
	    }
	    default :{
	       print_list = print_list->mod->next;
	    }
	    }
	}
	  else
	    {
	      switch(print_list->identifier[0])
		{
		case 'i': {
		  printf("%d ", print_list->int_data);
		  print_list = print_list->next;
		  break;
		}
		case 'f' : {
		  printf("%f ", print_list->float_data);
		  print_list = print_list->next;
		  break;
		}
		case 'c': {
		  printf("%c ", print_list->char_data);
		  print_list = print_list->next;
		  break;
		}
		case 'd':{
		  printf("%lf ", print_list->double_data);
		  print_list = print_list->next;
		  break;
		}
		default :{
		  print_list = print_list->next;
		}
		}
	    }
    }
}


node* update_left(list* list, node* list_list, node* newnode, int current_version)
{

  if(list_list == NULL) return NULL;

  if(list_list->mod->version == unused)
    {
      switch(list_list->identifier[0])
	{
	case 'i': {
	  list_list->mod->int_data = list_list->int_data;
	  list_list->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  list_list->mod->float_data = list_list->float_data;
	  list_list->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  list_list->mod->char_data = list_list->char_data;
	  list_list->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  list_list->mod->double_data = list_list->double_data;
	  list_list->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      list_list->mod->version = current_version;
      list_list->mod->next = newnode;
      list_list->mod->prev = list_list->prev;

      list->head[current_version] = list->head[current_version-1];
      return list_list;
    }
  else
    {
      node* newnode_parent;
      switch(list_list->mod->identifier[0])
	{
	case 'i': {
	  newnode_parent = int_addNode(list_list->mod->int_data);
	  break;
	}
	case 'f': {
	  newnode_parent = float_addNode(list_list->mod->float_data);
	  break;
	}
	case 'c': {
	  newnode_parent = char_addNode(list_list->mod->char_data);
	  break;
	}
	case 'd': {
	  newnode_parent = double_addNode(list_list->mod->double_data);
	  break;
	}
	default: {
	  ;
	}
	}
       
      newnode_parent->next = newnode;

      if(list_list->mod->prev == NULL)
	{
	  list->head[current_version] = newnode_parent;
	  return newnode_parent;
	}
      
      newnode_parent->prev = update_left(list, list_list->mod->prev, newnode_parent, current_version);
    }

}



node* update_right(list* list, node* list_list, node* newnode, int current_version)
{

  if(list_list == NULL) return NULL;
    
  if(list_list->mod->version == unused)
    {
      switch(list_list->identifier[0])
	{
	case 'i': {
	  list_list->mod->int_data = list_list->int_data;
	  list_list->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  list_list->mod->float_data = list_list->float_data;
	  list_list->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  list_list->mod->char_data = list_list->char_data;
	  list_list->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  list_list->mod->double_data = list_list->double_data;
	  list_list->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      list_list->mod->version = current_version;
      list_list->mod->prev = newnode;
      list_list->mod->next = list_list->next;

      return list_list;
    }
  else
    {
      node* newnode_parent;
      switch(list_list->mod->identifier[0])
	{
	case 'i': {
	  newnode_parent = int_addNode(list_list->mod->int_data);
	  break;
	}
	case 'f': {
	  newnode_parent = float_addNode(list_list->mod->float_data);
	  break;
	}
	case 'c': {
	  newnode_parent = char_addNode(list_list->mod->char_data);
	  break;
	}
	case 'd': {
	  newnode_parent = double_addNode(list_list->mod->double_data);
	  break;
	}
	default: {
	  ;
	}
	}

      newnode_parent->prev = newnode;
	
      newnode_parent->next = update_right(list, list_list->mod->next, newnode_parent, current_version);
    }

}



 bool insert(list* list, char str[], int index)
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
      newnode = int_addNode(int_data);
      break;
    }
    case 'f': {
      float float_data;
      sscanf(str, "%*[^','],%f", &float_data);
      newnode = float_addNode(float_data);
      break;
    }
    case 'c': {
      char char_data;
      sscanf(str, "%*[^','],%c", &char_data);
      newnode = char_addNode(char_data);
      break;
    }
    case 'd': {
      double double_data;
      sscanf(str, "%*[^','],%lf", &double_data);
      newnode = double_addNode(double_data);
      break;
    }
    default: {
      printf("Invalid datatype\n");
    }
    }  
  
  node* list_list = (node*) malloc(sizeof(node));
  node* list_list_prev = (node*) malloc(sizeof(node));
  
  if(!list_list)	
    {
      printf("Memory allocation error");
      return false;
    }
  
  if(!list_list_prev)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(list_list = list->head[current_version], list_list_prev = list->head[current_version]; list_list != NULL; index_count++)
    {
      if(list_list != list->head[current_version])
	list_list_prev = list_list->prev;
      
      if(index_count == index) break;
      
      if((list_list->mod->version <= current_version) && list_list->mod->version != unused)
	list_list = list_list->mod->next;
      else
	list_list = list_list->next;
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
  
  if(list_list_prev == list->head[current_version] && index == 1)
    list_list = list_list_prev;
  else if((list_list == NULL) && (list_list_prev->mod->version == unused))
    list_list = list_list_prev->next;
  else if((list_list == NULL) && (list_list_prev->mod->version != unused))
    list_list = list_list_prev->mod->next;
  else
    list_list = list_list_prev;  

  if(list_list->mod->version == unused)
    {      
      current_version++;

      switch(list_list->identifier[0])
	{
	case 'i': {
	  list_list->mod->int_data = list_list->int_data;
	  list_list->mod->identifier = "int";
	  break;
	}
	case 'f': {
	  list_list->mod->float_data = list_list->float_data;
	  list_list->mod->identifier = "float";
	  break;
	}
	case 'c': {
	  list_list->mod->char_data = list_list->char_data;
	  list_list->mod->identifier = "char";
	  break;
	}
	case 'd': {
	  list_list->mod->double_data = list_list->double_data;
	  list_list->mod->identifier = "double";
	  break;
	}
	default: {
	  ;
	}
	}

      list_list->mod->version = current_version;

      if(index != 0)
	{
	  list_list->mod->next = newnode;
	  list_list->mod->prev = list_list->prev;

	  newnode->next = update_right(list, list_list->next, newnode, current_version);
	  newnode->prev = update_left(list, list_list, newnode, current_version);
	}
      else
	{
	  newnode->next = list_list;
  	  list_list->mod->next = list_list->next;
	  list_list->mod->prev = newnode;

	  list->head[current_version] = newnode;
      	}
    }
  else
    {
      current_version++;
   
      if(index !=0)
	{
	  newnode->next = update_right(list, list_list->mod->next, newnode, current_version);
	  newnode->prev = update_left(list, list_list, newnode, current_version);
	}
      else
	{
	  node* trailNode;
	  switch(list_list->mod->identifier[0])
	    {
	    case 'i': {
	      trailNode = int_addNode(list_list->mod->int_data);
	      break;
	    }
	    case 'f': {
	      trailNode = float_addNode(list_list->mod->float_data);
	      break;
	    }
	    case 'c': {
	      trailNode = char_addNode(list_list->mod->char_data);
	      break;
	    }
	    case 'd': {
	      trailNode = double_addNode(list_list->mod->double_data);
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  trailNode->next = list_list->mod->next;
	  trailNode->prev = newnode;
	  
	  newnode->next = trailNode;
  	  
	  list->head[current_version] = newnode;
	}
    }
  
  list->current_version = current_version;
  return true;
}



bool update(list* list, char str[], int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
  
  int index_count = 0;
  int current_version = list->current_version;

  node* list_list = (node*) malloc(sizeof(node));
  
  if(!list_list)	
    {
      printf("Memory allocation error");
      return false;
    }
 
  for(list_list = list->head[current_version]; list_list != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_list->mod->version <= current_version) && list_list->mod->version != unused)
	list_list = list_list->mod->next;
      else
	list_list = list_list->next;
    }

  if(index != index_count) 
    {
      printf("Index not found in the list. ");
      insert(list, str, index);
    }
  else
    {
      char type[string_size];
      
      if(list_list->mod->version == unused)
	{  
	  current_version++;

	  switch(str[0])
	    {
	    case 'i': {
	      int int_data;
	      sscanf(str, "%*[^','],%d", &int_data);
	      list_list->mod->int_data = int_data;
	      list_list->mod->identifier = "int";
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      list_list->mod->float_data = float_data;
	      list_list->mod->identifier = "float";
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data);
	      list_list->mod->char_data = char_data;
	      list_list->mod->identifier = "char";
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      list_list->mod->double_data = double_data;
	      list_list->mod->identifier = "double";
	      break;
	    }
	    default: {
	      ;
	    }
	    }

	  list_list->mod->version = current_version;
	  list_list->mod->next = list_list->next;
	  list_list->mod->prev = list_list->prev;

	  list->head[current_version] = list->head[current_version-1];
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
	      newnode = int_addNode(int_data);
	      break;
	    }
	    case 'f': {
	      float float_data;
	      sscanf(str, "%*[^','],%f", &float_data);
	      newnode = float_addNode(float_data);
	      break;
	    }
	    case 'c': {
	      char char_data;
	      sscanf(str, "%*[^','],%c", &char_data); 
	      newnode = char_addNode(char_data);
	      break;
	    }
	    case 'd': {
	      double double_data;
	      sscanf(str, "%*[^','],%lf", &double_data);
	      newnode = double_addNode(double_data);
	      break;
	    }
	    default: {
	      printf("Invalid datatype\n");
	    }
	    }  
  
	  
	  if(index != 0)
	    {
	      newnode->next = update_right(list, list_list->mod->next, newnode, current_version);
	      newnode->prev = update_left(list, list_list->mod->prev, newnode, current_version);
	    }
	  else
	    {	  
	       newnode->next = update_right(list, list_list->mod->next, newnode, current_version);
	       list->head[current_version] = newnode;
	    }
	}

      list->current_version = current_version;
    }
  return true;
}




bool delete_list(list* list, int index)
{
  if(index<0)
    {
      printf("Index cannot be negative");
      return false;
    }
      
  int index_count = 0;
  int current_version = list->current_version;

  node* list_list = (node*) malloc(sizeof(node));
  
  if(!list_list)	
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
  
  for(list_list = list->head[current_version]; list_list != NULL; index_count++)
    {
      if(index_count == index) break;
      
      if((list_list->mod->version <= current_version) && list_list->mod->version != unused)
	list_list = list_list->mod->next;
      else
	list_list = list_list->next;
    }
  
  if(list_list == NULL) index_count--;

  if(index != index_count) 
    {
      printf("Index not found in the list\n");
      return false;
    }
  else
    {
      if(index == 0)
	{
	  if(list_list->mod->version == unused)
	    {
	      if(list_list->next->mod->version == unused)
		{  
		  current_version++;
	
		  switch(list_list->next->identifier[0])
		    {
		    case 'i': {
		      list_list->next->mod->int_data = list_list->next->int_data;
		      list_list->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->next->mod->float_data = list_list->next->float_data;
		      list_list->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->next->mod->char_data = list_list->next->char_data;
		      list_list->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->next->mod->double_data = list_list->next->double_data;
		      list_list->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  list_list->next->mod->version = current_version;
		  list_list->next->mod->next = list_list->next->next;
		  list_list->next->mod->prev = list_list->prev;

		  list->head[current_version] = list_list->next;
		}
	      else
		{
		  current_version++;

		  node* newnode;
		  switch(list_list->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = int_addNode(list_list->next->mod->int_data);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_list->next->mod->float_data);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_list->next->mod->char_data);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_list->next->mod->double_data);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  newnode->next = update_right(list, list_list->next->mod->next, newnode, current_version);
	  	  
		  list->head[current_version] = newnode;
		}
	    }
	  else
	    {
	      if(list_list->mod->next->mod->version == unused)
		{  
		  current_version++;

		  switch(list_list->mod->next->identifier[0])
		    {
		    case 'i': {
		      list_list->mod->next->mod->int_data = list_list->mod->next->int_data;
		      list_list->mod->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->mod->next->mod->float_data = list_list->mod->next->float_data;
		      list_list->mod->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->mod->next->mod->char_data = list_list->mod->next->char_data;
		      list_list->mod->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->mod->next->mod->double_data = list_list->mod->next->double_data;
		      list_list->mod->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  list_list->mod->next->mod->version = current_version;
		  list_list->mod->next->mod->next = list_list->mod->next->next;
		  list_list->mod->next->mod->prev = list_list->mod->prev;

		  list->head[current_version] = list_list->mod->next;
		}
	      else
		{
		  current_version++;

		  node* newnode;
		  switch(list_list->mod->next->mod->identifier[0])
		    {
		    case 'i': {
		      newnode = int_addNode(list_list->mod->next->mod->int_data);
		      break;
		    }
		    case 'f': {
		      newnode = float_addNode(list_list->mod->next->mod->float_data);
		      break;
		    }
		    case 'c': {
		      newnode = char_addNode(list_list->mod->next->mod->char_data);
		      break;
		    }
		    case 'd': {
		      newnode = double_addNode(list_list->mod->next->mod->double_data);
		      break;
		    }
		    default: {
		      ;
		    }
		    }

		  newnode->next = update_right(list, list_list->mod->next->mod->next, newnode, current_version);
	  	  
		  list->head[current_version] = newnode;
		}
	    }
	  
	  list->current_version = current_version;
	  return true;
	}

      if((list_list->next == NULL) && (list_list->mod->version == unused))
	{
	  if(list_list->prev->mod->version == unused)
	    {  
	      current_version++;

	      switch(list_list->prev->identifier[0])
		    {
		    case 'i': {
		      list_list->prev->mod->int_data = list_list->prev->int_data;
		      list_list->prev->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->prev->mod->float_data = list_list->prev->float_data;
		      list_list->prev->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->prev->mod->char_data = list_list->prev->char_data;
		      list_list->prev->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->prev->mod->double_data = list_list->prev->double_data;
		      list_list->prev->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }
 
	      list_list->prev->mod->version = current_version;
	      list_list->prev->mod->next = list_list->next;
	      list_list->prev->mod->prev = list_list->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode;
	      switch(list_list->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(list_list->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(list_list->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      newnode->prev = update_left(list, list_list->prev->mod->prev, newnode, current_version);
	    }
 
	  list->current_version = current_version;
	  return true;
	}
      
      if((list_list->mod->next == NULL) && (list_list->mod->version != unused))
	{
	  if(list_list->mod->prev->mod->version == unused)
	    {  
	      current_version++;

	      switch(list_list->mod->prev->identifier[0])
		    {
		    case 'i': {
		      list_list->mod->prev->mod->int_data = list_list->mod->prev->int_data;
		      list_list->mod->prev->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->mod->prev->mod->float_data = list_list->mod->prev->float_data;
		      list_list->mod->prev->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->mod->prev->mod->char_data = list_list->mod->prev->char_data;
		      list_list->mod->prev->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->mod->prev->mod->double_data = list_list->mod->prev->double_data;
		      list_list->mod->prev->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	      
	      list_list->mod->prev->mod->version = current_version;
	      list_list->mod->prev->mod->next = list_list->mod->next;
	      list_list->mod->prev->mod->prev = list_list->mod->prev->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else
	    {
	      current_version++;

	      node* newnode;
	      switch(list_list->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(list_list->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(list_list->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      	      
	      newnode->prev = update_left(list, list_list->mod->prev->mod->prev, newnode, current_version);
	    }

	  list->current_version = current_version;
	  return true;
	}
      

      if(list_list->mod->version == unused)
	{
	  if((list_list->prev->mod->version == unused) && (list_list->next->mod->version == unused))
	    {  
	      current_version++;

	      switch(list_list->prev->identifier[0])
		    {
		    case 'i': {
		      list_list->prev->mod->int_data = list_list->prev->int_data;
		      list_list->prev->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->prev->mod->float_data = list_list->prev->float_data;
		      list_list->prev->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->prev->mod->char_data = list_list->prev->char_data;
		      list_list->prev->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->prev->mod->double_data = list_list->prev->double_data;
		      list_list->prev->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

	      list_list->prev->mod->version = current_version;
	      list_list->prev->mod->next = list_list->next;
	      list_list->prev->mod->prev = list_list->prev->prev;

	      switch(list_list->next->identifier[0])
		    {
		    case 'i': {
		      list_list->next->mod->int_data = list_list->next->int_data;
		      list_list->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->next->mod->float_data = list_list->next->float_data;
		      list_list->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->next->mod->char_data = list_list->next->char_data;
		      list_list->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->next->mod->double_data = list_list->next->double_data;
		      list_list->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

	      list_list->next->mod->version = current_version;
	      list_list->next->mod->next = list_list->next->next;
	      list_list->next->mod->prev = list_list->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_list->prev->mod->version == unused) && (list_list->next->mod->version != unused))
	    {
	      current_version++;
	      
	      switch(list_list->prev->identifier[0])
		{
		case 'i': {
		  list_list->prev->mod->int_data = list_list->prev->int_data;
		  list_list->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_list->prev->mod->float_data = list_list->prev->float_data;
		  list_list->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_list->prev->mod->char_data = list_list->prev->char_data;
		  list_list->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_list->prev->mod->double_data = list_list->prev->double_data;
		  list_list->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      node* newnode;
	      switch(list_list->next->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(list_list->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(list_list->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      list_list->prev->mod->version = current_version;

	      list_list->prev->mod->next = newnode;
	      list_list->prev->mod->prev = list_list->prev->prev;

	      newnode->prev = list_list->prev;		
	      newnode->next = update_right(list, list_list->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_list->prev->mod->version != unused) && (list_list->next->mod->version == unused))
	    {
	      current_version++;

	      node* newnode;
	      switch(list_list->prev->mod->identifier[0])
		{
		case 'i': {
		 newnode = int_addNode(list_list->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->prev->mod->float_data);
		  break;
		}
		case 'c': {
		   newnode = char_addNode(list_list->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      switch(list_list->next->identifier[0])
		    {
		    case 'i': {
		      list_list->next->mod->int_data = list_list->next->int_data;
		      list_list->next->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->next->mod->float_data = list_list->next->float_data;
		      list_list->next->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->next->mod->char_data = list_list->next->char_data;
		      list_list->next->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->next->mod->double_data = list_list->next->double_data;
		      list_list->next->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }

	      list_list->next->mod->version = current_version;

	      list_list->next->mod->next = list_list->next->next;
	      list_list->next->mod->prev = newnode;

	      newnode->next = list_list->next;
	      newnode->prev = update_left(list, list_list->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;
        
	      node* newnode_prev;
	      switch(list_list->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode_prev = int_addNode(list_list->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_prev = float_addNode(list_list->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_prev = char_addNode(list_list->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_prev = double_addNode(list_list->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      node* newnode_next;
	      switch(list_list->next->mod->identifier[0])
		{
		case 'i': {
		  newnode_next = int_addNode(list_list->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_next = float_addNode(list_list->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_next = char_addNode(list_list->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_next = double_addNode(list_list->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_list->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_right(list, list_list->next->mod->next, newnode_next, current_version);
 	    }
	}
      else
	{
	  if((list_list->mod->prev->mod->version == unused) && (list_list->mod->next->mod->version == unused))
	    {  
	      current_version++;
	     
	      switch(list_list->mod->prev->identifier[0])
		{
		case 'i': {
		  list_list->mod->prev->mod->int_data = list_list->mod->prev->int_data;
		  list_list->mod->prev->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_list->mod->prev->mod->float_data = list_list->mod->prev->float_data;
		  list_list->mod->prev->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_list->mod->prev->mod->char_data = list_list->mod->prev->char_data;
		  list_list->mod->prev->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_list->mod->prev->mod->double_data = list_list->mod->prev->double_data;
		  list_list->mod->prev->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_list->mod->prev->mod->version = current_version;
	      list_list->mod->prev->mod->next = list_list->mod->next;
	      list_list->mod->prev->mod->prev = list_list->mod->prev->prev;

	      switch(list_list->mod->next->identifier[0])
		{
		case 'i': {
		  list_list->mod->next->mod->int_data = list_list->mod->next->int_data;
		  list_list->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_list->mod->next->mod->float_data = list_list->mod->next->float_data;
		  list_list->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_list->mod->next->mod->char_data = list_list->mod->next->char_data;
		  list_list->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_list->mod->next->mod->double_data = list_list->mod->next->double_data;
		  list_list->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}

	      list_list->mod->next->mod->version = current_version;

	      list_list->mod->next->mod->next = list_list->mod->next->next;
	      list_list->mod->next->mod->prev = list_list->mod->prev;

	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_list->mod->prev->mod->version == unused) && (list_list->mod->next->mod->version != unused))
	    {
	      current_version++;
	      
	       switch(list_list->mod->prev->identifier[0])
		    {
		    case 'i': {
		      list_list->mod->prev->mod->int_data = list_list->mod->prev->int_data;
		      list_list->mod->prev->mod->identifier = "int";
		      break;
		    }
		    case 'f': {
		      list_list->mod->prev->mod->float_data = list_list->mod->prev->float_data;
		      list_list->mod->prev->mod->identifier = "float";
		      break;
		    }
		    case 'c': {
		      list_list->mod->prev->mod->char_data = list_list->mod->prev->char_data;
		      list_list->mod->prev->mod->identifier = "char";
		      break;
		    }
		    case 'd': {
		      list_list->mod->prev->mod->double_data = list_list->mod->prev->double_data;
		      list_list->mod->prev->mod->identifier = "double";
		      break;
		    }
		    default: {
		      ;
		    }
		    }
	 
	       node* newnode ;
	      switch(list_list->mod->next->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(list_list->mod->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->mod->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(list_list->mod->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->mod->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	      	      
	      list_list->mod->prev->mod->version = current_version;

	      list_list->mod->prev->mod->next = newnode;
	      list_list->mod->prev->mod->prev = list_list->mod->prev->prev;
	      
	      newnode->prev = list_list->mod->prev;
	      newnode->next = update_right(list, list_list->mod->next->mod->next, newnode, current_version);
	  	  
	      list->head[current_version] = list->head[current_version-1];
	    }
	  else if((list_list->mod->prev->mod->version != unused) && (list_list->mod->next->mod->version == unused))
	    {
	      current_version++;

	      switch(list_list->mod->next->identifier[0])
		{
		case 'i': {
		  list_list->mod->next->mod->int_data = list_list->mod->next->int_data;
		  list_list->mod->next->mod->identifier = "int";
		  break;
		}
		case 'f': {
		  list_list->mod->next->mod->float_data = list_list->mod->next->float_data;
		  list_list->mod->next->mod->identifier = "float";
		  break;
		}
		case 'c': {
		  list_list->mod->next->mod->char_data = list_list->mod->next->char_data;
		  list_list->mod->next->mod->identifier = "char";
		  break;
		}
		case 'd': {
		  list_list->mod->next->mod->double_data = list_list->mod->next->double_data;
		  list_list->mod->next->mod->identifier = "double";
		  break;
		}
		default: {
		  ;
		}
		}
	      
	      node* newnode;
	      switch(list_list->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode = int_addNode(list_list->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode = float_addNode(list_list->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode = char_addNode(list_list->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode = double_addNode(list_list->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}
	     
	      list_list->mod->next->mod->version = current_version;

	      list_list->mod->next->mod->next = list_list->mod->next->next;
	      list_list->mod->next->mod->prev = newnode;

	      newnode->next = list_list->mod->next;

	      newnode->prev = update_left(list, list_list->mod->prev->mod->prev, newnode, current_version);
	    }
	  else
	    {
	      current_version++;

	      node* newnode_prev;
	      switch(list_list->mod->prev->mod->identifier[0])
		{
		case 'i': {
		  newnode_prev = int_addNode(list_list->mod->prev->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_prev = float_addNode(list_list->mod->prev->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_prev = char_addNode(list_list->mod->prev->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_prev = double_addNode(list_list->mod->prev->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}

	      node* newnode_next;
	      switch(list_list->mod->next->mod->identifier[0])
		{
		case 'i': {
		  newnode_next = int_addNode(list_list->mod->next->mod->int_data);
		  break;
		}
		case 'f': {
		  newnode_next = float_addNode(list_list->mod->next->mod->float_data);
		  break;
		}
		case 'c': {
		  newnode_next = char_addNode(list_list->mod->next->mod->char_data);
		  break;
		}
		case 'd': {
		  newnode_next = double_addNode(list_list->mod->next->mod->double_data);
		  break;
		}
		default: {
		  ;
		}
		}	      

	      newnode_prev->next = newnode_next;
	      newnode_next->prev = newnode_prev;

	      newnode_prev->prev = update_left(list, list_list->mod->prev->mod->prev, newnode_prev, current_version);
	      newnode_next->next = update_right(list, list_list->mod->next->mod->next, newnode_next, current_version);
	    }

	}
      
      list->current_version = current_version;
    }
  return true;
}
