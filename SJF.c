#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int running;

int compare(const void 8A, const void *b){
	return ( *(int*)a - *(int*)b );
}
void child(){
	static int num_done = 0;
	wait(NULL);
	num_done++;
	running = 0;
	if(num_done == N){
		exit(0);
	}
}
void priority_up(){
	set_priority(proc[0].pid, SCHED_FIFO, INIT_PRIORITY);
}
void priority_down(){
	if(running == 0){
		return;
	}
	set_priority(proc[0].pid, SCHED_FIFO, LOW_PRIORITY);
}
void nextproc(){
	proc[0].t_exec = 10000000000;
	proc[0].t_ready = 10000000000;
	set_priority(proc[0].pid, SCHED_FIFO, HIGH_PRIORITY);
	running = 1;
}
void priority_set(){
	if(running == 0){
		nextproc();
	}
	if(running == 0){
		priority_up();
	}
}


/*=========================================================*/
int main(){
	int N;
	scanf("%d",&N);

	process* proc;
	proc = take_tasks(N);

	qsort(proc.t_exec, ordernum,sizeof(int), compare );
	qsort(proc.t_ready, ordernum,sizeof(int), compare );

	child();

	int nextproc = 0;

	for (int time = 0, int i = N; i > 0; t++){
		priority_set();
		while(nextproc < N && time == proc[nextproc].t_ready){
			priority_down();
			create_proc(proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
			nextproc ++;
			priority_set();
		}
		run_unit_time();
	}
}
