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
#include "functions.h"
#define ever    ;;

char S[8]; //scheduling policy
int N; //number of processes

int main(int argc, char *argv[]) {
    
    assign_cpu(getpid(), 0);
    set_priority(getpid(), SCHED_FIFO, INIT_PRIORITY);
    
    //take scheduling type and execute scheduling program
    scanf("%s", S);
    if(strcmp(S, "FIFO") == 0) {
        execl("./FIFO", "./FIFO", NULL);
    }
    else if(strcmp(S, "RR") == 0) {
        execl("./RR", "./RR", NULL);
    }
    else if(strcmp(S, "SJF") == 0) {
        execl("./SJF", "./SJF", NULL);
    }
    else if(strcmp(S, "PSJF") == 0) {
        execl("./PSJF", "./PSJF", NULL);
    }
    else {
        fprintf(stderr, "Invalid scheduling policy: %s\n", S);
        exit(1);
    }
    exit(0);
}
