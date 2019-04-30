#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sched.h>
#include "functions.h"

#define QUEUE_MAX_SIZE 1000007
#define TIME_QUANTUM 500
#define ever ;;

int run;
int queue[QUEUE_MAX_SIZE];
int q_size = 0;
int front = 0, back = 0;
int time_counting = 0, block;
int N;
process* proc;

void push_queue( int x ){
    q_size++;
    back++;
    queue[back] = x;
}

void pop_queue(){
    if(front<back) {
        front++;
        q_size--;
    }
}

int front_queue(){
    return queue[front];
}

void sig_child( int signum ){
    static int num_fin = 0;
    wait(NULL);
    num_fin++;
    pop_queue();
    run = 0;
    block = 0;
    time_counting = 0;
    if( num_fin==N ) {
        exit(0);
    }
}

void incr_nextproc_priority(){
    int next = queue[front+1];
    set_priority( proc[next].pid, SCHED_FIFO, INIT_PRIORITY );
}

void run_nextproc(){
    time_counting = 0;
    int next = queue[front];
    if( proc[next].t_exec <= TIME_QUANTUM )
      block = 1;
    set_priority( proc[next].pid, SCHED_FIFO, HIGH_PRIORITY );
    run = 1;
}

void priority_ch(){
    if(run == 0 && q_size >= 1 )
      run_nextproc();
    if(run == 1 && q_size >= 2 )
      incr_nextproc_priority();
}

int main(int argc, char *argv[]) {
    scanf("%d",&N);

    proc = take_tasks(N);
    
    struct sigaction sig;
    sig.sa_flags = 0;
    sig.sa_handler = sig_child;
    sigfillset(&sig.sa_mask);
    sigaction(SIGCHLD, &sig, NULL);

    int nextproc = 0;
    
    int t = 0;
    for(ever) {
        priority_ch();
        while( nextproc < N && t == proc[nextproc].t_ready ){
            create_proc( &proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            push_queue( nextproc );
            nextproc++;
            priority_ch();
        }

        run_unit_time();
        time_counting++;

        if(block == 0 && run == 1 && time_counting == TIME_QUANTUM ){
            int cur = queue[front];
            proc[cur].t_exec -= TIME_QUANTUM;
            set_priority( proc[cur].pid, SCHED_FIFO, LOW_PRIORITY );
            pop_queue();
            push_queue( cur );
            run = 0;
            priority_ch();
        }
        t++;
    }
    exit(0);
}

