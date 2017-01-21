#include "server_UNIX.h"




int server_unix_action(int* udp_socket) {





	// output what this version of the program do

	printf("This program hopefully fullfils the functionality described in section %d\n", SECTION);

	// beginning

	int socket_ = *udp_socket;

	//we are receiving from the sockets provided and sending back using the same socket.


	//Receiving buffer
	char RecBuffer[BUFFER_SIZE];

	int Buffer_Size = BUFFER_SIZE;

	struct sockaddr SenderAddr;

	int fromlen = sizeof(SenderAddr);

	int receive_size = 0;

	receive_size = recvfrom(socket_, RecBuffer, Buffer_Size, 0, &SenderAddr, &fromlen);

	if (receive_size == 0) {

		printf("There is an error in the receiving process\n");
		return -1;

	}

	//here we should have received a valid message;

	int is_ftp=0;
        
#ifdef DEBUG
   
        
        printf("The message received has a size of %d\n",receive_size);
        RecBuffer[receive_size] = '\0';        
        printf("The message received is %s \n",RecBuffer);

#endif

	if (receive_size != 3 || RecBuffer[0] != 'f' || RecBuffer[1] != 't' || RecBuffer[2] != 'p') {

		is_ftp = 0;

	}
	else {

		is_ftp = 1;

	}

	// starting sending back process;
	// using the same socket to send back.

	char* msg;

	if (is_ftp == 1) {
            
#ifdef DEBUG
            printf("The message received is ftp and resending\n");
            
#endif
            
            msg = "Yes";    
        }
	else {           
        
#ifdef DEBUG
            printf("The message received is ftp and resending\n");
            
#endif
            
            
            msg = "No";
	
        
        
        
        }

	int msg_sent_len;

	msg_sent_len = sendto(socket_, msg,strlen(msg), 0, &SenderAddr,sizeof(struct sockaddr_storage));
        
#ifdef DEBUG
        printf("The byte sent is %d\n",msg_sent_len);
        
        
#endif

	// all done









	return 0;






















}

