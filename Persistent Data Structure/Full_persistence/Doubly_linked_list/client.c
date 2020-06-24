#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x, y, z,i;
  char str[str_size];

  list* list = initialize();
  printf("\nEnter 3 numbers to add into list : \n");
  for(i=0; i<3; i++)
    {
      scanf("%d", &x);
      if(!insert(list,x,i, list->current_version))
		printf("Error\n");
    }
    
  printf("Enter index where yout want to update data : ");
  scanf("%d",&y);
  printf("Enter version in which you want to update data : ");
  scanf("%d",&z);
  printf("Enter new number want to add into list : ");
  scanf("%d", &x); 
  if(!update(list,x,y,z))
	printf("Error\n");  

  printf("Enter index want to delete : ");
  scanf("%d",&y);
  printf("Enter version in which you want to delete : ");
  scanf("%d",&z);
  if(!delete_list(list,y,z))
	printf("Error\n");	
	
  for(i = 0; i<5; i++)
    {
      print_list(list,i);
    }	
 
}
