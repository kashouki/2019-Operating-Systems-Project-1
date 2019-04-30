#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define TIME_UNIT 1000000UL

typedef struct process {
    pid_t pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;

//run unit of time. usage: run_unit_time();
void run_unit_time();

//for function process* take_tasks();
int cmp(const void *a, const void *b);

//take input tasks. usage: process* proc = take_tasks();
process* take_tasks();

#endif
