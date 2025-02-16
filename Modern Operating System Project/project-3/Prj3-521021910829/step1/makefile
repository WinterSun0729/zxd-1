obj = $(wildcard *.c)                                                       
	edit = $(patsubst %.c,%.o,$(wildcard *.c))
disk: $(edit)
	gcc -o disk $(edit)
clean:
	-rm *.o
