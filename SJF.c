#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.h"
#include <stdlib.h>
#include <sched.h>
int running = 0; int nextproc = 0; int N;

process* proc;

void sig_child(int signum){
	static int num_done = 0;
	wait(NULL);
	num_done++;
	running = 0;
	fprintf(stderr, "num_done : %d\n", num_done);
	if(num_done == N){
		exit(0);
	}
}

void priority_down(){
	if(running == 0){
		return;
	}
	set_priority(proc[nextproc].pid, SCHED_FIFO, LOW_PRIORITY);
}

void priority_ch(){
	if(running == 0){
		set_priority(proc[nextproc].pid, SCHED_FIFO, HIGH_PRIORITY);/*next*/
		running = 1;
	}
	if(running != 0){
		set_priority(proc[nextproc+1].pid, SCHED_FIFO, INIT_PRIORITY);/*prior_up*/
	}
}

/*=========================================================*/
int main(){
	scanf("%d",&N);

	proc = take_tasks(N);

	
	qsort(proc, N,sizeof(int), cmp_t_ready );
	qsort(proc, N,sizeof(int), cmp_t_exec );
	
	fprintf(stderr, "sorted\n");

	struct sigaction sig;
	sig.sa_flags = 0;
	sig.sa_handler = sig_child;
	sigfillset(&sig.sa_mask);
	sigaction(SIGCHLD, &sig, NULL);
	fprintf(stderr, "signal\n");

	fprintf(stderr, "startinggggggggggg\n");
	for (int time = 0, i = N; i > 0; time++){
		priority_ch();
		while(nextproc < N && time == proc[nextproc].t_ready){
			priority_down();
			create_proc(&proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
			nextproc ++;
			fprintf(stderr, "Nextproc_A : %d\n", nextproc);
			priority_ch();
			fprintf(stderr, "Nextproc_B : %d\n", nextproc);
		}
		run_unit_time();
	}
}
