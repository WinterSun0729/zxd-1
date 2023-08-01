obj = $(wildcard *.c)                                                       
	edit = $(patsubst %.c,%.o,$(wildcard *.c))
Copy: $(edit)
	gcc -o Copy $(edit)
clean:
	-rm *.o
