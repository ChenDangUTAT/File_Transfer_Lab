#this target will compile all the file 
OBJS = file1 file2 file3 
CC = gcc


all: file1 file2 file3  
#create a target

file1:
	$(CC) deliver.c -o DeliverTest -lm

file2:
	$(CC) -Wall -c server.c -o server.o
	$(CC) -Wall -c server_unix_action.c -o server_unix_action.o
	$(CC) -Wall -c server_unix_setup.c -o server_unix_setup.o
	$(CC) -Wall -c extraction.c -o extraction.o
file3: 
	$(CC) -o ServerTest server.o server_unix_action.o server_unix_setup.o extraction.o



clean:
	rm -rf $(OBJS)
