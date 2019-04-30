#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define GET_TIME 314
#define PRINTK 315
#define CHILD_CPU 1
#define PARENT_CPU 0
#include "functions.h"
#define ever ;;

static int last,numberOfTime, run, countFinishing;
int numberOfProcess;
int running = 0;

void sig_child(int signum)
{
    static int finished = 0;
    wait(NULL);
    finished++;
    running = 0;
    if (finished == numberOfProcess) exit(0);
}

int proc_wakeup(int pid)
{
	struct sched_param param;
	param.sched_priority = 0;
	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	if (ret < 0) {
		//perror("sched_setscheduler");
		return -1;
	}
	return ret;
}

int proc_block(int pid)
{
	struct sched_param param;
	param.sched_priority = 0;
	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	if (ret < 0) 
		return -1;
	return ret;
}


int nextP(struct process *proc, int numberOfProcess)
{
	int ret = -1;
    if(running == 1) {
        return ret;
    }
    
	for (int i = 0; i < numberOfProcess; i++) {
		if (proc[i].pid == -1 || proc[i].t_exec == 0)
			continue;
		if (ret == -1 || proc[i].t_exec < proc[ret].t_exec)
			ret = i;
	}
	return ret;
}


int main(int argc, char* argv[])
{

	struct process *proc;

	scanf("%d", &numberOfProcess);
    
    proc = take_tasks(numberOfProcess);

	for (int i = 0; i < numberOfProcess; i++)
		proc[i].pid = -1;

  struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sig_child;
    sigfillset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);

	assign_cpu(getpid(), PARENT_CPU);
	proc_wakeup(getpid());
	numberOfTime = 0;
	run = -1;
	countFinishing = 0;

	for(ever) {
		if (run != -1 && proc[run].t_exec == 0) {
			waitpid(proc[run].pid, NULL, 0);
			//printf("%s %d\n", proc[run].name, proc[run].pid);
			run = -1;
			countFinishing++;
      fprintf(stderr, "cf: %d, n: %d", countFinishing, numberOfProcess);
			if (countFinishing == numberOfProcess)
				break;
		}
		for (int i = 0; i < numberOfProcess; i++) {
			if (proc[i].t_ready == numberOfTime) {
                create_proc(&proc[i].pid, proc[i].name, i, proc[i].t_exec);
				proc_block(proc[i].pid);
			}

		}
    
		int next = nextP(proc, numberOfProcess);
		if (next != -1) {
			if (run != next) {
				proc_wakeup(proc[next].pid);
				proc_block(proc[run].pid);
				run = next;
                running = 1;
				last = numberOfTime;
			}
		}
    
		run_unit_time();
		numberOfTime++;
	}
	return 0;
}
