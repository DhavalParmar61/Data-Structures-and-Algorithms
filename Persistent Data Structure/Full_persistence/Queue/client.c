#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x, y, z,i;
  queue* queue = initialize();

  for(i=0; i<3; i++)
    {
      printf("\nEnter numbers to put in queue : ");
      scanf(" %d", &x);
      printf("\nEnter the version of queue : ");
      scanf(" %d",&y);
      if(!insert(queue,x,y))
	  	printf("Error\n");
    }
    
  for(i = 0; i<3; i++)
    {
      print_queue(queue,i);
    }  
    
  printf("\nEnter version to delete element from front : ");
  scanf(" %d",&y);
  if(!delete_queue(queue,y))
	printf("Error\n");  
 
   print_queue(queue,3); 
}
