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

void * register_person(void * arg)
{
	struct registrar_thread_params *reg = arg;
	FILE *f = reg->fp;
	char nm[30];
	char g;
	int age,pincode,tests,type;
	long long int aadhar,phone_no;
	reg->p = NULL;
	struct person *p;
	struct person *tmp;
	while(!feof(f))
	{
		fscanf(f, "%lld %d %c %d %d %d %lld ", &aadhar, &age, &g, &pincode,&tests,&type,&phone_no);
		fgets(nm, 30, f);
		p = create_node(aadhar,age,g,pincode,tests,nm,type,phone_no);
		if(reg->p == NULL)
		{
			reg->p = p;
			reg->last = p;
			tmp=p;
		}
		else
		{
			tmp=reg->last;
			reg->last->next = p;
			reg->last = p;
		}
	}
	reg->last=tmp;
	reg->last->next=NULL;
	printf("\nResult of Registered Candidates: \n");
	pthread_exit(0);
} 
