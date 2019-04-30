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
#include "process.h"
#include "scheduler.h"
#include "functions.h"

int main(){
	int N; /*number of proc*/
	scanf("%d", &N);

	process *proc = take_task(N);/*scan the task*/
	int ret;
	for(int i = 0; i < N; i++){
		if(proc[i].pid == -1){
			continue;
		}
		if(proc[i].t_exec == 0){
			continue;
		}
		if(ret == -1){
			ret = i;
		}
		else if(proc[i].t_exec < proc[ret].t_exec){
			ret = i;
		}
	}
	
}


