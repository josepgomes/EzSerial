#include <unistd.h>
#include "ezserial.h"
#include <iostream>

using namespace std;


int  main(void)
{
    EzSerial serial("/dev/ttyACM0", 57600);
    while(1){
		serial.Send("this is it\n");
		usleep(1000000);
	}
    return 0;
}

