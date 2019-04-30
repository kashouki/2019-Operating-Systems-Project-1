#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.h"

int N, nextproc = 0, workingon = 0, running = 0;
process* proc;

int cmp_sum(const void *a, const void *b) {
    return (((process *)a)->t_ready - ((process *)b)->t_ready) +
    (((process *)a)->t_exec - ((process *)b)->t_exec);
}

    
void sig_child(int signum)
{
    static int finished = 0;
    wait(NULL);
    ++finished;
    ++workingon;
    running = 0;
    if (finished == N) exit(0);
}

void change_priority() {
    if (running == 0){
        set_priority(proc[nextproc].pid, SCHED_FIFO, HIGH_PRIORITY);
        running = 1;
    }
    if (running != 0){
        set_priority(proc[nextproc+1].pid, SCHED_FIFO, INIT_PRIORITY);
    }
}

int main(void) {
    
    // init
    
    scanf("%d", &N);
    proc = take_tasks(N);
    
    heap* diu = create_heap();
    
    for (int i = 0; i < N; i++){
        proc[i].pid = -1;
    }
    
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sig_child;
    sigfillset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);
    
    
    for (int j=0; j<N; j++) {
        if (proc[j].t_ready <= time ) {
            insert(diu, j, proc);
            proc[j].t_ready = 999999;
        }
    }
    nextproc = heap_min(diu);
    remove_min(diu, proc);
    
    //F IFOdasdasda
    for (int time = 0, i = N; i > 0; time++) {
        change_priority();
        
        while (nextproc < N && time == (proc[nextproc].t_ready + proc[nextproc].t_exec)) {
            
            create_proc(&proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            
            for (int j=1; j<N; j++) {
                if (proc[j].t_ready <= time ) {
                    insert(diu, j, proc);
                    proc[j].t_ready = 999999;
                }
            }
            nextproc = heap_min(diu);
            remove_min(diu, proc);
            
            change_priority();
        }
        
        

        run_unit_time();
    }
    exit(0);
}