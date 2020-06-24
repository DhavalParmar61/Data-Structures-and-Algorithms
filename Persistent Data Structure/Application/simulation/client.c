#include <stdio.h>
#include <stdbool.h>
#include "header.h"

int main()
{
  int x,i,j,n,m,k,version,strt_state,no_transition;
  bool y;
  float fw_prob,bw_prob,ss_prob;

  list* list = init_list();

  printf("Please enter number of state in chain : ");
  scanf("%d",&n);
  printf("\nPlease enter forward state transition probability : ");
  scanf("%f",&fw_prob);
  printf("\nPlease enter previous state transition probability : ");
  scanf("%f",&bw_prob);  
  printf("\nPlease enter same state transition probability : ");
  scanf("%f",&ss_prob);		
  
  for(i=0; i<n; i++)
    {
      	if(!insert(list,i,i,fw_prob,bw_prob,ss_prob))
		{	
			printf("\nError");
		}
    }
  
  printf("Please enter starting state to simulate model : ");
  scanf("%d",&strt_state);
  printf("Please enter number of transition : ");
  scanf("%d",&no_transition);
  
  simulate(list,n-1,strt_state,no_transition);
  
}
