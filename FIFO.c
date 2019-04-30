#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int N, nextproc = 0, workingon = 0;

void sig_child(int signum)
{
    static int finished = 0;
    wait(NULL);
    ++finished;
    ++workingon;
    running = 0;
    if (finished == N) exit(0);
}

void change_priority(pid_t pid) {
    if (running == 0){
        set_priority(proc[nextproc].pid, SCHED_FIFO, HIGH_PRIORITY);
        running = 1;
    }
    if (running != 0){
        SET_PRIORITY(proc[nextproc+1].pid, SCHED_FIFO, PRIORITY_INIT);
    }
}

int main(void) {
    
    // init

    scanf("%d", &N);
    process* proc;
    proc = take_tasks(N);
    
    for (int i = 0; i < nproc; i++){
        proc[i].pid = -1;
    }
    
    while (1) {
        struct sigaction act;
        act.sa_flags = 0;
        act.sa_handler = sig_child;
        sigfillset(&act.sa_mask);
        sigaction(SIGCHLD, &act, NULL);
    }
    
    
    //F IFO
    for (int time = 0, int i = N; i > 0; time++) {
        change_priority();
        
        while (nextproc < N && time == proc[nextproc].t_ready) {
            (nextproc < N && time == proc[nextproc].t_ready
            
            create_process(proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            nextproc ++;
            
            change_priority();
        }
        

        run_unit_time();
    }
    exit(0);
}
