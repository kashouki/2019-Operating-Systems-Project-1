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


typedef struct process{
    int pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;


char S[8]; //scheduling policy
int Nn; //number of processes
char N[1024][32]; //names of the processes
int R[1024]; //ready time
int T[1024]; //execution time

int main(int argc, char *argv[]) {
    
    int policy = 0;
    process *proc;
    
    scanf("%s", S);
    if(strcmp(S, "FIFO") == 0) {
        policy = 1;
    }
    else if(strcmp(S, "RR") == 0) {
        policy = 2;
    }
    else if(strcmp(S, "SJF") == 0) {
        policy = 3;
    }
    else if(strcmp(S, "PSJF") == 0) {
        policy = 4;
    }
    else {
        fprintf(stderr, "Invalid scheduling policy: %s\n", S);
        exit(0);
    }
    
    scanf("%d", &Nn);
    proc = (struct process *)malloc(Nn * sizeof(process));
    for(int i = 0; i < Nn; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    
    
    
    
    
    
    
    
    
    exit(0);
}
