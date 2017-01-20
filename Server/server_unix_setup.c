#include "server_UNIX.h"
#ifdef UNIX


int server_unix_setup(char* udp_port, int* udp_socket) {


	struct addrinfo hints;

	struct addrinfo* result = NULL;


	// set up the hint for the getaddrinfo()

	// IPv4
	hints.ai_family = AF_INET;

	//UDP
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	// fill in my IP as server
	hints.ai_flags = AI_PASSIVE;


	// this will get the information we need to create a socket
	iResult = getaddrinfo(NULL, udp_port, &hints, &result);

	if (iResult != 0) {

		wprintf("Get Address Info failed\n");
		return -1;

	}

	// now we have the info, we will open up a socket

	int socket_;

	socket_ = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (socket_ == -1) {

		wprintf("Failed to create socket descryptor\n");

		return -1;


	}


	// now we bind

	iResult = bind(socket_, result->ai_addr, result->ai_addrlen);

	if (iResult != 0) {

		wprintf("Failed to bind the socket\n");
		return -1;


	}


	// after we bind we should be OK to send the packets
	// we will use the sendto and recfrom() function to fulfill this part
	// technically the setup is done here and should be success

	//at this point the link list is no longer needed

	FreeAddrInfo(result);

	// and we pass the "binded" socket descryptor to the next function

	*udp_socket = socket_;

	return 0;











}

#endif