#include "XBee.h"

#define MASTER_ADDR_HIGH   0x0013A200
#define MASTER_ADDR_LOW    0x408916A6
#define SLAVE_ADDR_HIGH    0x0013A200
#define SLAVE_ADDR_LOW     0x40891696

class InterComm {
  public:
    InterComm(void);
    void begin(int baud);
    void SendCommand(uint8_t);
    uint8_t GetCommand(void);
  
  private:
    /* XBee */
    XBee xbee;
    XBeeResponse response;
    ZBRxResponse rx;
    ModemStatusResponse msr;
    XBeeAddress64 masterAddr;
    XBeeAddress64 slaveAddr;
  
};
