#include <server.h>


int main(int argc,char* argv[]) {

	// check if there is one argument to the function
	if (argc != 2) {
		wprintf("usage: %s <port number>\n",argv[0]);
		return 1;
	}

	//check if the port number is a number

	char* udp = argv[1];

	for (;udp != NULL; udp = udp + 1) {
	
		if (!isdigit(*udp)) {
			wprintf("The port must be an integer between %d to %d",UDP_PORT_LOW_RANGE,UDP_PORT_HIGH_RANGE);
			return 1;
		
		}
	}

	//checking whether the udp port is valid or not given that the input is an integer

	int udp_number = wtoi(argv[1]);

	if (udp_number > UDP_PORT_HIGH_RANGE || udp_number < UDP_PORT_LOW_RANGE) {

		wprintf("The port must be an integer between %d to %d", UDP_PORT_LOW_RANGE, UDP_PORT_HIGH_RANGE);
		return 1;

	}

	// here we should have a valid input awaiting to to processed 

	if (win == 1) {
	
	
	}

	if (UNIX == 1) {
	
	
	
	
	}



	return 0;

}