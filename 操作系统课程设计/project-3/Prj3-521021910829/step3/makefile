# Define compiler and compiler flags
CC = gcc
CFLAGS = -Wall

# Define object files for each executable
DISK_OBJ = disk.o
FS_OBJ = fs.o
CLIENT_OBJ = client.o

# Define executable names
DISK_EXEC = disk
FS_EXEC = fs
CLIENT_EXEC = client

# Define default target to build all executables
all: $(DISK_EXEC) $(FS_EXEC) $(CLIENT_EXEC)

# Define dependencies for each executable
$(DISK_EXEC): $(DISK_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(FS_EXEC): $(FS_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_EXEC): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Define how each object file should be built
disk.o: disk.c
	$(CC) $(CFLAGS) -c -o $@ $<

fs.o: fs.c
	$(CC) $(CFLAGS) -c -o $@ $<

client.o: client.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Define how to clean up object and executable files
clean:
	rm -f $(DISK_OBJ) $(FS_OBJ) $(CLIENT_OBJ) $(DISK_EXEC) $(FS_EXEC) $(CLIENT_EXEC) disk.log fs.log disk_file
