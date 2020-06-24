#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  char c;
  int x,i;
  bool y;

  dequeue* deque = initialize();
  
  for(i=0; i<3; i++)
    {
      printf("\nEnter number want to add to queue : ");	
      scanf(" %d", &x);
      printf("\nWant to enter at front(f) or rear(r) [f/r] :");
      scanf(" %c",&c);
      if((c == 'f') || (c == 'F'))
      	{
      		if(!insert_front(deque, x))
				printf("\nError");
      	}
      else if((c == 'r') || (c == 'R'))
      {
      		if(!insert_rear(deque, x))
				printf("\nError");
      }
      else
      	printf("Invalid input.");
    }
    
  for(i = 0; i<3; i++)
    {
      print_dequeue(deque,i);
    }  

  x = delete_front(deque);
  printf("\nDeleted element from front : %d",x);
  print_dequeue(deque,3);	
	
  x = delete_rear(deque);
  printf("\nDeleted element from rear : %d",x);
  print_dequeue(deque,4); 
  
}
