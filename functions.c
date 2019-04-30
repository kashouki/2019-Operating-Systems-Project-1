



typedef struct process {
    pid_t pid;
    char name[32];
    int t_ready;
    int t_exec;
}process;


//take input tasks. usage: process* proc = take_tasks();
process* take_tasks() {
    int N;
    scanf("%d", &N);
    process *proc = (process *)malloc(N * sizeof(process));
    for(int i = 0; i < N; i++) {
        scanf("%s%d%d", proc[i].name, &proc[i].t_ready, &proc[i].t_exec);
    }
    return proc;
}




