#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/select.h>
#include <time.h>
#include <signal.h>
#define FIFO    1
#define RR      2
#define SJF     3
#define PSJF    4
#define ever    ;;
#define WAKE    1
#define BLOCK   -1

typedef struct process{
    int pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;

int create_proc(process proc) {
    int pid;
    if(pid = fork() < 0) {
        fprintf(stderr, "fork error");
    }
    else if(pid == 0) {
        
    }
    
    
}

int wake_block_proc(int pid, int wakeblock) {
    struct sched_param par;
    par.sched_priority = 0;
    int ret;
    if(wakeblock == WAKE) {
        ret = sched_setscheduler(pid, SCHED_OTHER, &par);
    }
    else if(wakeblock == BLOCK) {
        ret = sched_setscheduler(pid, SCHED_IDLE, &par);
    }
    else {
        fprintf(stderr, "setscheduler error");
        exit(1);
    }
    
    if(ret < 0){
        perror("sched_setscheduler");
        return -1;
    }
    return ret;
}

int select_next_process(process proc, int N, int policy, int time) {
    for(int i = 0; i < N; i++) {
        if(proc[i].t_ready == time) {
            proc[i].pid = create_proc(proc[i]);
        }
    }
    /*next process judgement*/
    int next_process;

    /*premptive judgement*/
    if(running != 1 && policy == SJF){/*nah*/
	next_process = -1;
    }
    else if (running != 1 && policy == FIFO){/*nah*/
	next = -1;
    }
    else {/*yes*/
	int loc = -1;
	if(policy == FIFO){
       	    /*FIFO*/
	}
	else if(policy == SJF){
	    /*SJF*/
	    int flag = 0;
	    for(int i=0; i<N; i++){
		if(proc[i].pid == -1 || proc[i].t_exec == 0){
		    continue;
		}
		if(proc[i].t_exec < proc[loc].t_exec){
		    flag = 1;
		}
		if(loc == -1 || flag == 1){
		    loc = i;
		}
		flag = 0;
	    }
	}
	else if(policy == PSJF){
		/*PSJF*/
	}
	else if(policy == RR){
		/*RR*/
	}
    }
}

