#this target will compile all the file 
OBJS = file1 file2 file3
CC = gcc


all: file1 file2  
#create a target
file1:
	$(CC) deliver.c -o DeliverTest -lm

file2:
	$(CC) server.c server.h -o server.o
	$(CC) server_unix_action.c server_UNIX.h server-o server_unix_action.o
	#$(CC) server_unix_setup.c  -o server_unix_setup.o

#file3:
	#$(CC)server.o server_unix_action.o server_unix_setup.o -o Server
clean:
	rm -rf $(OBJS)
