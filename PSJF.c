#include <stdio.h>
#include <stdlib.h>

bool compare(process a,process b)
{
	return a.t_ready<b.t_ready;
}

bool compare2(process a,process b)
{
	return a.t_exec<b.t_exec;
	/* This Schedule will always return TRUE
	if above condition comes*/
}

int main(int argc, char *argv[]) {
    int 
    int N;
    scanf("%d", &N);
    process* proc;
    proc = take_tasks(N);
    
    sort(proc,proc+N,compare);
    i=0;
    pcom=0;
    while(pcom<N){
        for(j=0;j<n;j++)
		{
			if(proc[j].t_ready>i)
			break;
		}
        sort(proc,proc+j,compare2);
        
        if(j>0)
		{

			for(j=0;j<n;j++)
			{
				if(proc[j].t_exec!=0)
				break;
			}
			if(proc[j].t_ready>i)
				i=proc[j].t_ready;
			proc[j].ct=i+1;
			proc[j].exec--;
		}
        i++;
		pcom=0;
		for(j=0;j<N;j++)
		{
			if(proc[j].t_exec==0)
			pcom++;
		}
    }
    exit(0);
}
