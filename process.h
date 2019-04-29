#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <errno.h>
#ifndef PROCESS_H_
#define PROCESS_H_

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

typedef struct process{
    int pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;

int exec_proc(process* proc);

int wake_block_proc(int pid, int wakeblock);

int select_next_process(process* proc, int N, int policy, int time, int running);

#endif
