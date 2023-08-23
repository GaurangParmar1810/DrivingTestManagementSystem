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

void DisplayTodayData()
{
	FILE *four_wheeler_vehicles = fopen("../dataFiles/four_wheeler_passed.txt","a");
	FILE *two_wheeler_vehicles = fopen("../dataFiles/two_wheeler_passed.txt","a");
	FILE *heavy_vehicles = fopen("../dataFiles/heavy_vehicles_passed.txt","a");
	
	fprintf(four_wheeler_vehicles,"\nFour wheeler passed: %d",lastData.total_4wheeler_passed);
	fclose(four_wheeler_vehicles);
	
	fprintf(two_wheeler_vehicles,"\nTwo wheeler passed: %d",lastData.total_2wheeler_passed);
	fclose(two_wheeler_vehicles);
	
	fprintf(heavy_vehicles,"\nHeavy vehicles passed: %d",lastData.total_heavy_vehicle_passed);
	fclose(heavy_vehicles);
	
	int i=1;
	FILE *fp = fopen("../resultFiles/reappear.txt","r");
	int reappearing_candidates=0;
	for(int c=getc(fp); c!=EOF ; c=getc(fp))
	{
		if(c=='\n')
		      reappearing_candidates++;
	}	    	
	fclose(fp);
	
	i=1;
	FILE *fp2 = fopen("../resultFiles/suspend.txt","r");
	int suspended_candidates=0;
	for(int c=getc(fp2); c!=EOF ; c=getc(fp2))
	{
		if(c=='\n')
		      suspended_candidates++;
	}	    	
	fclose(fp2);
	
	printf("\n\n-----------------------Today's Data-----------------------\n");
	
	//printing Records
	printf("\nTotal Tests done : %d ", lastData.totalTests);
	printf("\nTotal Test Passed :  %d\n\n", lastData.totalPassed);
	printf("------------------------------------------------------------\n");
	printf("\nTotal 2-wheeler Tests passed today : %d", lastData.total_2wheeler_passed);
	printf("\nTotal 4-wheeler Tests passed today : %d", lastData.total_4wheeler_passed);
	printf("\nTotal heavy vehicle passed today : %d\n\n", lastData.total_heavy_vehicle_passed);
	printf("------------------------------------------------------------\n");
	printf("\nTotal candidates who can reappear in test: %d",reappearing_candidates);
	printf("\nTotal Candidates who have to registration again for test: %d\n",suspended_candidates);
	printf("\n---------------------------DONE---------------------------\n\n");
}

