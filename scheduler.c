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
#define FIFO    1
#define RR      2
#define SJF     3
#define PSJF    4
#define ever    ;;
#define WAKE    1
#define BLOCK   -1

char S[8]; //scheduling policy
int N; //number of processes

int cmp(const void *a, const void *b) {
    return ((process *)a)->t_ready - ((process *)b)->t_ready;
}

int main(int argc, char *argv[]) {
    
    int policy = 0;
    process *proc;
    
    //input
    scanf("%s", S);
    if(strcmp(S, "FIFO") == 0) {
        policy = FIFO;
    }
    else if(strcmp(S, "RR") == 0) {
        policy = RR;
    }
    else if(strcmp(S, "SJF") == 0) {
        policy = SJF;
    }
    else if(strcmp(S, "PSJF") == 0) {
        policy = PSJF;
    }
    else {
        fprintf(stderr, "Invalid scheduling policy: %s\n", S);
        exit(0);
    }
    
    scanf("%d", &N);
    proc = (struct process *)malloc(N * sizeof(process));
    for(int i = 0; i < N; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    
    //sort processes by ready time
    qsort(proc, N, sizeof(struct process), cmp);
    
    int time = 0;
    int running = -1;
    int n_finished = 0;
    
    //start processes
    for(ever) {
        
        //check current running process
        if(running != -1 && proc[running].t_exec == 0) {
            waitpid(proc[running].pid, NULL, 0);
            running = -1;
            n_finished++;
            
            if(n_finished == N) {
                break;
            }
        }
        
        //select the next process
        int select = select_next_process(proc, N, policy, time);
        if(select != -1 && running != next) {
            wake_proc();
            
            running = next;
            
        }
        
        //time increment
        
        if(running != -1) {
            proc[running].t_exec--;
        }
        time++;
    }
    
    exit(0);
}
