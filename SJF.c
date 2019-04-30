#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.h"
#include <stdlib.h>
#include <sched.h>
int running;
int N;

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

void priority_up(pid_t pid){
	set_priority(pid, SCHED_FIFO, INIT_PRIORITY);
}
void priority_down(pid_t pid){
	if(running == 0){
		return;
	}
	set_priority(pid, SCHED_FIFO, LOW_PRIORITY);
}
void nextproc(pid_t pid){
	set_priority(pid, SCHED_FIFO, HIGH_PRIORITY);
	running = 1;
}
void priority_ch(pid_t pid){
	if(running == 0){
		nextproc(pid);
	}
	if(running){
		priority_up(pid);
	}
}


/*=========================================================*/
int main(){
	scanf("%d",&N);
	fprintf(stderr, "scanned\n");
	process* proc;
	proc = take_tasks(N);
	fprintf(stderr, "task taken\n");
	qsort(proc, N,sizeof(int), cmp_t_exec );
	qsort(proc, N,sizeof(int), cmp_t_ready );
	fprintf(stderr, "sorted\n");

	struct sigaction sig;
	sig.sa_flags = 0;
	sig.sa_handler = sig_child;
	sigfillset(&sig.sa_mask);
	sigaction(SIGCHLD, &sig, NULL);
	fprintf(stderr, "signal\n");

	int nextproc = 0;
	fprintf(stderr, "startinggggggggggg\n");
	for (int time = 0, i = N; i > 0; time++){
		priority_ch(proc[nextproc].pid);
		while(nextproc < N && time == proc[nextproc].t_ready){
			priority_down(proc[nextproc].pid);
			create_proc(&proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
			nextproc ++;
			priority_ch(proc[nextproc].pid);
			fprintf(stderr, "Nextproc : %d\n", nextproc);
		}
		run_unit_time();
	}
}
