#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x,i;
  bool y;

  list* list = initialize();
  printf("Enter 3 numbers\n");
  for(i=0; i<3; i++)
    {
      scanf(" %d", &x);
      if(!insert(list,x,i))
		printf("\nError");
    }
    
  for(i = 0; i<3; i++)
    {
      print_list(list,i);
    }  
    
  printf("\nEnter index number to update : ");
  scanf(" %d", &i);
  printf("\nEnter new data : ");
  scanf(" %d",&x);
  
  if(!update(list,x,i))
	printf("\nError");
  print_list(list,3);	

  printf("\nEnter indx number to delete : ");
  scanf(" %d", &i);
 
  if(!delete_node(list,i))
	printf("\nError");
  print_list(list,4);	
 
  
}
