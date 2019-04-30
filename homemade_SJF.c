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
void priority_down(){
    if(running == 0){
        return ;
    }
    set_priority(proc[nextproc].pid, SCHED_FIFO, LOW_PRIORITY);
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
    int i = 0, j = 0;
    scanf("%d", &N);
    proc = take_tasks(N);
    
    heap* diu = create_heap();
    
    for (i = 0; i < N; i++){
        proc[i].pid = -1;
    }
    
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sig_child;
    sigfillset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);
    
    
    int time = 0, start = 0, found = 0;
    
    while (!fonud) {
        for (i=0; i<N; i++) {
            if (proc[i].t_ready == time ) {
                insert(diu, i, proc);
                proc[nextproc].t_ready = 9999999;
                found = 1;
            }
        }
        time ++;
    }
    
    start = time;

    nextproc = heap_min(diu);
    remove_min(diu, proc);
    
    //F IFOdasdasda
    while (1) {
        change_priority();
        
        while (nextproc < N && time == (start + proc[nextproc].t_exec)) {
            priority_down();
            create_proc(&proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            start += proc[nextproc].t_exec;

            for (int i=0; i<N; i++) {
                if (proc[i].t_ready <= time ) {
                    insert(diu, i, proc);
                    proc[nextproc].t_ready = 9999999;
                }
            }
            nextproc = heap_min(diu);
            remove_min(diu, proc);
            
            change_priority();
        }
        
        
        time ++;
        run_unit_time();
    }
    exit(0);
}
