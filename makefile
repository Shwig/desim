FLAGS = -g -std=c99
objects = main.o priority_queue.o fifo_queue.o config_reader.o

print_list : $(objects)
	cc -o a $(CFLAGS) $(objects)

.PHONY : clean
clean :
	rm a $(objects)
