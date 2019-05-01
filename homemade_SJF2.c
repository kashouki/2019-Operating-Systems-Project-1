#define _GNU_SOURCE
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/syscall.h>
#define GET_TIME 314
#define PRINTK 315
#define CHILD_CPU 1
#define PARENT_CPU 0
#include "functions.h"
#define ever ;;

static int last,numberOfTime, run, countFinishing;
int running = 0;

int proc_wakeup(int pid)
{
    struct sched_param param;
    param.sched_priority = 0;
    int ret = sched_setscheduler(pid, SCHED_OTHER, &param);
    if (ret < 0) {
        //perror("sched_setscheduler");
        return -1;
    }
    return ret;
}

int proc_block(int pid)
{
    struct sched_param param;
    param.sched_priority = 0;
    int ret = sched_setscheduler(pid, SCHED_IDLE, &param);
    if (ret < 0)
        return -1;
    return ret;
}

int nextP(struct process *proc, int numberOfProcess)
{
    int ret = -1;
    if(run != -1) {
        return ret;
    }
    
    for (int i = 0; i < numberOfProcess; i++) {
        if (proc[i].pid == -1 || proc[i].t_exec == 0)
            continue;
        if (ret == -1 || proc[i].t_exec < proc[ret].t_exec)
            ret = i;
    }
    return ret;
}

int main(int argc, char* argv[])
{
    int numberOfProcess;
    struct process *proc;
    
    scanf("%d", &numberOfProcess);
    
    proc = take_tasks(numberOfProcess);
    
    for (int i = 0; i < numberOfProcess; i++)
        proc[i].pid = -1;
    
    assign_cpu(getpid(), PARENT_CPU);
    proc_wakeup(getpid());
    numberOfTime = 0;
    run = -1;
    countFinishing = 0;
    
    for(ever) {
        if (run != -1 && proc[run].t_exec == 0) {
            fprintf(stderr, "wait for %s\n", proc[run].name);
            waitpid(proc[run].pid, NULL, 0);
            //printf("%s %d\n", proc[run].name, proc[run].pid);
            run = -1;
            countFinishing++;
            if (countFinishing == numberOfProcess)
                break;
        }
        else {
            
            for (int i = 0; i < numberOfProcess; i++) {
                int max = 1000000000;
                int choose;
                if(proc[i].t_ready != -1 && proc[i].t_ready == numberOfTime && proc[i].t_exec < max) {
                    max = proc[i].t_exec;
                    choose = i;
                }
            }
            if(choose != 1000000000) {
                create_proc(&proc[choose].pid, proc[choose].name, i, proc[choose].t_exec);
                proc_block(proc[choose].pid);
                proc[choose].t_ready = -1;
            }
            
            /*
            for (int i = 0; i < numberOfProcess; i++) {
                if (proc[i].t_ready == numberOfTime && proc[i].t_ready != -1) {
                    create_proc(&proc[i].pid, proc[i].name, i, proc[i].t_exec);
                    proc_block(proc[i].pid);
                    proc[i].t_ready = -1;
                }
                
            }
             */
        }
        /*
        if(run == -1) {
            int next = nextP(proc, numberOfProcess);
            if (next != -1) {
                if (run != next) {
                    fprintf(stderr, "%s selected\n", proc[next].name);
                    proc_wakeup(proc[next].pid);
                    //proc_block(proc[run].pid);
                    run = next;
                    last = numberOfTime;
                }
            }
            next = -1;
        }
        
        if (run != -1)
            proc[run].t_exec--;
        for(int i = 0; i < numberOfProcess; i++) {
            if(proc[i].t_ready != -1 && proc[i].t_ready < numberOfTime) {
                proc[i].t_ready = numberOfTime;
            }
        }
         */
        run_unit_time();
        numberOfTime++;
    }
    return 0;
}
