#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x, y, z,i;
 
  stack* stack = initialize();

  printf("Enter 3 numbers to push to stack\n");
  for(i=0; i<3; i++)
    {
      printf("\nEnter numbers to push to stack : \n");
      scanf(" %d", &x);
      printf("\nEnter version of stack : \n");
      scanf(" %d",&y);
      if(!push(stack,x,y))
	printf("Error\n");
    }
  
  for(i = 0; i<3; i++)
    {
      print_stack(stack,i);
    }

  printf("\nEnter the version of stack to pop element : ");
  scanf(" %d",&y);
  if(!pop(stack,y))
	printf("Error\n");
  print_stack(stack,3);	
}
