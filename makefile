CFLAGS = -g

objects = main.c Queue.c Heap.c Config\ Reader.c

Event : $(objects)
	cc -o Event $(objects)

.PHONY : clean
clean :
	rm QueueTest $(objects)
