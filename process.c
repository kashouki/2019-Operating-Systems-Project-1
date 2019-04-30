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
#include <linux/kernel.h>
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
    
    long t_start = time();
    for(int i = 0; i < t_exec; i++) {
        run_unit_time();
    }
    long t_finish = time();
    
    printk(KERN_INFO, "[Project1] %d %ld %d\n", pid, t_start, t_finish);
    
    exit(0);
}
