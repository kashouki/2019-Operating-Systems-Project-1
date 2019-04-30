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
//#include <linux/kernel.h>
#include <time.h>
#include <signal.h>
#include <sched.h>
#include "functions.h"
#define ever    ;;

//usage: execl("./process, "./process", name, index, t_exec);
int main(int argc, char *argv[]) {
    char *name = argv[1];
    int idx = atoi(argv[2]);
    int t_exec = atoi(argv[3]);
    
    pid_t pid = getpid();
    fprintf(stderr, "%s %d\n", name, pid);
    
    struct timespec t_start, t_finish;
    
    clock_gettime(CLOCK_REALTIME, &t_start);

    for(int i = 0; i < t_exec; i++) {
        run_unit_time();
    }
    clock_gettime(CLOCK_REALTIME, &t_finish);
    
    char dmesg_buff[512];
    sprintf(dmesg_buff, "[project1] %d %lu.%09lu %lu.%09lu\n", pid, t_start.tv_sec, t_start.tv_nsec, t_finish.tv_sec, t_finish.tv_nsec);
    syscall(PRINTK, dmesg_buff);
    
    exit(0);
}
