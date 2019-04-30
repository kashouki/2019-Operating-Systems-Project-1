#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include "functions.c"

#define QUEUE_MAX_SIZE 1000007
#define TIME_QUANTUM 500

int run;
process queue[QUEUE_MAX_SIZE]; 
int front=0, back=0;
int time_counting=0, block;
int N;

void push_queue( int x ){
    back++;
    queue[back] = x;
}

void pop_queue(){
    if(front<back) front++;
}

int front_queue(){
    return queue[front];
}

int queue_size(){
    return back - front;
}

void sig_child( int signum ){
    static int num_fin = 0;
    wait(NULL);
    num_fin++;
    pop_queue();
    run = 0;
    flag = 0;
    time_counting = 0;
    if( num_fin==N ) exit(0);
}

void incr_nextproc_priority(){
    int next = queue[front+1];
    set_priority( proc[next].pid, SCED_FIFO, INIT_PRIORITY );
}

void run_nextproc(){
    time_counting = 0;
    int next = queue[front];
    if( proc[next].t_exec <= TIME_QUANTUM )
      block = 1;
    set_priority( proc[next].pid, SCED_FIFO, HIGH_PRIORITY );
    run = 1;
}

void priority_ch(){
    if( !run && queue_size()>=1 )
      run_nextproc();
    if( run && queue_size()>=2 )
      incr_nextproc_priority();
}

int main(int argc, char *argv[]) {
    scanf("%d",&N);

    process* proc;
    proc = take_tasks(N);
    
    struct sigaction sig;
    sig.sa_flags = 0;
    sig.sa_handler = sigchild;
    sigfillset(&sig.sa_mask);
    sigaction(SIGCHILD, &sig, NULL);

    int nextproc = 0;

    for(int t=0, i=N; i>0; t++) {
        priority_ch();
        while( nextproc < N && t == proc[nextproc].t_ready ){
            creat_proc( &proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            push_queue( nextproc );
            nextproc++;
            priority_ch();
        }

        run_unit_time();
        time_counting++;

        if( !block && run && time_counting==TIME_QUANTUM ){
            int cur = front_queue();
            pop_queue();
            proc[cur] -= TIME_QUANTUM;
            set_priority( proc[cur].pid, SCED_FIFO, LOW_PRIORITY );
            push_queue( cur );
            run = 0;
            priority_ch();
        }
    }
    exit(0);
}

