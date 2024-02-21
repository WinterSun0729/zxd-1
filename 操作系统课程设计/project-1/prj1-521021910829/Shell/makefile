all: shell
.PHONY: all
obj = shell.c                                                       
shell.o: shell.c
	gcc -c shell.c
shell: shell.o 
	gcc -o shell shell.o
clean:
	-rm *.o
