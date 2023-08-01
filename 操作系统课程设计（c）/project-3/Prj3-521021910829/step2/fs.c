//Design and implement a basic file system based on FAT
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <time.h>

#define MAX_DATA_LENGTH 1000
#define MAX_INPUT_SIZE 1024
#define BLOCK_SIZE 256
#define NUM_BLOCKS 256
#define MAX_FILENAME_LENGTH 30
#define MAX_FILE_ENTRIES 32
#define MAX_PATH_LENGTH 100

#define CYLINDERS 10
#define SECTORS 10
#define NUM_BLOCKS 256

// DirectoryEntry struct
typedef struct {
    char filename[MAX_FILENAME_LENGTH];
    char type;
    int start_block;
    int file_size;
    char* last_modified;
} DirectoryEntry;

DirectoryEntry root_directory[MAX_FILE_ENTRIES];
char disk[NUM_BLOCKS][BLOCK_SIZE];

char current_directory[MAX_PATH_LENGTH] = "/";

int find_free_entry() {
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (root_directory[i].filename[0] == '\0')
            return i;
    }
    return -1;
}

int find_free_block() {
    for (int i = 0; i < NUM_BLOCKS; i++) {
        if (disk[i][0] == '\0')
            return i;
    }
    return -1;
}

char* concat_strings(const char* str1, const char* str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char* result = (char*)malloc((len1 + len2 + 1) * sizeof(char)); // +1 Used to store '\0'

    strcpy(result, str1);
    strcat(result, str2);

    return result;
}

int find_file(const char* name) {
    char* filename= concat_strings(current_directory, name);
    for (int  entry_index= 0; entry_index < NUM_BLOCKS; entry_index++) {
        if (strcmp(root_directory[entry_index].filename, filename) == 0) {
            free(filename);
            return entry_index;
        }
    }
    free(filename);
    return -1;
}

void create_file(const char* name, char type) {
    char* filename= concat_strings(current_directory, name);
    if(find_file(name) != -1){
        printf("No: same name\n");
        free(filename);
        return;
    } 
    int entry_index = find_free_entry();
    if (entry_index == -1) {
        printf("No: full\n");
        free(filename);
        return;
    }

    strcpy(root_directory[entry_index].filename, filename);
    root_directory[entry_index].type = type;
    root_directory[entry_index].start_block = find_free_block();
    strncpy(disk[root_directory[entry_index].start_block], "\t", 1);
    root_directory[entry_index].file_size = 1;

    printf("Yes\n");
    // set last modified time
    time_t current_time;
    time(&current_time);
    root_directory[entry_index].last_modified = ctime(&current_time);
    root_directory[entry_index].last_modified[strlen(root_directory[entry_index].last_modified) - 1] = '\0';
    
    free(filename);
}

void delete_file(const char* name) {
    char* filename= concat_strings(current_directory, name);
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if(strcmp(root_directory[i].filename, filename) == 0) {
            root_directory[i].filename[0] = '\0';
            root_directory[i].file_size = 0;
            printf("Yes\n");
            free(filename);
            strcpy(disk[root_directory[i].start_block], "\0");
            return;
        }
    }
    printf("No\n");
    free(filename);
}

