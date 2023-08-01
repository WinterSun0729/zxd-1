obj = $(wildcard *.c)                                                       
	edit = $(patsubst %.c,%.o,$(wildcard *.c))
fs: $(edit)
	gcc -o fs $(edit)
clean:
	-rm *.o
