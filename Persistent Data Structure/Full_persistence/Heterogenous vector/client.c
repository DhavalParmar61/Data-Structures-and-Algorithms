#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x,y,i;
  char str[str_size];
  char split_str[str_size];

  list* list = initialize();
  printf("Enter 5 data in the form of : type, data \n");
  
  for(i=0; i<5; i++)
    {
      scanf("%s", str);
      if(!insert(list, str, i, list->current_version))
    	printf("Error\n");
    }
    
  printf("\n");
  for(i = 0; i<5; i++)
    {
      print_list(list,i);
    }
 
  printf("\nEnter data to insert in the form : type,data;index,version \n");
  scanf("%s",str);
  sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
  if(!insert(list, split_str, x, y))
	printf("Error\n");
  
  print_list(list,5);
  
  printf("\nEnter data to update in the form : type,data;index,version \n");
  scanf("%s",str);
  sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
  if(!update(list, split_str, x, y))
	printf("Error\n");
	
 print_list(list,6);
  
  printf("\nEnter data to delete in the form : index,version \n");
  scanf("%s",str);
  sscanf(str, "%d,%d", &x, &y);
  if(!delete_list(list,x,y))
	printf("Error\n");
  
  print_list(list,7);

}
