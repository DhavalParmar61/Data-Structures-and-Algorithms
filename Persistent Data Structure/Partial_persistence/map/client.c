#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  char str[str_size];
  int i;
  map* list = initialize();

  printf("Enter 5 data in the form : key,value\n");
  for(i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!insert(list, str, i))
		printf("Error\n");
    }
    
  for(i = 0; i<5; i++)
    {
      print(list,i);
      printf("\n");
    }
      
  printf("\nEnter index number to update : \n");
  scanf("%d", &i);
  printf("\nEnter new data int the form : key,value\n");
  scanf("%s", str);

  if(!update(list,str,i))
	printf("\nError");
	
  print(list,5);	
	
  printf("\nEnter key to find in the form : key, version \n");	
  scanf("%s", str);
  find(list, str);

  printf("\nEnter indx number to delete : \n");
  scanf("%d", &i);
 
  if(!delete_map(list,i))
	printf("\nError");
 
  print(list,6);
}
