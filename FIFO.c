#include <stdio.h>
#include <sched.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.h"


int N, nextproc = 0, workingon = 0, running = 0;
process* proc;

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

    for (int i = 0; i < N; i++){
        proc[i].pid = -1;
    }
    
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = sig_child;
    sigfillset(&act.sa_mask);
    sigaction(SIGCHLD, &act, NULL);
    
    //FIFO
    for (int time = 0, i = N; i > 0; time++) {
        change_priority();
        
        while (nextproc < N && time == proc[nextproc].t_ready) {
            
            create_proc(&proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            nextproc ++;
            
            change_priority();
        }
        

        run_unit_time();
    }
    exit(0);
}
