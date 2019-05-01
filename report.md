#REPORT 

MEMBER

綦家承 b06902078 資工二
Write the scheduler
Fix major and minor mistake regarding overall performance

林貞 b06902099 資工二
Write the report.md 
Fix minor mistake regarding overall performance

陳智豐 b06902088 資工二 
Arrange the implementation of FIFO and write the code 

方喬 b06502060 機械二 
Arrange the implementation of RR and write the code 

羅寶瑩 b06902091 資工二 
Arrange the implementation of SJF and write the code 

李芍妍 t07902137  資工一 
Arrange the implementation of PSJF and write the code 

#DESIGN 

SCHEDULER 
In the scheduler, we will begin by reading the first line of the input and execute FIFO, RR, SJF or PSJF accordingly. Then, each execution will get the rest of the input. The execution will start the scheduling tasks and create a process for each task when they start. The output will display the scheduled process. 
We will then explain the design of the four scheduling policy that we write in the part below. 
FIRST IN, FIRST OUT (FIFO)
The basic principle for FIFO is that the first to come is the first to be processed.
 In this project implementation, we first scan the number of tasks that will be assigned to each process (N). And then, we set the flags and the handler of the SIGCHLD. Next, we implement the FIFO scheduling policy by these rules. 
-	Firstly, we will call change_priority function, which will adjust the priority of the process
-	Next, while there are unfinished tasks and there are processes that are ready in this current time, we will create process, add next process into the queue and call change_priority function once again

ROUND-ROBIN (RR)
Round Robin scheduling policy means that there are some time slices assigned to each process in equal portions and in circular order, and it will handle the process without priority. 
In this project implementation, we first scan the number of tasks (N). After that, we will set the handler and the flags for the SIGCHLD. Next, we will implement the Round-Robin scheduling policy with these rules :
-	Firstly, we will call priority_change function. to adjust the priority of the tasks
-	Next, while there are unfinished tasks and there are processes that are ready in the current time, we will create new process and push the next process into queue. Inside this while condition also, we will call priority_change function for the second time
-	After that, we will add another condition that will pop process from the queue if it has passed the timer and deduct the remaining time of the process. We will then put this process back into the queue and set the priority of this process to LOW. 

SHORTEST JOB FIRST (SJF)
Shortest job first, pretty explanatory, means that it is a scheduling policy that chooses the job with the shortest execution time. 
In this project implementation, we first scan the number of tasks (N). After that, we will set the handle and the flags for the SIGCHLD. Next, we will implement the SFJ scheduling policy with these rules :
-	We will create a heap
-	Next, while there are unfinished tasks and there are processes that are ready in the current time, we will insert next process into the heap and create new process. We will also decrease the priority of the next process and call the priority_change function

PREEMPTIVE SHORTEST JOB FIRST (PSJF)
Preemptive shortest job first have the same concept as the SFJ, however it is preemptive. Preemptive scheduling means that once a process has been given to the CPU, it still can be interrupted.
In this project implementation, we first scan the number of tasks (N). After that, we will implement the PSJF scheduling policy by these rules :
-	If the process is still running and and there are processes that are ready in the current time, we will call waitpid function. 
-	For there are some unfinished tasks, if the process is ready, we will create new process and block the process to avoid any race conditions.
-	If next process is running, then we will wake the next process and block the current process






