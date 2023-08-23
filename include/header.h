#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<time.h>
#include<signal.h>

struct registrar_thread_params
{
	FILE *fp;
	struct person *p ;
	struct person *last;
	struct person *tmp;
};

struct total_applications
{
	int totalPassed;
	int totalTests;
	int remaining_tests;
	int total_2wheeler_passed;
	int total_4wheeler_passed;
	int total_heavy_vehicle_passed;
};

struct person
{
	char name[30];
	int pincode;
	char gender;
	int age;
	int no_of_tests;
	long long int aadharNo;
	int isPassed;
	int time_elapsed;
 	int driving_score;
 	int vehicle_type;
 	long long phone_number;
	struct person *next;
};


extern struct total_applications lastData;

struct person* create_node(long long int , int , char , int ,int , char* ,int,long long);
void * register_person(void * );
void * Testing(void * );
void * make_fail_list(void * );
void * make_pass_list(void * );
void DisplayTodayData();
char* stringconverter(struct person*);
void* attempt_check(void *);
void run(char *);

