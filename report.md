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

TASK AND ANALYSIS

FIFO

Sample Test 1

![FIFO1](https://user-images.githubusercontent.com/49953935/57005027-d58e7f00-6c06-11e9-9ad1-e21a5cd1e5f5.png)

Sample Test 2

![FIFO2](https://user-images.githubusercontent.com/49953935/57005408-76326e00-6c0a-11e9-8cda-4603d113968b.png)

Sample Test 3

![fifo3](https://user-images.githubusercontent.com/49953935/57005409-77639b00-6c0a-11e9-8432-722cf325f0e4.png)

Sample Test 4

![FIFO4](https://user-images.githubusercontent.com/49953935/57005413-7af72200-6c0a-11e9-93fb-beb6b5cf51b3.png)

Sample Test 5

![FIFO5](https://user-images.githubusercontent.com/49953935/57005417-7cc0e580-6c0a-11e9-997d-7e153375176c.png)

RR

Sample Test 1

![RR1](https://user-images.githubusercontent.com/49953935/57005435-af6ade00-6c0a-11e9-8483-bf305dd35fdd.png)

Sample Test 2

![RR2](https://user-images.githubusercontent.com/49953935/57005437-b0037480-6c0a-11e9-8d1b-38744d1adce7.png)

Sample Test 3

![RR3](https://user-images.githubusercontent.com/49953935/57005438-b09c0b00-6c0a-11e9-8ab3-4b9cdce262b0.png)

Sample Test 4

![RR4](https://user-images.githubusercontent.com/49953935/57005440-b134a180-6c0a-11e9-9063-aef2b6b4daee.png)

Sample Test 5

![RR5](https://user-images.githubusercontent.com/49953935/57005442-b2fe6500-6c0a-11e9-9932-b63892da2106.png)

SJF

Sample Test 1

![SJF1](https://user-images.githubusercontent.com/49953935/57005465-db865f00-6c0a-11e9-9b9f-b961549e195e.png)

Sample Test 2

![SJF2](https://user-images.githubusercontent.com/49953935/57005466-db865f00-6c0a-11e9-9ef2-0992e626ef0b.png)

Sample Test 3

![SJF3](https://user-images.githubusercontent.com/49953935/57005467-dc1ef580-6c0a-11e9-87da-1f34410bcede.png)

Sample Test 4

![SJF4](https://user-images.githubusercontent.com/49953935/57005469-dcb78c00-6c0a-11e9-8a6c-5ddca4535a5f.png)

Sample Test 5

![SJF5](https://user-images.githubusercontent.com/49953935/57005472-dfb27c80-6c0a-11e9-8615-7de799b9bd6f.png)

PSJF

Sample Test 1

![PSJF1](https://user-images.githubusercontent.com/49953935/57005485-0375c280-6c0b-11e9-80cd-7100fd526822.png)

Sample Test 2

![PSJF2](https://user-images.githubusercontent.com/49953935/57005486-04a6ef80-6c0b-11e9-98f5-c8c586a74645.png)

Sample Test 3

![PSJF3](https://user-images.githubusercontent.com/49953935/57005487-04a6ef80-6c0b-11e9-84e6-4931a7192a56.png)

Sample Test 4

![PSJF4](https://user-images.githubusercontent.com/49953935/57005488-053f8600-6c0b-11e9-803a-be7c56c0fb2e.png)

Sample Test 5

![PSJF5](https://user-images.githubusercontent.com/49953935/57005489-05d81c80-6c0b-11e9-8db7-9dfb6166f377.png)


