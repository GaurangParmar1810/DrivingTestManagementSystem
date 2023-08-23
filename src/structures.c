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

struct person* create_node(long long int aadhar, int age, char g, int pin,int tests, char nm[],int type,long long phone_no)
{
	struct person *p = (struct person*)malloc(sizeof(struct person));
	p->age = age;
	p->gender = g;
	strcpy(p->name,nm);
	p->pincode = pin;
	p->no_of_tests=tests;
	p->aadharNo = aadhar;
	p->vehicle_type=type;
	p->phone_number=phone_no;
	p->isPassed = -1;
	p->time_elapsed = -1;
	p->driving_score = -1;
	p->next = NULL;
	return p;
}

