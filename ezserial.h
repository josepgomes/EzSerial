#include <string>

class  EzSerial
{

public:

  int handle;
  std::string  deviceName;
  int baud;

  EzSerial(std::string deviceName, int baud);
  ~EzSerial();

  bool Send( unsigned char  * data,int len);
  bool Send(unsigned char value);
  bool Send( std::string value);
  std::string Receive();
  bool IsOpen(void);
  void Close(void);
  bool Open(std::string deviceName, int baud);
  bool NumberByteRcv(int &bytelen);
};
