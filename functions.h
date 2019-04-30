#define TIME_UNIT 1000000UL
#define LOW_PRIORITY 25
#define INIT_PRIORITY 50
#define HIGH_PRIORITY 75

typedef struct process {
    pid_t pid;
    char name[32];
    int t_ready;
    int t_exec;
    int t_comp;
}process;

//run unit of time. usage: run_unit_time();
void run_unit_time();

//cmp for sorting by t_ready
int cmp_t_ready(const void *a, const void *b);

//cmp for sorting by t_exec
int cmp_t_exec(const void *a, const void *b);

//assign CPU to process
void assign_cpu(pid_t pid, int cpu);

//set process priority
void set_priority(pid_t pid, int policy, int priority);

//create a process for a task.
void create_proc(pid_t* pid, char name[], int idx, int t_exec);

//take input tasks, tasks already sorted by t_ready. usage: (process*) proc = take_tasks(N);
process* take_tasks(int N);
