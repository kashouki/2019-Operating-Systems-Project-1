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

static int last,numberOfTime,run,countFinishing;

#define UNIT_T()				\
{						\
	volatile unsigned long i;		\
	for (i = 0; i < 1000000UL; i++);	\
}			

typedef struct process {
	pid_t pid;
	char name[32];
	int t_ready;
	int t_exec;
	int t_comp;
}process;

int proc_assign_cpu(int pid, int core)
{
	if (core > sizeof(cpu_set_t)) {
		fprintf(stderr, "Core index error.");
		return -1;
	}

	cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(core, &mask);

	if (sched_setaffinity(pid, sizeof(mask), &mask) < 0) {
		perror("sched_setaffinity");
		exit(1);
	}
	return 0;
}

int proc_exec(struct process proc)
{
	int pid = fork();

	if (pid < 0) {
		perror("fork");
		return -1;
	}

	if (pid == 0) {
		char to_dmesg[200];
		unsigned long start_sec, startTime, end_sec, endTime;

		struct timespec t_start, t_finish;

		clock_gettime(CLOCK_REALTIME, &t_start);

		//syscall(GET_TIME, &start_sec, &startTime);
		for (int i = 0; i < proc.t_exec; i++) {
			UNIT_T();
		}
		//syscall(GET_TIME, &end_sec, &endTime);
		clock_gettime(CLOCK_REALTIME, &t_finish);
		sprintf(to_dmesg, "[project1] %d %lu.%09lu %lu.%09lu\n", getpid(), t_start.tv_sec, t_start.tv_nsec, t_finish.tv_sec, t_finish.tv_nsec);
		printf("%s",to_dmesg);
		exit(0);
	}
	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
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

int cmp(const void *a, const void *b) {
	return ((struct process *)a)->t_ready - ((struct process *)b)->t_ready;
}

int nextP(struct process *proc, int numberOfProcess, int policy)
{
	int ret = -1;
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
	int policy,numberOfProcess;
	char sched_policy[256];
	struct process *proc;

	//scanf("%s", sched_policy);
	scanf("%d", &numberOfProcess);
	printf("%s\n", sched_policy);
	proc = (struct process *)malloc(numberOfProcess * sizeof(struct process));

	for (int i = 0; i < numberOfProcess; i++) 
		scanf("%s %d %d", proc[i].name,&proc[i].t_ready, &proc[i].t_exec);

	qsort(proc, numberOfProcess, sizeof(struct process), cmp);

	for (int i = 0; i < numberOfProcess; i++)
		proc[i].pid = -1;

	proc_assign_cpu(getpid(), PARENT_CPU);
	proc_wakeup(getpid());
	numberOfTime = 0;
	run = -1;
	countFinishing = 0;

	while (1) {
		if (run != -1 && proc[run].t_exec == 0) {
			waitpid(proc[run].pid, NULL, 0);
			printf("%s %d\n", proc[run].name, proc[run].pid);
			run = -1;
			countFinishing++;
			if (countFinishing == numberOfProcess)
				break;
		}
		for (int i = 0; i < numberOfProcess; i++) {
			if (proc[i].t_ready == numberOfTime) {
				proc[i].pid = proc_exec(proc[i]);
				proc_block(proc[i].pid);
			}

		}
		int next = nextP(proc, numberOfProcess, policy);
		if (next != -1) {
			if (run != next) {
				proc_wakeup(proc[next].pid);
				proc_block(proc[run].pid);
				run = next;
				last = numberOfTime;
			}
		}
		UNIT_T();
		if (run != -1)
			proc[run].t_exec--;
		numberOfTime++;
	}
	return 0;
}
