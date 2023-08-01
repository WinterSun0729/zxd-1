#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<time.h>
int main(int argc, char* argv[]){
	//open file
	FILE *src;
	src = fopen(argv[1],"r");
	if(src == NULL){
		printf("Error!");
		fclose(src);
		exit(-1);
	}
	FILE *dest;
	dest = fopen(argv[2],"w+");
	if(dest == NULL){
		printf("Error!");
		fclose(src);
		exit(-1);
	}
	
	int length = atoi(argv[3]);
	char buffer[length];
	
	//create mypipe
	int mypipe[2];
	if (pipe(mypipe)) {
		fprintf (stderr, "Pipe failed.\n");
		return -1;
	}
	
	//start timer
	clock_t start, end;
	double elapsed;
	start = clock();
	
	//fork process
	pid_t ForkPID;
	ForkPID = fork();
	switch (ForkPID) {
	case -1:
		printf("Error: Failed to fork.\n"); break;
	// 0, this is the child process
	//read process
	case 0:
		close(mypipe[0]);
		do {
      			fread(buffer,length,1,src);
     			if( feof(src) ) {
       				break ;
      			}
			write(mypipe[1],buffer,sizeof(buffer));
   		} while(1);
		close(mypipe[1]);
		fclose(src);
		printf("Read file end.\n");
	break;
	// > 0, parent process and the PID is the child's PID
	//write process
	default:
		close(mypipe[1]);
		while (read(mypipe[0],buffer,sizeof(buffer)) > 0) {
			fwrite(buffer,length,1, dest);
		}
		close(mypipe[0]);
		fclose(dest);
		printf("Write file end.\n");
		
		//end timer
		end = clock();
		elapsed = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
		printf("Time used: %f millisecond.\n", elapsed);
	}
	return 0;
}