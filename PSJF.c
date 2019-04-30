// /*#include <stdio.h>
// #include <stdlib.h>
// #include "functions.c"

// bool compare(process a,process b)
// {
// 	return a.t_ready<b.t_ready;
// }

// bool compare2(process a,process b)
// {
// 	return a.t_exec<b.t_exec;
// 	/* This Schedule will always return TRUE
// 	if above condition comes*/
// }

// int main(int argc, char *argv[]) {
//     int 
//     int N;
//     scanf("%d", &N);
//     process* proc;
//     proc = take_tasks(N);
    
//     sort(proc,proc+N,compare);
//     i=0;
//     pcom=0;
//     while(pcom<N){
//         for(j=0;j<n;j++)
// 		{
// 			if(proc[j].t_ready>i)
// 			break;
// 		}
//         sort(proc,proc+j,compare2);
        
//         if(j>0)
// 		{

// 			for(j=0;j<n;j++)
// 			{
// 				if(proc[j].t_exec!=0)
// 				break;
// 			}
// 			if(proc[j].t_ready>i)
// 				i=proc[j].t_ready;
// 			//proc[j].ct=i+1;
// 			proc[j].exec--;
// 		}
//         i++;
// 		pcom=0;
// 		for(j=0;j<N;j++)
// 		{
// 			if(proc[j].t_exec==0)
// 			pcom++;
// 		}
//     }
//     exit(0);
// }
// */
	#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>

#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define GET_TIME 314
#define PRINTK 315

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
		unsigned long start_sec, start_nsec, end_sec, end_nsec;
		char to_dmesg[200];
		syscall(GET_TIME, &start_sec, &start_nsec);
		for (int i = 0; i < proc.t_exec; i++) {
			UNIT_T();
#ifdef DEBUG
			if (i % 100 == 0)
				fprintf(stderr, "%s: %d/%d\n", proc.name, i, proc.t_exec);
#endif
		}
		syscall(GET_TIME, &end_sec, &end_nsec);
		sprintf(to_dmesg, "[project1] %d %lu.%09lu %lu.%09lu\n", getpid(), start_sec, start_nsec, end_sec, end_nsec);
		syscall(PRINTK, to_dmesg);
		exit(0);
	}
	
	/* Assign child to another core prevent from interupted by parant */
	proc_assign_cpu(pid, CHILD_CPU);

	return pid;
}

int proc_block(int pid)
{
	struct sched_param param;
	
	/* SCHED_IDLE should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;
}

int proc_wakeup(int pid)
{
	struct sched_param param;
	
	/* SCHED_OTHER should set priority to 0 */
	param.sched_priority = 0;

	int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
	
	if (ret < 0) {
		perror("sched_setscheduler");
		return -1;
	}

	return ret;
}





/* Last context switch time for RR scheduling */
static int t_last;

/* Current unit time */
static int ntime;

/* Index of running process. -1 if no process running */
static int running;

/* Number of finish Process */
static int finish_cnt;

/* Sort processes by ready time */
int cmp(const void *a, const void *b) {
	return ((struct process *)a)->t_ready - ((struct process *)b)->t_ready;
}







int main(void)
{
	char sched_policy[256];
	int policy;
	int nproc;
	struct process *proc;

	scanf("%s", sched_policy);
	scanf("%d", &nproc);
	
	proc = (struct process *)malloc(nproc * sizeof(struct process));
	
	qsort(proc, nproc, sizeof(struct process), cmp);

	/* Initial pid = -1 imply not ready */
	for (int i = 0; i < nproc; i++)
		proc[i].pid = -1;

	/* Set single core prevent from preemption */
	proc_assign_cpu(getpid(), PARENT_CPU);
	
	/* Set high priority to scheduler */
	proc_wakeup(getpid());
	
	/* Initial scheduler */
	ntime = 0;
	running = -1;
	finish_cnt = 0;
	
	while(1) {
		//fprintf(stderr, "Current time: %d\n", ntime);

		/* Check if running process finish */
		if (running != -1 && proc[running].t_exec == 0) {
		
#ifdef DEBUG
			fprintf(stderr, "%s finish at time %d.\n", proc[running].name, ntime);
#endif
			//kill(running, SIGKILL);
			waitpid(proc[running].pid, NULL, 0);
			printf("%s %d\n", proc[running].name, proc[running].pid);
			running = -1;
			finish_cnt++;

			/* All process finish */
			if (finish_cnt == nproc)
				break;
		}

		/* Check if process ready and execute */
		for (int i = 0; i < nproc; i++) {
			if (proc[i].t_ready == ntime) {
				proc[i].pid = proc_exec(proc[i]);
				proc_block(proc[i].pid);
#ifdef DEBUG
				fprintf(stderr, "%s ready at time %d.\n", proc[i].name, ntime);
#endif
			}

		}

		/* Select next running  process */
		
		
		if (running != -1){
			next = running;
		}else{
			next = -1
			for (int i = 0; i < nproc; i++) {
				if (proc[i].pid == -1 || proc[i].t_exec == 0)
					continue;
				if (ret == -1 || proc[i].t_exec < proc[ret].t_exec)
					next = i;
			}
		}

		
		if (next != -1) {
			/* Context switch */
			if (running != next) {
				proc_wakeup(proc[next].pid);
				proc_block(proc[running].pid);
				running = next;
				t_last = ntime;
			}
		}

		/* Run an unit of time */
		UNIT_T();
		if (running != -1)
			proc[running].t_exec--;
		ntime++;
	}

	return 0;
}
