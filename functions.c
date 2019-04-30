#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

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

//take input tasks. usage: process* proc = take_tasks();
process* take_tasks() {
    int N;
    scanf("%d", &N);
    process *proc = (process *)malloc(N * sizeof(process));
    for(int i = 0; i < N; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    qsort(proc, N, sizeof(process), cmp_t_ready);
    return proc;
}
