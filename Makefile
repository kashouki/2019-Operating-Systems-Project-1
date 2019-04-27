all:
	gcc scheduler.c -o scheduler
run:
	./scheduler 
clean:
	rm -rf scheduler