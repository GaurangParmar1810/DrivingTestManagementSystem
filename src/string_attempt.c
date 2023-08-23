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

char* stringconverter(struct person* person_detail)
{
   char *s=(char *)malloc(100*sizeof(char));
   sprintf(s,"%lld %d %d %lld %s",person_detail->aadharNo,person_detail->vehicle_type,person_detail->no_of_tests,person_detail->phone_number,person_detail->name);
   return s;   
}

void* attempt_check(void *s)
{
	char str[100]="";
	strcpy(str,(char *)s);
	long long aadharcard,phone_no;
	char tmp[30];
	char type[15];
	int trial,t;
	char name[30];
	sscanf(str,"%lld %d %d %lld %s",&aadharcard,&t,&trial,&phone_no,tmp);
	
	switch((char)str[13])
	{
		case '0':
		{
			strcpy(type,"two wheeler  ");
			break;
		}
		case '1':
		{
			strcpy(type,"four wheeler ");
			break;
		}
		case '2':
		{
			strcpy(type,"heavy vehicle");
			break;
		}
	}
	
	switch((char)str[15])
	{
		case '1':
		{
			strcpy(tmp,"1");
			trial=atoi(tmp);
			break;
		}
		case '2':
		{
			strcpy(tmp,"2");
			trial=atoi(tmp);
			break;
		}
		case '3':
		{
			strcpy(tmp,"3");
			trial=atoi(tmp);
			break;
		}
	}
	
	strcpy(name,&str[28]);
	if(trial==3)
	{
		FILE* fp=fopen("../resultFiles/suspend.txt","a+");
		if(fp==NULL)
		{
			printf("ERROR: CANNOT OPEN THE FILE1!!\n");
			pthread_exit(0);
		}
		fprintf(fp,"%lld \t %s \t %lld \t %s",aadharcard,type,phone_no,name);
		
		fclose(fp);
		
	}
	else
	{
		FILE* fp=fopen("../resultFiles/reappear.txt","a+");
		if(fp==NULL)
		{
			printf("ERROR: CANNOT OPEN THE FILE2!!\n");
			pthread_exit(0);
		}
		fprintf(fp,"%lld \t %s \t %d \t %lld \t %s",aadharcard,type,trial,phone_no,name);
		
		fclose(fp);
		
	}
	pthread_exit(0);
	
}
