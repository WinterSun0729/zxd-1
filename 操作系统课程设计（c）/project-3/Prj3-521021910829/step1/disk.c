//Design and implement a basic disk-like secondary storage server.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

#define BLOCKSIZE 256

int main(int argc, char *argv[]) {
    int CYLINDERS, SECTORS, track_to_track_time, fd;
    char *filename;
    char *disk_data;

    if (argc != 5) {
        printf("Usage: %s <#cylinders> <#sectors per cylinder> <track-to-track delay> <#disk-storage-filename>\n", argv[0]);
        exit(-1);
    }

    int fd_log = open("disk.log", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd_log == -1) {
        perror("Error: Could not open file 'disk.log'.\n");
        exit(-1);
    }
    // redirect using dup2
    if (dup2(fd_log, STDOUT_FILENO) == -1) {
        perror("Error: Could not dup.");
        exit(-1);
    }
    
    // Parse command-line arguments
    CYLINDERS = atoi(argv[1]);
    SECTORS = atoi(argv[2]);
    track_to_track_time = atoi(argv[3]);
    long FILESIZE = BLOCKSIZE * SECTORS * CYLINDERS;
    filename = argv[4];
    
    // Open disk file and map it into memory
    fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        printf("Error: Could not open file '%s'.\n", filename);
        exit(-1);
    }
    if (lseek(fd, FILESIZE - 1, SEEK_SET) == -1) {
        printf("Error calling lseek() to 'stretch' the file\n");
        exit(-1);
    }
    if (write(fd, "", 1) == -1) {
        printf("Error writing last byte of the file\n");
        exit(-1);
    }
    disk_data = mmap(NULL, FILESIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (disk_data == MAP_FAILED) {
        close(fd);
        printf("Error:Could not map file.\n");
        exit(-1);
    }
    
    // Process requests
    char cmd;
    int c, s;
    int last_c = 0;
    char data[BLOCKSIZE] = "";
    while (1) {
        scanf("%c", &cmd);
        if (cmd == 'E') {
            // Exit
            printf("Goodbye!\n");
            break;
        }
        else if (cmd == 'I') {
            // Information request
            printf("%d %d\n", CYLINDERS, SECTORS);
        } 
        else if (cmd == 'R') {
            // Read request
            scanf("%d %d", &c, &s);
            if (c < 0 || c >= CYLINDERS || s < 0 || s >= SECTORS) {
                printf("No\n");
            } 
            else {
                printf("Yes ");
                memcpy(data, disk_data + (c * SECTORS + s) * BLOCKSIZE, BLOCKSIZE);
                fwrite(data, sizeof(char), strlen(data), stdout);
                printf("\n");
                usleep(track_to_track_time * abs(c - last_c));
            }
        }
        else if (cmd == 'W') {
            // Write request
            scanf("%d %d", &c, &s);
            if (c < 0 || c >= CYLINDERS || s < 0 || s >= SECTORS) {
                printf("No\n");
            }
            else {
                fgets(data, BLOCKSIZE, stdin);
                memcpy(disk_data + (c * SECTORS + s) * BLOCKSIZE, data, strlen(data)-1);
                printf("Yes\n");
                usleep(track_to_track_time * abs(c - last_c));
            }
        }
        else if(cmd == '\n')continue;
        else {
            printf("Instructions Error!\n");
        }
        last_c = c;
    }
    
    // Unmap and close
    if (disk_data != NULL && munmap(disk_data, FILESIZE) == -1) {
        perror("munmap");
        return -1;
    }
    if (fd != -1 && close(fd) == -1) {
        perror("close");
        return -1;
    }
    close(fd_log);
    return 0;
}