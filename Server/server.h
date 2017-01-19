#pragma once


// specify the system manually

#define win 1
#define UNIX 0
#define UDP_PORT_LOW_RANGE 0
#define UDP_PORT_HIGH_RANGE 65535

// other common headers

#include <stdio.h>
#include <string.h>
#include <ctype.h>


// seperate the header for compatability
#if win == 1 
#include <./server_win.h>
#endif // win == 1 


#if UNIX == 1 
#include <./server_UNIX.h>
#endif // UNIX == 1 


