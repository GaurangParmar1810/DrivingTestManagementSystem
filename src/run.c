#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>
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

#define WRITE 1
#define READ 0

void run(char * argv)
{
	
	//registration phase
	pthread_t registrar;
	struct registrar_thread_params reg;
	int err=-1,ret=-1;
	
	reg.fp = fopen(argv, "r");
	if(reg.fp == NULL)
	{
		fprintf(stderr, "%s path or file does not exist\n", argv);
		exit(1);
	}
	
	err = pthread_create (&registrar, NULL, register_person, (void *)&reg);
	if (err != 0)
	{
		printf("cant create thread: %s\n", strerror(err));	
		exit(1);
	}
	err = -1;
	sleep(1);
	
	err = pthread_join(registrar, (void **)&ret);
	if (err != 0)
	{
		printf("Joining ERROR : %s\n", strerror(err));	
		exit(1);
	}	
	 
	 
	//Testing Phase
	pthread_t Testingcabins[5];
	int cnt=0,i,*isPassed;	
	struct person *phead = reg.p;
	struct person *plast = reg.last;
	int ans[50],ac=0;
	while(phead != NULL)
	{
		cnt++;
		err = pthread_create (&Testingcabins[cnt%5], NULL, Testing, (void *)phead);
		if (err != 0)
		{
			printf("can't create thread: %s\n", strerror(err));	
			exit(1);
		}
		phead = phead->next;
		sleep(1);
	}
	lastData.totalTests = cnt;
	for(i=0;i<5;i++)
	{
		err = pthread_join(Testingcabins[i], (void **)&isPassed);
		if (err != 0)
		{
			printf("cant create thread: %s\n", strerror(err));	
			exit(1);
		}
	}
	
	//collect data and diffranciate them 
	pthread_t pass,fail;
	phead = reg.p;
	
	err = pthread_create (&pass, NULL, make_pass_list, (void *)phead);
	if (err != 0)
	{
		printf("cant create thread: %s\n", strerror(err));	
		exit(1);
	}

	err = pthread_create (&fail, NULL, make_fail_list, (void *)phead);
	if (err != 0)
	{
		printf("cant create thread: %s\n", strerror(err));	
		exit(1);
	}

	err = pthread_join(pass, (void **)&ret);
	if (err != 0)
	{
		printf("cant create thread: %s\n", strerror(err));	
		exit(1);
	}
	err = pthread_join(fail, (void **)&ret);
	if (err != 0)
	{
		printf("cant create thread: %s\n", strerror(err));	
		exit(1);
	}
	
	//treatment_phase
	
	FILE* fp=fopen("../resultFiles/suspend.txt","w");
	fclose(fp);
	
	FILE* fp1=fopen("../resultFiles/reappear.txt","w");
	fclose(fp1);
	
	//
	int pid,status;
	int file_descriptor[2];
	pipe(file_descriptor);
	phead = reg.p;
	pid = fork();
	if(pid == 0)
	{
		close(file_descriptor[READ]);
	 	FILE *fp_two_wheeler_passed = fopen("../dataFiles/two_wheeler_passed.txt","w");
	 	FILE *fp_four_wheeler_passed = fopen("../dataFiles/four_wheeler_passed.txt","w");
	 	FILE *fp_heavy_vehicles_passed = fopen("../dataFiles/heavy_vehicles_passed.txt","w");
		
		while(phead != NULL)
		{
			if(phead->isPassed==0)
			{
				char str[100]="";
				strcpy(str,stringconverter(phead));
				write(file_descriptor[WRITE],str,strlen(str)+1);
				kill(getpid(),SIGSTOP);
			}
			else
			{
				if(phead->vehicle_type==0 && phead->aadharNo!=-1)
					fprintf(fp_two_wheeler_passed,"Aadhar No: %lld\tNumber of tests: %d\tPassing status: %s\tPhone Number: %lld\tName: %s",phead->aadharNo,phead->no_of_tests,"Passed",phead->phone_number,phead->name);
				if(phead->vehicle_type==1 && phead->aadharNo!=-1)
					fprintf(fp_four_wheeler_passed,"Aadhar No: %lld\tNumber of tests: %d\tPassing status: %s\tPhone Number: %lld\tName: %s",phead->aadharNo,phead->no_of_tests,"Passed",phead->phone_number,phead->name);
				if(phead->vehicle_type==2 && phead->aadharNo!=-1)
					fprintf(fp_heavy_vehicles_passed,"Aadhar No: %lld\tNumber of tests: %d\tPassing status: %s\tPhone Number: %lld\tName: %s",phead->aadharNo,phead->no_of_tests,"Passed",phead->phone_number,phead->name);
			}
			phead = phead->next;	
		}	 	
		
		write(file_descriptor[WRITE],"-1",3);
		close(file_descriptor[WRITE]);
		fclose(fp_four_wheeler_passed);
		fclose(fp_two_wheeler_passed);
		exit(0);

	}
	else
	{
		close(file_descriptor[WRITE]);
		int bytesRead;
		char str[100];
		while(1)
		{
			bytesRead = read(file_descriptor[READ],str,100);
			if(strcmp(str,"-1")==0)
			{
			   break;
			}
			else
			{
				pthread_t fail_split;
				err = pthread_create (&fail_split, NULL, attempt_check, (void *)str);
				if (err != 0)
				{
					printf("CANNOT CREATE THREAD!: %s\n", strerror(err));	
					exit(1);
				}
				
				err = pthread_join(fail_split, (void **)&ret);
				if (err != 0)
				{
					printf("CANNOT CREAT THREAD: %s\n", strerror(err));	
					exit(1);
				}
				kill( pid, SIGCONT );   
			}
		}
		close(file_descriptor[READ]);
	}
	pid = wait(&status);

	//Display the end of the day Records.
	if(pid!=0)
	DisplayTodayData();
	
}
