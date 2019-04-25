all:
	gcc scheduler.c -lpthread -o scheduler
run:
	./scheduler 
clean:
	rm -rf scheduler