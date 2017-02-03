#pragma once

#ifdef WIN
// this header should be responsible for all the windows network code

#include <WinSock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>



//telling what we are doing 

#define SECTION 1

//determining the receiver buff size

#define BUFFER_SIZE 1024

//Possible TCP feature
// the maximum link allowed, for our uses, it should not be very large
#define MAX_PENDING_LINK 3


// this function is responsible for setting up the UDP receiving socket
int server_win_setup(char* udp_port,SOCKET* udp_socket);


// this function should be handling UDP socket behavior and should receive update over time
int server_win_action(SOCKET* udp_socket);


#endif
