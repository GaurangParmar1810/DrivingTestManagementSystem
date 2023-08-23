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

void * Testing(void * arg)
{
	struct person *p_head = arg;
	
	srand(time(0));
	//two_wheeler phase
	int time_elapsed = 1 + (rand() % 10),drive_score;
	if(p_head->vehicle_type==0 && time_elapsed > 5)
	{
		printf("\n \t\t Passing Status: Fail \t Vehicle Type: Two Wheeler \t Name: %s",p_head->name);
		p_head->isPassed = 0;
		p_head->time_elapsed = time_elapsed;
	}
	else if(p_head->vehicle_type==0 )
	{
		p_head->time_elapsed = time_elapsed;
		
		if(time_elapsed < 2)
			drive_score = 50 + (rand() % 40);
		else if(time_elapsed > 2 && time_elapsed <= 3)
			drive_score = 50 + (rand() % 30);
		else
			drive_score = 50 + (rand() % 20);
		
		p_head->driving_score = drive_score;
		
		if(drive_score>=40)
		{
		        printf("\n \t\t Passing Status: Pass \t Vehicle Type: Two Wheeler \t Name: %s",p_head->name);
			p_head->isPassed=1;
			lastData.total_2wheeler_passed++;
		}	
		else
		{
			printf("\n \t\t Passing Status: Fail \t Vehicle Type: Two Wheeler \t Name: %s",p_head->name);
			p_head->isPassed=0;
			p_head->no_of_tests++;   
		}
	}
	
	//four_wheeler testing phase
	int time_elapsed_1 = 5 +(rand() % 10);
	if(p_head->vehicle_type==1 && time_elapsed_1 > 10)
	{
		printf("\n \t\t Passing Status: Fail \t Vehicle Type: Four Wheeler \t Name: %s",p_head->name);
		p_head->isPassed = 0;
		p_head->time_elapsed = time_elapsed_1;
	}
	else if( p_head->vehicle_type==1)
	{
		p_head->time_elapsed = time_elapsed_1;
		
		if(time_elapsed_1 <= 7)
			drive_score = 50 + (rand() % 40);
		else if(time_elapsed_1 > 7 && time_elapsed_1 <= 9)
			drive_score = 50 + (rand() % 30);
		else
			drive_score = 50 + (rand() % 20);
		
		p_head->driving_score = drive_score;
		
		if(drive_score>=40)
		{
		        printf("\n \t\t Passing Status: Pass \t Vehicle Type: Four Wheeler \t Name: %s",p_head->name);
			p_head->isPassed=1;
			lastData.total_4wheeler_passed++;
		}
		else
		{
			printf("\n \t\t Passing Status: Fail \t Vehicle Type: Four Wheeler \t Name: %s",p_head->name);
			p_head->isPassed=0;
			p_head->no_of_tests++;   
		}
	}
	
	
	//heavy_vehicle testing phase
	int time_elapsed_2 = 10 + (rand() % 10);
	if(p_head->vehicle_type==2 && time_elapsed_2 > 15)
	{
		printf("\n \t\t Passing Status: Fail \t Vehicle Type: Heavy Vehicle \t Name: %s",p_head->name);
		p_head->isPassed = 0;
		p_head->time_elapsed = time_elapsed_2;
	}
	else if(p_head->vehicle_type==2)
	{
		p_head->time_elapsed = time_elapsed_2;
		
		if(time_elapsed_2 < 11)
			drive_score = 50 + (rand() % 40);
		else if(time_elapsed_2 > 11 && time_elapsed_2 <= 13)
			drive_score = 50 + (rand() % 30);
		else 
			drive_score = 50 + (rand() % 20);
		
		p_head->driving_score = drive_score;
		
		if(drive_score>=40)
		{
			printf("\n \t\t Passing Status: Pass \t Vehicle Type: Heavy Vehicle \t Name: %s",p_head->name);
			p_head->isPassed=1;
			lastData.total_heavy_vehicle_passed++;
		}
		else
		{
		   printf("\n \t\t Passing Status: Fail \t Vehicle Type: Heavy Vehicle \t Name: %s",p_head->name);
		   p_head->isPassed=0;
		   p_head->no_of_tests++;   
		}
	}
	
		
	pthread_exit(0);
}

