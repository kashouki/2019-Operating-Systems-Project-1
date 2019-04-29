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
#include <time.h>
#include <signal.h>
#define FIFO    1
#define RR      2
#define SJF     3
#define PSJF    4
#define ever    ;;

typedef struct process{
    int pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;

int create_proc(process proc) {
    int pid;
    if()
    
    
}

int select_next_process(process proc, int N, int policy, int time) {
    for(int i = 0; i < N; i++) {
        if(proc[i].t_ready == time) {
            proc[i].pid = create_proc(proc[i]);
        }
    }
    
    
    
    
    
}
