#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    // init
    int N, nextproc = 0;
    scanf("%d", &N);
    process* proc;
    proc = take_tasks(N);
    
    for (int i = 0; i < nproc; i++){
        proc[i].pid = -1;
    }
    
    //F IFO
    for (int time = 0, int i = N; i > 0; t++) {
        priority_ch(proc[nextproc].pid);
        
        while (ptrReady < nProcess && t == R[nextReady]) {
            
            create_process(proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            nextproc ++;
            priority_ch(proc[nextproc].pid);
        }
        

        run_unit_time();
    }
    exit(0);
}
