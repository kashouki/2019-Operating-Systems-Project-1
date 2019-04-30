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
    if(*pid == 0) {//child
        //fprintf(stderr, "child created\n");
        char IDX[32];
        char T_EXEC[32];
        sprintf(IDX, "%d", idx);
        sprintf(T_EXEC, "%d", t_exec);
        execl("./process", "./process", name, IDX, T_EXEC);
    }
    if(*pid > 0) {//parent
        //fprintf(stderr, "this is parent\n");
        assign_cpu(*pid, 1);
        set_priority(*pid, SCHED_FIFO, LOW_PRIORITY);
    }
}

//take input tasks. usage: (process*) proc = take_tasks(N); N = number of tasks
process* take_tasks(int N) {
    //fprintf(stderr, "in take_tasks\n");
    process *proc = (process *)malloc(N * sizeof(process));
    //fprintf(stderr, "taking tasks...\n");
    for(int i = 0; i < N; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    //fprintf(stderr, "tasks taken!\nsorting...\n");
    qsort(proc, N, sizeof(process), cmp_t_ready);
    //fprintf(stderr, "tasks sorted!\n");
    return proc;
}

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int parent(int x){ return x/2; }
int left(int x){ return 2*x; }
int right(int x){ return (2*x + 1); }

void bub_up(heap* hp, process* proc){
    int cur = hp->size;
    int par = parent(cur);
    while(cur != 0 && proc[hp->proc_idx[cur]].t_exec < proc[hp->proc_idx[par]].t_exec  ){
        swap(&hp->proc_idx[cur],&hp->proc_idx[par]);
        cur = par;
        par = parent(cur);
    }
}
void bub_down(heap* hp, process* proc){
    for(int cur=1; cur<=hp->size;){
        int l = left(cur);
        int r = right(cur);
        int min = (proc[hp->proc_idx[r]].t_exec < proc[hp->proc_idx[l]].t_exec)? r:l;
        if( proc[hp->proc_idx[cur]].t_exec > proc[hp->proc_idx[min]].t_exec ){
            swap(&hp->proc_idx[cur],&hp->proc_idx[min]);
            cur = min;
        }
        else{
            break;
        }
    }
}

void remove_min(heap* hp, process* proc){
    hp->proc_idx[1] = hp->proc_idx[hp->size];
    hp->size--;
    bub_down(hp,proc);
}

void insert(heap* hp, int x, process* proc){
    hp->size++;
    hp->proc_idx[hp->size] = x;
    bub_up(hp,proc);
}


heap* create_heap() {
    heap *new = (heap *)malloc(sizeof(heap));
    new->size = 0;
    return new;
}

int heap_min(heap *hp) {
    return hp->proc_idx[1];
}


