#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

void main()
{
	struct node *header1,*header2;
	char c;
	double time_taken;
	clock_t start,end; 
	printf("Please enter bin size greater than 24 byte: ");
	int bin_size;
	scanf("%d",&bin_size);
	initialize_bin(bin_size);
	while(1)
	{
		printf("\n\nPlease enter dividened polinomial in the form (degree,constant) separated by comma :");
		header1=input_poly();
		printf("\nPlease enter divisor polinomial in the form (degree,constant) separated by comma :");
		header2=input_poly();
		start=clock();	
		divide_poly(header1,header2);
		end=clock();
		time_taken=((double)(end-start))/CLOCKS_PER_SEC;
		printf("\nTime taken : %lf seconds",time_taken);
		printf("\nWant to continue[y/n] : ");
		scanf(" %c",&c);
		if(c=='n' || c=='N')
			break;	
	}
	print_bin_data();
}
