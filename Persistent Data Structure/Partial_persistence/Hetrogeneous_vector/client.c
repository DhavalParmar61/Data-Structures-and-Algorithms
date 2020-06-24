#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  char str[string_size];
  bool y;
  int i;
  list* list = initialize();

  printf("Enter 5 data in the form : type, data\n");
   
  for(i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!insert(list, str, i))
		printf("Error\n");
      print_list(list,i);
      printf("\n");
    }
  
  printf("\nEnter index number to update : ");
  scanf("%d", &i);
  printf("\nEnter new data : ");
  scanf("%s", str);

  if(!update(list,str,i))
	printf("\nError");

  printf("\nEnter indx number to delete : ");
  scanf("%d", &i);
 
  if(!delete_list(list,i))
	printf("\nError");
 
 for(i = 0; i<7; i++)
    {
      print_list(list,i);
    }
  
}
