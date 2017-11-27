extern "C" {
#include <asm/termbits.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
}
#include <iostream>
using namespace std;

#include "ezserial.h"

EzSerial::EzSerial(string deviceName, int baud)
{
   handle=-1;
   Open(deviceName,baud);
}

EzSerial::~EzSerial()
{
  if(handle >=0)
      Close();
}

void EzSerial::Close(void)
{
   if(handle >=0)
      close(handle);
   handle = -1;
}


bool EzSerial::Open(string deviceName , int baud)
{
    struct termios tio;
    struct termios2 tio2;
    this->deviceName=deviceName;
    this->baud=baud;
    handle  = open(this->deviceName.c_str(),O_RDWR | O_NOCTTY /* | O_NONBLOCK */);

    if(handle <0)
       return false;
    tio.c_cflag =  CS8 | CLOCAL | CREAD;
    tio.c_oflag = 0;
    tio.c_lflag = 0;       //ICANON;
    tio.c_cc[VMIN]=0;
    tio.c_cc[VTIME]=1;     // time out every .1 sec
    ioctl(handle,TCSETS,&tio);

    ioctl(handle,TCGETS2,&tio2);
    tio2.c_cflag &= ~CBAUD;
    tio2.c_cflag |= BOTHER;
    tio2.c_ispeed = baud;
    tio2.c_ospeed = baud;
    ioctl(handle,TCSETS2,&tio2);

//   flush buffer
    ioctl(handle,TCFLSH,TCIOFLUSH);

    return true;
}

bool EzSerial::IsOpen(void)
{
   return( handle >=0);
}

bool EzSerial::Send(std::string value)
{
   if(!IsOpen()) return false;
   int rlen= write(handle,value.c_str(),value.size());
   return(rlen == value.size());
}


std::string EzSerial::Receive()
{
	char buffer[1];
	int bytesRead = 0;
	std::string returnString;
   
	if(!IsOpen()) return returnString;
	do
	{
	   bytesRead = read(handle, buffer, 1);

		if(bytesRead > 0)
		{
			returnString += buffer[0];
			if(buffer[0]=='\n'){
				break;
			}
        }

    } while (bytesRead == sizeof(buffer));
	return returnString;
}
