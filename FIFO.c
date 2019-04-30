#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    
    int N, now;
    scanf("%d", &N);
    process* proc;
    proc = take_tasks(N);
    
    for (int i = 0; i < nproc; i++){
        proc[i].pid = -1;
    }
        
    
    int nextproc = 0;
    

    
    for (int time = 0, int i = N; i > 0; t++) {
        set_priority();
        
        while (ptrReady < nProcess && t == R[nextReady]) {
            
            create_process(proc[nextproc].pid, proc[nextproc].name, nextproc, proc[nextproc].t_exec);
            nextproc ++;
            set_priority();
        }
        
        
        
        run_unit_time();
    }
    
    
    exit(0);
}
