#include <stdio.h>
#include <stdbool.h>
#include "header.h"

void main()
{
  int x, y, z,i;
  char str[str_size];
  char split_str[str_size];
  
  map* list = initialize();

  printf("Enter 3 data in the form : key, value\n");
  for(i=0; i<3; i++)
    {
      scanf("%s", str);
      if(!insert(list,str,i,list->current_version))
		printf("Error\n");
    }
 
 printf("\n");
  for(i = 0; i<3; i++)
    {
      print_map(list,i);
    }
 
  printf("\nEnter data to insert in the form :  key,value;index,version\n");
  scanf("%s",str);
  sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
  if(!insert(list,split_str,x,y))
	printf("Error\n");
	
  printf("\n");	
  print_map(list,3);	

  printf("\nEnter data to update in the form : key,value;index,version\n");
  scanf("%s",str);
  sscanf(str, "%[^';'];%d,%d", split_str, &x, &y);
  if(!update(list,split_str,x,y))
	printf("Error\n");
	
  printf("\n");	
  print_map(list,4);	

  printf("\nEnter data to find in the form : key, version\n");
  scanf("%s", str);
  sscanf(str, "%[^,],%d",split_str,&y);
  find(list,split_str,y);
  
  printf("\nEnter data to delete in the form : index,version\n");
  scanf("%s",str);
  sscanf(str, "%d,%d", &x, &y);
  if(!delete_map(list,x,y))
	printf("Error\n");

  printf("\n");	
  print_map(list,5);
  
}
