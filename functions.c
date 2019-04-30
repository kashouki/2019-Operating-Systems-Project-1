#define _GNU_SOURCE
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
#include <sys/syscall.h>
#include <time.h>
#include <signal.h>
#include <sched.h>
#include "functions.h"
#define ever    ;;


//run unit of time. usage: run_unit_time();
void run_unit_time() {
    for(int i = 0; i < TIME_UNIT; i++);
}

//cmp for sorting by t_ready
int cmp_t_ready(const void *a, const void *b) {
    return ((process *)a)->t_ready - ((process *)b)->t_ready;
}
//cmp for sorting by t_exec
int cmp_t_exec(const void *a, const void *b) {
    return ((process *)a)->t_exec - ((process *)b)->t_exec;
}

//assign CPU to process
void assign_cpu(pid_t pid, int cpu) {
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu, &mask);
    sched_setaffinity(pid, sizeof(mask), &mask);
}

//set process priority. USE int policy AS THE FUNCTION ITSELF DEFINES, SEE MANUAL; int priority DEFINED IN functions.h
void set_priority(pid_t pid, int policy, int priority) {
    struct sched_param param;
    param.sched_priority = priority;
    sched_setscheduler(pid, policy, &param);
}

//create a process for a task.
void create_proc(pid_t* pid, char name[], int idx, int t_exec) {
    if((*pid = fork()) < 0) {
        fprintf(stderr, "fork error.\n");
        exit(1);
    }
    else if(*pid == 0) {//child
        char IDX[32];
        char T_EXEC[32];
        sprintf(IDX, "%d", idx);
        sprintf(T_EXEC, "%d", t_exec);
        execl("./process", "./process", name, IDX, T_EXEC);
    }
    else if(*pid > 0) {//parent
        assign_cpu(*pid, 1);
        set_priority(*pid, SCHED_FIFO, LOW_PRIORITY);
    }
}

//take input tasks. usage: (process*) proc = take_tasks(N); N = number of tasks
process* take_tasks(int N) {
    process *proc = (process *)malloc(N * sizeof(process));
    for(int i = 0; i < N; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    qsort(proc, N, sizeof(process), cmp_t_ready);
    return proc;
}
