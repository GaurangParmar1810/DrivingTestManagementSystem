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

struct total_applications lastData={0,0,0,0,0,0};

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("\n ERR: please provide data.\n");
		exit(1);
	}
	run(argv[1]);
	return 0;
}
