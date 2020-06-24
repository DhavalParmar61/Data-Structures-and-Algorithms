#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x,i;
  bool y;

  queue* queue = initialize();
  printf("\nEnter 3 numbers to put in queue : \n");
  for(i=0; i<3; i++)
    {
      scanf(" %d", &x);
      if(!insert(queue, x))
		printf("\nError");
    }

  for(i = 0; i<3; i++)
    {
      print_queue(queue,i);
    }
    
  x = delete_queue(queue);
  printf("\nDeleted element from front of queue : %d\n",x);  
 
  print_queue(queue,3);
  
}
