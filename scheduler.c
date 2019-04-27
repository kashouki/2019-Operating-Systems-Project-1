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

char S[8]; //scheduling policy
int Nn; //number of processes
char N[1024][32]; //names of the processes
int R[1024]; //ready time
int T[1024]; //execution time

int policy;

int main(int argc, char *argv[]) {
    
    //INPUT
    scanf("%s%d", S, &Nn);
    
    if(strcmp(S, "FIFO") == 0) {
        policy = 0;
    }
    else if(strcmp(S, "RR") == 0) {
        policy = 1;
    }
    else if(strcmp(S, "SJF") == 0) {
        policy = 2;
    }
    else if(strcmp(S, "PSJF") == 0) {
        policy = 3;
    }
    else {
        fprintf(stderr. "Invalid scheduling policy.\n");
        exit(0);
    }
    
    
    for(int i = 0; i < Nn; i++) {
        scanf("%s%d%d", N[i], &R[i], &T[i]);
    }
    
    
    
    
    exit(0);
}
