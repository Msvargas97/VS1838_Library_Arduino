#ifndef _VS1838_H
#define _VS1838_H

class VS1838 {
  public: VS1838(unsigned char pin,unsigned char LED=255);
  unsigned int read();
  private:
  void setPins();
  unsigned char _pin,_led;

};
#endif

