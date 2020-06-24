#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x,i;
  bool y;

  stack* stack = initialize();
  printf("\nEnter 3 numbers to put into stack : \n");
  for(i=0; i<3; i++)
    {
      scanf(" %d", &x);
      if(!push(stack, x))
		printf("Error\n");
    }
  
  for(i = 0; i<3; i++)
    {
      print_stack(stack,i);
    }

  x = pop(stack);
  printf("\nPoped element from the stack : %d \n",x);
	
  print_stack(stack,3);
  
}
