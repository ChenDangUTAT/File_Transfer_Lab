#include "deliver.h"



int main(int argc,char *argv[]){
	// want to check the two inputs
	if(argc !=3){
		printf("Error, please enter 2 inputs, serverAddress and serverPort\n");
		return 1;
	}

	// want to print out the deliver to input
	

	//want to check the port number


	//check if the port number is a number


	
	int checker = 0;
	for (; checker < strlen(argv[2]); checker++ ) {
		
		// go through
		if (!isdigit(argv[2][checker])) {
	
			printf("The port must be an integer between %d to %d",UDP_PORT_LOW_RANGE,UDP_PORT_HIGH_RANGE);
			return 1;
		
		}
	}

	//checking whether the udp port is valid or not given that the input is an integer

	int udp_number = atoi(argv[2]);

	if (udp_number > UDP_PORT_HIGH_RANGE || udp_number < UDP_PORT_LOW_RANGE) {

		printf("The port must be an integer between %d to %d", UDP_PORT_LOW_RANGE, UDP_PORT_HIGH_RANGE);
		return 1;

	}
	
	char file[256];	
	printf("ftp\n");
	scanf("%s", file);
	
	printf(file);
	
	if(access(file,F_OK) == -1){
		// means not equal to zero

		printf("The file does not exist\n");
		return 0;
		
	}
	
	/*------------------start of get addr-----------------*/
	

	// then use get address to set up
	struct addrinfo hints, *res;
	

	//a status to check if the get address succeed or not
	int status;	

	memset(&hints,0,sizeof hints);
	hints.ai_family = AF_UNSPEC;
	//for UDP
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE; // fill in IP for you 
	//check if the status is correct
	



	//check for the error	
	if((status = getaddrinfo(argv[1],argv[2],&hints,&res)) !=0){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		printf("can not get address successfuly");
 		return 2;

	}
	

	/*------------------end of get addr-----------------*/
	/*-------------------Set up socket-----------------*/
	int socDesc; 
	// get the socket desciptor
	socDesc = socket(res->ai_family,res->ai_socktype, res->ai_protocol);
	/*-----------------end Set up socket------------------*/
	
	// connect!
	connect(socDesc, res->ai_addr, res->ai_addrlen);
	
	//send!
	int bytes_send,len,bytes_receive;
	char* msg= "ftp";
	char* recvMsg;
	len = strlen(msg); 
	
	

	//send the bytes 
	bytes_send = send(socDesc, msg, len,0);

	printf("process test");
	// receive the message?
	bytes_receive = recv(socDesc,recvMsg,1000,0);


	// check if the return msg is yes,
	if(strcmp( recvMsg, "yes") == 0){
		printf("A file transfer can start");
		
	}
	// close the connection
	close(socDesc);
	// free address info
	freeaddrinfo(res);

	return 0;

	


}
