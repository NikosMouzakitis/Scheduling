#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NTASKS	5

/*
Scheduling of tasks based into their given periods, 
not taking in mind any conlicts assuming messages
got to be sent, figuring out the order.
*/

struct tape {
	char name[10];	
	int  time;
};

struct jobs {
	char name[10];
	int period;	
};

struct tape myTape[10000];
int tape_len;
int tape_var;
int jcnt;	
int sarray[NTASKS];

void add_job( struct jobs *p, char *name, int period)
{

	strcpy(p->name, name);
	p->period = period;
	jcnt++;
}

void print_jobs(struct jobs *p)
{
	printf("JOBS: %d\n", jcnt);

	for(int i = 0; i < jcnt; i++)
		printf("NAME: %s\tPERIOD: %d\n", p[i].name, p[i].period);

}

//greater common divisor
int gcd( int a, int b)
{
	if(b == 0)
		return a;
	return gcd(b, a%b);
}

// least common multiple
int find_LCM( int *p)
{
	int ret = p[0];

	for(int i = 1; i < jcnt; i++)
		ret = ( ( ( p[i] * ret) ) / (gcd(p[i], ret)));
	
	return ret;
}

void print_tape(struct tape *t)
{

	printf("Scheduler print-out\n");

	for(int i = 0; i < tape_len; i++) {
		printf("time: %d, name: %s\n", myTape[i].time, myTape[i].name);
	}
}

void scheduler( struct jobs *p)
{
	for(int i = 0; i < jcnt; i++) 
		sarray[i] = p[i].period;	
	
	int lcm = find_LCM(sarray);
	
	printf("Least Common Mult. : %d\n", lcm);
	
	//	creating the "tape" based on the period
	//	of each task.			

	for( int i = 1 ; i <= lcm; i++) {
		
		for( int j = 0; j < jcnt; j++) {
			
			if( i % sarray[j] == 0) {
				myTape[tape_var].time = i;	
				strcpy(myTape[tape_var++].name, p[j].name);
				tape_len++;
			}
		}
	}

	printf("TAPE LEN:  %d\n", tape_len);
	print_tape(myTape);
}

int main(int argc, char *argv[])
{
	struct jobs mat[NTASKS];
	// adding some jobs to schedule.
	add_job (&mat[jcnt], "taskA", 10);	
	add_job (&mat[jcnt], "taskB", 8);	
	add_job (&mat[jcnt], "taskC", 5);	
	add_job (&mat[jcnt], "taskD", 2);	

	print_jobs(mat);
	scheduler(mat);

	return(0);
}
