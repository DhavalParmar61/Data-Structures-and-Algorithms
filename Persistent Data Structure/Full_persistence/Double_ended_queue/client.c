#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x, y, z,i;
  char c;
 
  deque* deque = initialize();
  
 for(i=0; i<3; i++)
    {
      printf("\nEnter number want to add to queue : ");	
      scanf(" %d", &x);
      printf("\nEnter version of queue you want to add into : ");
      scanf(" %d",&y);
      printf("\nWant to enter at front(f) or rear(r) [f/r] : ");
      scanf(" %c",&c);
      if((c == 'f') || (c == 'F'))
      	{
      		if(!insert_front(deque, x,y))
				printf("\nError");
      	}
      else if((c == 'r') || (c == 'R'))
      {
      		if(!insert_rear(deque, x,y))
				printf("\nError");
      }
      else
      	printf("Invalid input.");
    }
    
  for(i = 0; i<3; i++)
    {
      print_dequeue(deque,i);
    }  

  printf("\nEnter Version of queue to delete element form front : ");
  scanf(" %d",&y);
  if(!delete_front(deque,y))
  	printf("\nError");
  print_dequeue(deque,3);

  printf("\nEnter Version of queue to delete element form rear : ");
  scanf(" %d",&y);
  if(!delete_rear(deque,y))
  	printf("\nError");
  print_dequeue(deque,4);
    
}
