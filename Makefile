all:
	gcc scheduler.c functions.c -o scheduler
	gcc process.c functions.c -o process
	gcc FIFO.c functions.c -o FIFO
	gcc RR.c functions.c -o RR
	gcc SJF.c functions.c -o SJF
	gcc PSJF.c functions.c -o PSJF
	
run:
	./scheduler 
clean:
	rm -rf scheduler process FIFO RR SJF PSJF