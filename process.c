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
#define ever    ;;

//usage: execl("./process, "./process", name, index, t_exec);
int main(int argc, char *argv[]) {
    char *name = argv[1];
    int idx = atoi(argv[2]);
    int t_exec = atoi(argv[3]);
    
    for(int i = 0; i < t_exec; i++) {
        run_unit_time();
    }
    
    exit(0);
}
