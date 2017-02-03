#include "deliver.h"

char * processFile(char* fileName, struct packet* testPack, int *totalSize);
char * processMsg(int* totalSize,struct packet* testPack,const char* totalFile);

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
    char type[4];

	printf("Please enter the message follows by 'ftp <filename>' format\n");
 
	scanf("%s%s",type, file);
	
    //check the correctness of ftp
	if(strcmp(type,"ftp")!=0){
		printf("Error, plese see the format!");
		return 0;
	}
	
	
	
	if(access(file,F_OK) == -1){
		// means not equal to zero

		printf("The file does not exist\n");
		return 0;
		
	}
	
   /*-----------------get the file attributes------------*/
   struct packet testPacket;
	int totalSize;
	char* totalFile;
   totalFile = processFile(file,&testPacket,&totalSize);
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

	if(socDesc == 0){
		printf("soc get failed");
		return 0;
	}
	/*-----------------end Set up socket------------------*/
	
	// connect!
	// connect(socDesc, res->ai_addr, res->ai_addrlen);
	
	//send!
	int bytes_send,len,bytes_receive;
	

	// you have to initalize the msg
	char* recvMsg = malloc(sizeof(char) * 1024);

	
	/*----------set up the testPack, and send the first byte of data-----------*/
	while(totalSize >0){
  		
		char* msg = processMsg(&totalSize,&testPacket,totalFile);
	
		//send the bytes 
		bytes_send = sendto(socDesc, msg, strlen(msg)+1,0,res->ai_addr,sizeof(struct sockaddr_storage ));

	
		// receive the message?
		//read the text book man!
		int fromLen = sizeof(struct sockaddr_storage);


		struct sockaddr from;

		// define a clock to track the time
		clock_t begin = clock();


		bytes_receive = recvfrom(socDesc,recvMsg,1000,0, &from, &fromLen);
		clock_t end = clock();

		float time_spent = (float)(end - begin) / CLOCKS_PER_SEC;
		
		printf("%f\n",time_spent);

	 
		printf("%s",recvMsg);
		printf("The received byte is %d\n", bytes_receive);

		// check if the return msg is yes,
		if(strcmp( recvMsg, "Yes") == 0){
			printf("A file transfer can start\n");
		
		}
		else{
			printf("not succeed");
		}
}
	// close the connection
	close(socDesc);
	// free address info
	freeaddrinfo(res);

	return 0;

	
}

char * processFile(char* fileName, struct packet* testPack, int *totalSize){ 

 	struct stat st;
	FILE *f;
   // does the initialization for the file content
   stat(fileName,&st);

   // get the size of file
   *totalSize = st.st_size; 
   f = fopen(fileName, "rb");
   printf("%d\n", *totalSize);
   char* totalFile = malloc(sizeof(char) *(*totalSize+1));
  
	//read the file contents into buffer
   fread(totalFile, *totalSize, 1,f);


   // set the attribute of testPack
   printf("%s\n",totalFile);
	testPack->total_frag = ceil(((double)*totalSize /1000));
   printf("%d\n",testPack->total_frag);
   testPack->frag_no =  0;
   testPack->size = (unsigned int) *totalSize; 
   testPack->filename  = fileName; 


   return totalFile;
 }  
// process and return the new msg 
char * processMsg(int* totalSize,struct packet* testPack,const char* totalFile){

 		char* msg= malloc(sizeof(char)*1048);
		
		if(*totalSize >1000){
			testPack->size =1000;
			*totalSize -=1000;
			memcpy( testPack->filedata, &totalFile[(testPack->frag_no)*1000], 1000 );
		}

		// update the toatl Size each ru 
      else{
 			testPack->size =*totalSize;
			memcpy( testPack->filedata, &totalFile[(testPack->frag_no)*1000], *totalSize );
			*totalSize = 0;
			
		}
		testPack->frag_no ++;
		char *temp = malloc(sizeof (20));
		
		sprintf(temp, "%d", testPack->total_frag);
		strcat(msg,temp);
		strcat(msg,":");
		sprintf(temp, "%d", testPack->frag_no);
		strcat(msg,temp);
		strcat(msg,":");
		sprintf(temp, "%d", testPack->size);
		strcat(msg,temp);
		strcat(msg,":");
		strcat(msg,testPack->filename);
		strcat(msg,":");
		strcat(msg,testPack->filedata);
		
		
      free(temp);
		printf("%s\n",msg);
		return msg;
}
