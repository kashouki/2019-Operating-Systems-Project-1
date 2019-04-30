/*
 int time = 0;
 int running = -1;
 int n_finished = 0;
 
 //start processes
 for(ever) {
 
 //check current running process
 if(running != -1 && proc[running].t_exec == 0) {
 waitpid(proc[running].pid, NULL, 0);
 running = -1;
 n_finished++;
 
 if(n_finished == N) {
 break;
 }
 }
 
 //select the next process
 int select = select_next_process(proc, N, policy, time, running);
 if(select != -1 && running != select) {
 
 running = select;
 
 }
 
 //time increment
 
 if(running != -1) {
 proc[running].t_exec--;
 }
 time++;
 }
 
 exit(0);
 }
 
 */




/*
 int exec_proc(process* proc) {
 int pid;
 if((pid = fork()) < 0) {
 fprintf(stderr, "fork error");
 exit(1);
 }
 else if(pid == 0) {
 for(int i = 0; i < proc->t_exec; i++) {
 
 
 
 
 }
 exit(0);
 }
 
 return pid;
 }
 
 int wake_block_proc(int pid, int wakeblock) {
 struct sched_param par;
 par.sched_priority = 0;
 int ret;
 if(wakeblock == WAKE) {
 ret = sched_setscheduler(pid, SCHED_OTHER, &par);
 }
 else if(wakeblock == BLOCK) {
 ret = sched_setscheduler(pid, SCHED_IDLE, &par);
 }
 else {
 fprintf(stderr, "wakeblock parameter error\n");
 return -1;
 }
 
 if(ret < 0){
 fprintf(stderr, "sched_setscheduler error\n");
 return -1;
 }
 
 return ret;
 }
 
 int select_next_process(process* proc, int N, int policy, int time, int running) {
 for(int i = 0; i < N; i++) {
 if(proc[i].t_ready == time) {
 proc[i].pid = exec_proc(&proc[i]);
 }
 }
 /*next process judgement*/
int next_process;

/*premptive judgement*/
if(running != 1 && policy == SJF){/*nah*/
    next_process = -1;
}
else if (running != 1 && policy == FIFO){/*nah*/
    next_process = -1;
}
else {/*yes*/
    int loc = -1;
    if(policy == FIFO){
        /*FIFO*/
    }
    else if(policy == SJF){
        /*SJF*/
        int flag = 0;
        for(int i=0; i<N; i++){
            if(proc[i].pid == -1 || proc[i].t_exec == 0){
                continue;
            }
            if(proc[i].t_exec < proc[loc].t_exec){
                flag = 1;
            }
            if(loc == -1 || flag == 1){
                loc = i;
            }
            flag = 0;
        }
    }
    else if(policy == PSJF){
        /*PSJF*/
        for (int i = 0; i < N; i++) {
            if (proc[i].pid == -1 || proc[i].t_exec == 0)
                continue;
            if (loc == -1 || proc[i].t_exec < proc[ret].t_exec)
                loc = i;
        }
    }
    else if(policy == RR){
        /*RR*/
    }
}
}


 */
