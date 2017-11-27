# EzSerial
A simple serial library to send and receive data.

## How to install
Copy ezserial.h and ezserial.cpp in your project's folder and then just include "ezserial.h".

## How to use
```
//File Talker.cpp
EzSerial serial("/dev/ttyACM0", 57600);
serial.Send("Hello World!\n");
```

```
//File Listener.cpp
EzSerial serial("/dev/ttyACM0", 57600);
std::string received = serial.Receive();
if(received.length() > 0){
  std::cout << received;
}
```
