#include "server_UNIX.h"

#ifdef UNIX




int server_unix_action(int* udp_socket) {





	// output what this version of the program do

	wprintf("This program hopefully fullfils the functionality described in section %d\n", SECTION);

	// beginning

	int socket_ = *udp_socket;

	//we are receiving from the sockets provided and sending back using the same socket.


	//Receiving buffer
	char RecBuffer[BUFFER_SIZE];

	int Buffer_Size = BUFFER_SIZE;

	struct sockaddr SenderAddr;

	int fromlen = sizeof(SenderAddr);

	int receive_size = 0;

	receive_size = recfrom(socket_, RecBuffer, Buffer_Size, 0, &SenderAddr, &fromlen);

	if (receive_size == 0) {

		wprintf("There is an error in the receiving process\n");
		return -1;

	}

	//here we should have received a valid message;

	int is_ftp;

	if (receive_size != 3 || RecBuffer[0] != 'f' || RecBuffer[1] != 't' || RecBuffer[2] != 'p') {

		is_ftp = 0;

	}
	else {

		is_ftp = 1;

	}

	// starting sending back process;
	// using the same socket to send back.

	char msg[3];
	int msg_len;

	if (is_ftp == 1) {

		msg[0] = 'Y';
		msg[1] = 'e';
		msg[2] = 's';
		msg_len = 3;
	}
	else {
		msg[0] = 'N';
		msg[1] = 'o';
		msg_len = 2;

	}

	int msg_sent_len;

	msg_sent_len = sendto(socket_, msg, msg_len, 0, &SenderAddr, &fromlen);

	// all done









	return 0;






















}

#endif