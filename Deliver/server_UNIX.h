


//telling what we are doing 

//#define SECTION1
#define SECTION2

//determining the receiver buff size

#define BUFFER_SIZE 2048

//Possible TCP feature
// the maximum link allowed, for our uses, it should not be very large
#define MAX_PENDING_LINK 3



// other necessary libraries for UNIX like system
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "packet.h"
#include "extraction.h"

// this function is responsible for setting up the UDP receiving socket
int server_unix_setup(char* udp_port, int* udp_socket);


// this function should be handling UDP socket behavior and should receive update over time
int server_unix_action(int* udp_socket);




