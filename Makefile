all:
	gcc scheduler.c process.c -o scheduler
run:
	./scheduler 
clean:
	rm -rf scheduler