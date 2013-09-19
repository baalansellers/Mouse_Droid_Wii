
#include "Arduino.h"

/* Sparkfun Audio-Sound Breakout */

#define CLK 5
#define DI  6
//TODO: add busy read pin (maybe on pin 7?)

class AudioDriver {
  public:
    AudioDriver(void);
    void audioCommand(unsigned int Code);
    void init(void);
    void task(void);
    void play(unsigned int);
    void sendCommand(unsigned int);
    
  private:
    unsigned int Track;
    boolean Play;
    
};
