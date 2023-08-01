#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <ctype.h>

//define valuable
int sockfd, newsockfd, portno;
socklen_t clilen;
char buffer[256];
char *line = NULL;
char buf[1024];
struct sockaddr_in serv_addr, cli_addr;
int n;
int* com_num;

//get valid string in buffer
char* getValidString(const char* buffer) {
    int len = strlen(buffer);
    int start = 0, end = len - 1;
    //find the first position with char
    while (start < len && isspace(buffer[start])) {
        start++;
    }
    //find the last position with char
    while (end >= start && isspace(buffer[end])) {
        end--;
    }
    //copy valid string
    int strLen = end - start + 1;
    if (strLen <= 0) {
        return NULL;
    }
    char* validStr = (char*)malloc(sizeof(char) * (strLen + 1));
    if (validStr == NULL) {
        return NULL;
    }
    memcpy(validStr, buffer + start, strLen);
    validStr[strLen] = '\0';
    return validStr;
}

//deal with error
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//set a new strtok to prevent nested strtok error
char * myStrtok;
char * mystrtok( char * s,const char * ct) 
{ 
         
    char *sbegin, *send; 
    sbegin  = s ? s : myStrtok;// 
    if (!sbegin) { 
    return NULL;
    } 
    sbegin += strspn(sbegin,ct);
    if (*sbegin == '\0'){ 
    myStrtok = NULL; 
    return (NULL); 
    } 
    send = strpbrk(sbegin, ct); 
    if(send && *send != '\0') 
    *send++ = '\0'; 
    myStrtok = send; 
    return (sbegin); 
}

//parse the command line(without |)
int parseLine(char *line, char **command_array) {
    char *p;
    int count = 0;
    p = strtok(line, " ");
    while (p && strcmp(p,"|")!= 0){
        command_array[count] = p;
        count++;
        p = strtok(NULL," ");
    }
    return count; 
}

//get substr of a string
char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    for (int i = m; i < n && (*(src + i) != '\0'); i++)
    {
        *dest = *(src + i);
        dest++;
    }
    *dest = '\0';
    return dest - len;
}

//count number of commands devided by "|"
int countPipes(char *line){
    if (line == "") return 0;
    int count = 1;
    for(int i = 0; line[i] != '\0'; i++){
        if(line[i] == '|') count ++;
    }
    return count;
}
//remove " " at the begin of strings
char *ltrim(char *str) 
{ 
    if (str == NULL || *str == '\0') 
    { 
        return str; 
    } 
    int len = 0; 
    char *p = str;
    while (*p != '\0' && isspace(*p)) 
    { 
        ++p; ++len; 
    } 
    memmove(str, p, strlen(str) - len + 1); 
    return str; 
} 
//cammand function
void command(int num, char ***cmd){
	int fd[2];
	pid_t pid;
	int backup = 0;

	for(int i = 0; i < num; i++) {
		if(pipe(fd) < 0)error("Pipe Error");
		if ((pid = fork()) == -1) {
			perror("fork");
			exit(1);
		}
		else if (pid == 0) {
			dup2(backup, STDIN_FILENO);
			if (*cmd != NULL) {
                close(STDOUT_FILENO);
				dup2(fd[1], STDOUT_FILENO);
			}
			close(fd[0]);
			if(execvp((*cmd)[0], *cmd) == -1){
                write(newsockfd, "Command Error\n", 15);
                _exit(1);
            };
			exit(1);
		}
		else {
            if(i == num - 1){
                wait(NULL);
                close(fd[1]);
                backup = fd[0];
                while(read(fd[0], buf, sizeof(buf)) > 0){}
                n = write(newsockfd, buf, sizeof(buf));
                if (n < 0) error("Error writing to socket");
                close(fd[0]);
                bzero(buf,1024);
                cmd++;
            }
			else{
                wait(NULL);
                close(fd[1]);
                backup = fd[0];
                cmd++;
            }
		}
	}
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr,"Error, no port provided\n");
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    error("Error opening socket");
    printf("Accepting connections ...\n");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("Error on binding");
    listen(sockfd,5);

    //serve the client in a loop
    do{
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
        if (newsockfd < 0)
            error("Error on accept");
        printf("New client(%d) is added\n", cli_addr.sin_port);
        
        pid_t ForkPID;
	    ForkPID = fork();
	    switch (ForkPID) {
        case -1:
            printf("Error: Failed to fork.\n");
            break;
        
        //child process deal with clients
        case 0:
            close(sockfd);
            write(newsockfd,"\n========Welcome to Myshell========\n\n",38);
            do{
                //clean the buffer every loop
                bzero(buffer,256);
                bzero(buf,1024);

                n = write(newsockfd,"MyShell> ",10);
                if (n < 0) error("Error writing to socket");
                n = read(newsockfd, buffer, 255);
                if (n < 0) error("Error reading from socket");
    
                line = getValidString(buffer);    
                //no command
                if(line == NULL){
                    write(newsockfd, "No Command\n", 10);
                    continue;
                }      
                //when meet "exit", quit client
                if(strcmp(line, "exit") == 0){
                    printf("Client(%d) is closed\n", cli_addr.sin_port);
                    close(newsockfd);
                    exit(1);
                    return 1;
                }

                printf("Receive from PORT(%d): %s", cli_addr.sin_port, buffer);
                
                int num_of_pipes = countPipes(line);
                char *cmd;
                char *cmd_mod;
                char ***cmd_array = malloc((num_of_pipes+1)*sizeof(char**));
                for(int i = 0; i < num_of_pipes; i++){
                    cmd_array[i] = malloc(3*sizeof(char*));
                }
                //seperate commands
                char *t = mystrtok(line, "|");
                for(int i = 0; i < num_of_pipes; i++){
                    cmd = t;
                    cmd_mod = ltrim(cmd);
                    parseLine(cmd_mod, cmd_array[i]);
                    t = mystrtok(NULL,"|");
                }
                command(num_of_pipes, cmd_array);
                
                //free the space
                for(int i = 0; i < num_of_pipes; i++){
                    free(cmd_array[i]);
                }
                free(cmd_array);
                
            }while(1);
            break;
        
        //parent process accept new client
        default:
            close(newsockfd);
        }
        free(line);
     }while(1);

     close(sockfd);
     return 0; 
}