#include <unistd.h>
#include "ezserial.h"
#include <iostream>

using namespace std;


int  main(void)
{
    EzSerial serial("/dev/ttyACM0", 57600);
    while(1){
		std::string received = serial.Receive();
		if(received.length() > 0){
			std::cout << received;
		}
	}
    return 0;
}
