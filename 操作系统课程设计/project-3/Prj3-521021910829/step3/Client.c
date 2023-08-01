//Client connect to fs
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <ctype.h>
#include <sys/wait.h>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

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

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[1024];
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    server = gethostbyname(argv[1]);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");

    while (1) {
        fgets(buffer,1023,stdin);
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0){
            error("ERROR writing to socket");
        }
        if (n == 0) {
            printf("Client closed\n");
            close(sockfd);
            break;
        }
        bzero(buffer,1024);

        n = read(sockfd,buffer,1023);
        if (n < 0) {
            error("ERROR reading from socket");
        }
        if (n == 0) {
            printf("Client closed\n");
            close(sockfd);
            break;
        }
        printf("%s",buffer);
        bzero(buffer,1024);
    }
    close(sockfd);
    
    return 0;
}