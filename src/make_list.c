#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include <pthread.h>
#include<math.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>
#include"header.h"

#define two_wheeler 0
#define four_wheeler 1
#define heavy_vehicle 2

void * make_pass_list(void * arg)
{
	struct person *p = arg;
	FILE *fp = fopen("../dataFiles/passed_candidates.txt","w");
	if(fp == NULL)
	{
		printf("\nfailed..\n");
		pthread_exit(0);
	}

	while(p != NULL)
	{
		
		if(p->isPassed == 1)
		{
			if((p->time_elapsed)/10 ==0 )
				fprintf(fp,"%lld \t %d \t\t %d \t %d \t %lld \t %s",p->aadharNo,p->time_elapsed,p->age,p->driving_score,p->phone_number,p->name);
			else
				fprintf(fp,"%lld \t %d \t %d \t %d \t %lld \t %s",p->aadharNo,p->time_elapsed,p->age,p->driving_score,p->phone_number,p->name);
			lastData.totalPassed++;
		}
		p = p->next;
	}
	fclose(fp);
	pthread_exit(0);
}

void * make_fail_list(void * arg)
{
	struct person *p = arg;
	FILE *fp = fopen("../dataFiles/failed_candidates.txt","w");
	if(fp == NULL)
	{
		printf("\nfailed..\n");
		pthread_exit(0);
	}

	while(p != NULL)
	{
		if(p->isPassed == 0)
		{
			p->no_of_tests++; 
			fprintf(fp,"%lld \t %d \t %lld \t %s",p->aadharNo,p->age,p->phone_number,p->name);
		}
		p = p->next;	
	}
	fclose(fp);
	pthread_exit(0);
}

