all: single multi
.PHONY: all
obj1 = single.c
obj2 = multi.c                                        
single.o: single.c
	gcc -c single.c
client.o: multi.c
	gcc -c multi.c
single: single.o 
	gcc -o single single.o
client: multi.o
	gcc -o multi multi.o
clean:
	-rm *.o
