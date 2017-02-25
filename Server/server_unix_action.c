#include "server_UNIX.h"

int server_unix_action(int* udp_socket) {





    // output what this version of the program do

    unsigned section;
#ifdef SECTION1

    section = 1;

#endif

#ifdef SECTION2
    section = 2;
#endif

    printf("This program hopefully function as described in SECTION %d\n", section);

    // beginning

    int socket_ = *udp_socket;

    //we are receiving from the sockets provided and sending back using the same socket.


    //Receiving buffer
    char RecBuffer[BUFFER_SIZE];

    int Buffer_Size = BUFFER_SIZE;

    struct sockaddr SenderAddr;

    int fromlen = sizeof (SenderAddr);

    int receive_size = 0;




    //here we should have received a valid message;


#ifdef SECTION1

    receive_size = recvfrom(socket_, RecBuffer, Buffer_Size, 0, &SenderAddr, &fromlen);


    if (receive_size == 0) {

        printf("There is an error in the receiving packets\n");
        return -1;

    }


    int is_ftp = 0;

#ifdef DEBUG


    printf("The message received has a size of %d\n", receive_size);
    RecBuffer[receive_size] = '\0';
    printf("The message received is %s \n", RecBuffer);

#endif

    if (receive_size != 3 || RecBuffer[0] != 'f' || RecBuffer[1] != 't' || RecBuffer[2] != 'p') {

        is_ftp = 0;

    } else {

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
    } else {

#ifdef DEBUG
        printf("The message received is ftp and resending\n");

#endif


        msg = "No";




    }

    int msg_sent_len;

    msg_sent_len = sendto(socket_, msg, strlen(msg), 0, &SenderAddr, sizeof (struct sockaddr_storage));

#ifdef DEBUG
    printf("The byte sent is %d\n", msg_sent_len);


#endif

    // all done
    return 0;
#endif


#ifdef SECTION2

    struct packet packet;
    //initialize the first ACK number
    int ACK = 0;

    char msg_string[BUFFER_SIZE];

    unsigned i = 0;

    // return message will be in the format of "ACK%d", it should not exceed 12 digit
    // whose maximum will be ACK999999999999
    char msg[12];

    FILE* temp_;

    // initialization complete

    // open a temporary file and allow write only

    temp_ = fopen("temp", "wb+");

    char name[1024];

    do {


        receive_size = recvfrom(socket_, RecBuffer, Buffer_Size, 0, &SenderAddr, &fromlen);


        if (receive_size == 0) {

            printf("There is an error in the receiving packets\n");
            return -1;

        }

        // buffer the initial data 
        for (i = 0; i < BUFFER_SIZE; i++) {

            msg_string[i] = RecBuffer[i];

        }
        // extract data into standard packet
        extraction(msg_string, &packet);

        // check duplicate?
        if (packet.frag_no != ACK + 1) {
            // drop packet please

            sprintf(msg, "ACK%d", ACK);

            int msg_sent_len = sendto(socket_, msg, strlen(msg), 0, &SenderAddr, sizeof (struct sockaddr_storage));
            
            free(packet.filename);
            
            
            continue;


        } else {
            ACK = ACK + 1;

            sprintf(msg, "ACK%d", ACK);

            int msg_sent_len = sendto(socket_, msg, strlen(msg), 0, &SenderAddr, sizeof (struct sockaddr_storage));

            // send ACK 

        }
        
        // NULL Pointer Check
#ifdef NULLDEBUG

        unsigned i;
        for (i = 0; i < packet.size;i++){
        
            if(packet.filedata[i]== '\0'){
            
                printf("There is a null character in received packet %d\n",packet.frag_no);
            
            
            }
        
        
        
        }




#endif

        
        // do something to piece up the file
        
        
        

        fwrite(packet.filedata, sizeof(char),packet.size, temp_);

        strcpy(name, packet.filename);


#ifdef DEBUG
        printf("The received message is %s\n", packet.filedata);
#endif



        free(packet.filename);


    } while (ACK != packet.total_frag);

    // rename with the last packet and close

    rename("temp", name);

    // close the file

    if(fclose(temp_)==0){
        printf("The file is successful created \n");
    }else{
    
        printf("The fclose has encountered error \n %s \n",strerror(errno));
    
    }
























#endif









    return 0;






















}

