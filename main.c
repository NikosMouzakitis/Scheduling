#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NTASKS	1000

/*
Scheduling of tasks based into their given periods, 
not taking in mind any conlicts assuming messages
got to be sent, figuring out the order also in case
they have the same time but different priorities higher 
priorities are scheduled before lower.
*/

struct tape {
	char name[10];	
	int  time;
	int prio;
};

struct jobs {
	char name[10];
	int period;	
	int prio;
};

struct tape myTape[100000];
int tape_len;
int tape_var;
int jcnt;	
int sarray[NTASKS];

void add_job( struct jobs *p, char *name, int period, int priority)
{
	strcpy(p->name, name);
	p->period = period;
	p->prio = priority;
	jcnt++;
}

void print_jobs(struct jobs *p)
{
	printf("JOBS: %d\n", jcnt);

	for(int i = 0; i < jcnt; i++)
		printf("NAME: %s\tPERIOD: %d\tPRIORITY:%d\n", p[i].name, p[i].period, p[i].prio);
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

	printf("TAPE print-out\n");
	printf("TIME\tNAME\tPRIORITY\n");
	printf("-----------------------\n");
	for(int i = 0; i < tape_len; i++) {
		printf("%4d\t%s\t%d\n", myTape[i].time, myTape[i].name, myTape[i].prio);
		printf("-----------------------\n");
	}
}

void priority_check(void) 
{
	int doubles = 0;	
	int val, hold;
	
	for(int i = 1; i < tape_len-1; i++) {
		
		if( (myTape[i].time == myTape[i+1].time)) {
			
			hold = i;	
			val = 2;	

			while(myTape[i].time == myTape[hold+val].time) 
				val++;
			i += val - 1;	

			/// basic sort algorithm.
			int ki, kj;
			int kk;
			char kname[10];	
			int l, h;
			l = hold;
			h = hold+val;
			int min;	
			

			for( kj = l; kj < h; kj++) {

				min = kj;
				
				for( int j = min + 1; j < h; j++) {
				
					if( myTape[j].prio > myTape[min].prio) {
					
						min = j;		
					}
				}

				strcpy(kname, myTape[kj].name);
				kk = myTape[kj].prio;
				strcpy(myTape[kj].name, myTape[min].name);
				myTape[kj].prio = myTape[min].prio;
				strcpy(myTape[min].name, kname);
				myTape[min].prio = kk;
			}
		}
	}	
}

void scheduler( struct jobs *p)
{
	
	for(int i = 0; i < jcnt; i++) 
		sarray[i] = p[i].period;	
	
	int lcm = find_LCM(sarray);
	
	printf("Least Common Mult. : %d\n", lcm);
	
	//	creating the "tape" based task's periods.			
	for( int i = 1 ; i <= lcm; i++) {
		
		for( int j = 0; j < jcnt; j++) {
			
			if( i % sarray[j] == 0) {
				// check priorities here.	
			
				myTape[tape_var].prio = p[j].prio;		
				myTape[tape_var].time = i;	
				strcpy(myTape[tape_var].name, p[j].name);
				tape_var++;	
				tape_len++;
			}
		}
	}
	printf("TAPE LEN:  %d\n", tape_len);
	printf("Configuring tape according to priorities\n");	
	priority_check();
	print_tape(myTape);
}

int main(int argc, char *argv[])
{
	struct jobs mat[NTASKS];

	// adding some jobs to schedule.
	add_job (&mat[jcnt], "taskA", 5, 1);	
	add_job (&mat[jcnt], "taskB", 12, 1);	
	add_job (&mat[jcnt], "taskC", 20, 2);	
	add_job (&mat[jcnt], "taskD", 10, 5);	
	
	print_jobs(mat);
	scheduler(mat);

	return(0);
}
