obj = $(wildcard *.c)                                                       
	edit = $(patsubst %.c,%.o,$(wildcard *.c))
LCM: $(edit)
	gcc -o LCM $(edit)
clean:
	-rm *.o
