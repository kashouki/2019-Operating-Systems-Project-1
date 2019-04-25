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

int main(int argc, char *argv[]) {
    
    //INPUT
    scanf("%s%d", S, &Nn);
    for(int i = 0; i < Nn; i++) {
        scanf("%s%d%d", N[i], &R[i], &T[i]);
    }
    
    
    
    
    exit(0);
}
