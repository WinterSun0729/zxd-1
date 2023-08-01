obj = $(wildcard *.c)                                                       
	edit = $(patsubst %.c,%.o,$(wildcard *.c))
faneuil: $(edit)
	gcc -o faneuil $(edit)
clean:
	-rm *.o