void list_file() {
    int flag = 1;
    char tmp[256] = "";
    char file_tmp[1024] = "";
    char dir_tmp[256] = "";

    // Sort file and directory names in alphabetical order
    char sorted_files[MAX_FILE_ENTRIES][MAX_FILENAME_LENGTH];
    char sorted_dirs[MAX_FILE_ENTRIES][MAX_FILENAME_LENGTH];
    int num_files = 0;
    int num_dirs = 0;

    // Iterate over root_directory to populate sorted_files and sorted_dirs arrays
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (strncmp(root_directory[i].filename, current_directory, strlen(current_directory)) == 0) {
            flag = 0;
            if (root_directory[i].type == 'F') {
                strcpy(sorted_files[num_files], root_directory[i].filename);
                num_files++;
            } else {
                strcpy(sorted_dirs[num_dirs], root_directory[i].filename);
                num_dirs++;
            }
        }
    }

    // Sort file names in alphabetical order
    for (int i = 0; i < num_files - 1; i++) {
        for (int j = i + 1; j < num_files; j++) {
            if (strcmp(sorted_files[i], sorted_files[j]) > 0) {
                char temp[MAX_FILENAME_LENGTH];
                strcpy(temp, sorted_files[i]);
                strcpy(sorted_files[i], sorted_files[j]);
                strcpy(sorted_files[j], temp);
            }
        }
    }

    // Sort directory names in alphabetical order
    for (int i = 0; i < num_dirs - 1; i++) {
        for (int j = i + 1; j < num_dirs; j++) {
            if (strcmp(sorted_dirs[i], sorted_dirs[j]) > 0) {
                char temp[MAX_FILENAME_LENGTH];
                strcpy(temp, sorted_dirs[i]);
                strcpy(sorted_dirs[i], sorted_dirs[j]);
                strcpy(sorted_dirs[j], temp);
            }
        }
    }

    // Create file_tmp string with sorted file names
    for (int i = 0; i < num_files; i++) {
        sprintf(tmp, "%s, Size:%d, LastModifiedTime:%s", sorted_files[i], root_directory[i].file_size, root_directory[i].last_modified);
        strcat(file_tmp, tmp);
        if (i < num_files - 1) {
            strcat(file_tmp, " ");
        }
    }

    // Create dir_tmp string with sorted directory names
    for (int i = 0; i < num_dirs; i++) {
        sprintf(tmp, "%s", sorted_dirs[i]);
        strcat(dir_tmp, tmp);
        if (i < num_dirs - 1) {
            strcat(dir_tmp, " ");
        }
    }

    // Print the final output
    if (flag) {
        printf("\n");
    } else {
        if (dir_tmp[0] != '\0') {
            strcat(file_tmp, "\n&\n");
        }
        strcat(file_tmp, dir_tmp);
        printf("%s\n", file_tmp);
    }
}

void change_dir(char* path) {
    if (strcmp(path, "..") == 0) {
        // Switch to parent directory
        strcpy(current_directory, strrchr(current_directory, '/'));
    } 
    else if (strcmp(path, "/") == 0) {
        strcpy(current_directory, "/");
    }
    else if (strcmp(path, ".") == 0) {
        strcpy(current_directory, current_directory);
    }
    else {
        if (root_directory[find_file(path)].type == 'D') {
            // Switch to the specified subdirectory
            strcat(current_directory, path);
            strcat(current_directory, "/");
        }
        else {
            printf("Not a Directory\n");
            return;
        }
    }
    printf("Yes: %s\n", current_directory);
}

void write_file(const char* name, int len, const char* data) {
    char* filename= concat_strings(current_directory, name);
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (strcmp(root_directory[i].filename, filename) == 0 && root_directory[i].type == 'F') {
            int start_block = root_directory[i].start_block;

            strncpy(disk[start_block], data, len);
            root_directory[i].file_size = len;
            printf("Yes\n");

            time_t current_time;
            time(&current_time);
            root_directory[i].last_modified = ctime(&current_time);
            root_directory[i].last_modified[strlen(root_directory[i].last_modified) - 1] = '\0';

            free(filename);
            return;
        }
    }
    free(filename);
    printf("No\n");
}

void read_file(const char* name) {
    char* filename= concat_strings(current_directory, name);
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (strcmp(root_directory[i].filename, filename) == 0 && root_directory[i].type == 'F') {
            int start_block = root_directory[i].start_block;
            int file_size = root_directory[i].file_size;

            printf("Yes: ");
            for (int block = start_block; block < start_block + (file_size / BLOCK_SIZE) + 1; block++) {
                printf("%.*s", file_size - (block - start_block) * BLOCK_SIZE, disk[block]);
            }
            printf("\n");

            free(filename);
            return;
        }
    }
    free(filename);
    printf("No\n");
}

void insert_file(const char* name, int position, int length, const char* data) {
    char* filename= concat_strings(current_directory, name);
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (strcmp(root_directory[i].filename, filename) == 0 && root_directory[i].type == 'F') {
            int start_block = root_directory[i].start_block;  
            if (position > root_directory[i].file_size)
                position = root_directory[i].file_size;

            if (root_directory[i].file_size + length > MAX_DATA_LENGTH) {
                printf("Error: Inserted data exceeds maximum file size.\n");
                return;
            }
                
            memmove(disk[start_block] + position + length, disk[start_block] + position, root_directory[i].file_size - position);
            strncpy(disk[start_block] + position, data, length);
            root_directory[i].file_size += length;
            printf("Yes\n");

            time_t current_time;
            time(&current_time);
            root_directory[i].last_modified = ctime(&current_time);
            root_directory[i].last_modified[strlen(root_directory[i].last_modified) - 1] = '\0';

            free(filename);
            return;
        }
    }
    free(filename);
    printf("No\n");
}

