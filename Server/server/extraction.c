/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "extraction.h"
#define DEBUG

void extraction(char* msg_string, struct packet* packet) {
    // extract total_frag
#ifdef DEBUG

    printf("The raw string is %s\n\n\n", msg_string);


#endif

    unsigned ext_counter = 0;

    for (; msg_string[ext_counter] != ':'; ext_counter++) {

    }

    packet->total_frag = atoi(msg_string);

#ifdef DEBUG

    printf("The total_frag is %d\n", packet->total_frag);


#endif




    // extract complete


    ext_counter++;

    // extract frag_no

    packet->frag_no = atoi(msg_string + ext_counter);

    for (; msg_string[ext_counter] != ':'; ext_counter++) {

    }



    // extract complete

#ifdef DEBUG

    printf("The frag number is %d\n", packet->total_frag);


#endif






    // extract size
    ext_counter++;

    packet->size = atoi(msg_string + ext_counter);

    for (; msg_string[ext_counter] != ':'; ext_counter++) {

    }



    // extract complete
#ifdef DEBUG

    printf("The size is %d\n", packet->size);


#endif



    // extract name

    ext_counter++;

    packet->filename = malloc(sizeof (char)*MAX_NAME_SIZE);

    unsigned name_counter = 0;

    for (; msg_string[ext_counter + name_counter] != ':'; name_counter++) {
        packet->filename[name_counter] = msg_string[ext_counter + name_counter];

    }

    ext_counter += name_counter;
    // extraction data

#ifdef DEBUG

    printf("The file name is %s\n", packet->filename);

#endif

    unsigned i;
    for (i = 1; i < packet->size + 1; i++) {

        packet->filedata[i - 1] = msg_string[ext_counter + i];


    }
#ifdef DEBUG
    printf("The content of the file is ");
    for(i = 0 ; i < packet->size;i++)
    printf("%c", packet->filedata[i]);
    printf("\n");
#endif




    //extraction complete



}