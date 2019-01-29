FLAGS = -g -std=c99
objects = main.o desim_functions.o

print_list : $(objects)
	cc -o a $(CFLAGS) $(objects)

main.o : desim_functions.h

.PHONY : clean
clean :
	rm a $(objects)