void delete_content(const char* name, int position, int length) {
    char* filename= concat_strings(current_directory, name);
    for (int i = 0; i < MAX_FILE_ENTRIES; i++) {
        if (strcmp(root_directory[i].filename, filename) == 0 && root_directory[i].type == 'F') {
            int start_block = root_directory[i].start_block;  
            if (position >= root_directory[i].file_size) {
                printf("Error: Invalid position.\n");
                return;
            }

            if (position + length > root_directory[i].file_size)
                length = root_directory[i].file_size - position;

            memmove(disk[start_block] + position, disk[start_block] + position + length, root_directory[i].file_size - position - length);
            root_directory[i].file_size -= length;
            printf("Yes\n");

            time_t current_time;
            time(&current_time);
            root_directory[i].last_modified = ctime(&current_time);
            root_directory[i].last_modified[strlen(root_directory[i].last_modified) - 1] = '\0';

            free(filename);
            return;
        }
    }
    free(filename);
    printf("No\n");
}

void clear_all() {
    for(int i = 0; i < MAX_FILE_ENTRIES; i++){
        strcpy(root_directory[i].filename, "");
        if(root_directory[i].type == 'F')
            strcpy(disk[root_directory[i].start_block], "\0");
        root_directory[i].file_size = 0;
    }
    printf("Done\n");
}

int main() {
    char input[MAX_INPUT_SIZE];
    char command[MAX_INPUT_SIZE];
    char arg1[MAX_INPUT_SIZE];
    char arg2[MAX_INPUT_SIZE];
    char arg3[MAX_INPUT_SIZE];
    char arg4[MAX_INPUT_SIZE];
    int running = 1;

    // set log

    // int fd_log = open("fs.log", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
    // if (fd_log == -1) {
    //     perror("Error: Could not open file 'disk.log'.\n");
    //     exit(-1);
    // }
    // // redirect using dup2
    // if (dup2(fd_log, STDOUT_FILENO) == -1) {
    //     perror("Error: Could not dup.");
    //     exit(-1);
    // }

    while (running) {
        printf("My File System > ");
        fgets(input, MAX_INPUT_SIZE, stdin);

        if (sscanf(input, "%s %s %s %s %s", command, arg1, arg2, arg3, arg4) < 1) {
            continue;
        }
        if (strcmp(command, "e") == 0) {
            printf("Goodbye!\n");
            running = 0;
            return 0;
        } 
        if (strcmp(command, "f") == 0) {
            clear_all();
        } 
        else if (strcmp(command, "mk") == 0) {
            create_file(arg1, 'F');
        } 
        else if (strcmp(command, "mkdir") == 0) {
            create_file(arg1, 'D');
        } 
        else if (strcmp(command, "rm") == 0) {
            delete_file(arg1);
        } 
        else if (strcmp(command, "rmdir") == 0) {
            delete_file(arg1);
        } 
        else if (strcmp(command, "cd") == 0) {
            change_dir(arg1);
        }
        else if (strcmp(command, "ls") == 0) {
            list_file();
        }
        else if (strcmp(command, "cat") == 0) {
            read_file(arg1);
        }
        else if (strcmp(command, "w") == 0) {
            int len = atoi(arg2);
            sscanf(input, "%*s %*s %*s %[^\n]", arg3);
            write_file(arg1, len, arg3);
        }
        else if (strcmp(command, "i") == 0) {
            int pos = atoi(arg2);
            int len = atoi(arg3);
            sscanf(input, "%*s %*s %*s %*s %[^\n]", arg4);
            insert_file(arg1, pos, len, arg4);
        }
        else if (strcmp(command, "d") == 0) {
            int pos = atoi(arg2);
            int len = atoi(arg3);
            delete_content(arg1, pos, len);
        } 
        else {
            printf("Invalid command.\n");
        }
    }

    // set log
    // close(fd_log);

    return 0;
}