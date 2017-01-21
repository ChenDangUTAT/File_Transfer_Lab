#pragma once


// specify the system manually


//#define WIN
#define UNIX

#define UDP_PORT_LOW_RANGE 0
#define UDP_PORT_HIGH_RANGE 65535

// other common headers

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

// seperate the header for compatability
#include "server_win.h"
#include "server_UNIX.h"



