#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x,i,j,n,m,k,version,strt_state,no_transition;
  bool y;
  float fw_prob,bw_prob,ss_prob;

  list* list = initialize();
  printf("Please enter number of state in chain : ");
  scanf(" %d",&n);		
  for(i=0; i<n; i++)
    {
    	printf("\nPlease enter %d state data : ",i+1);	
      	scanf(" %d",&x);
		printf("\nPlease enter forward state transition probability : ");
		scanf(" %f",&fw_prob);
		printf("\nPlease enter previous state transition probability : ");
		scanf(" %f",&bw_prob);  
		printf("\nPlease enter same state transition probability : ");
		scanf(" %f",&ss_prob);        
      	if(!insert(list,x,i,fw_prob,bw_prob,ss_prob))
		{	
			printf("\nPlease enter data again.");
			i--;
		} 
    }
    
 for(i = 0; i<n; i++)
    {
      print_list(list,i);
    }
    
  printf("Please enter version of chain want to simulate : ");
  scanf(" %d",&version);
  printf("Please enter starting state data : ");
  scanf(" %d",&strt_state);
  printf("Please enter number of transition want to analyse : ");
  scanf(" %d",&no_transition);

  simulate(list,version,strt_state,no_transition);
    
  printf("\nEnter number of state want to update : ");
  scanf(" %d",&m);
  for(i=0; i<m; i++)
    {
      	printf("Please enter state index want to update : ");
      	scanf(" %d",&j);
      	printf("Please enter new data : ");	
      	scanf(" %d",&x);
		printf("Please enter forward state transition probability : ");
		scanf(" %f",&fw_prob);
		printf("Please enter previous state transition probability : ");
		scanf(" %f",&bw_prob);  
		printf("Please enter same state transition probability : ");
		scanf(" %f",&ss_prob); 
      if(!update(list,x,j,fw_prob,bw_prob,ss_prob))
	  {	
			printf("\nPlease enter data again.");
			i--;
	  } 
    }
    
 for(i = 0; i<n+m; i++)
    {
      print_list(list,i);
    }
  
  printf("Please enter version of chain want to simulate : ");
  scanf(" %d",&version);
  printf("Please enter starting state data : ");
  scanf(" %d",&strt_state);
  printf("Please enter number of transition want to analyse : ");
  scanf(" %d",&no_transition);
  
  simulate(list,version,strt_state,no_transition);
  
  printf("\nEnter number of state want to delete : ");
  scanf("%d",&k);
  for(i=0; i<k; i++)
    {
    	printf("Please enter state index want to delete : ");
      	scanf(" %d",&j);
      	if(!delete_node(list,j))
			printf("Error\n");
    }
 
  for(i = 0; i<n+m+k; i++)
    {
      print_list(list,i);
    }
    
  printf("Please enter version of chain want to simulate : ");
  scanf(" %d",&version);
  printf("Please enter starting state data : ");
  scanf(" %d",&strt_state);
  printf("Please enter number of transition want to analyse : ");
  scanf(" %d",&no_transition);
  
  simulate(list,version,strt_state,no_transition);
  
}
