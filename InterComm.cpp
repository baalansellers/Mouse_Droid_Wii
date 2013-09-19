
#include "InterComm.h"

InterComm::InterComm(void) {
  xbee = XBee();
  response = XBeeResponse();
  rx = ZBRxResponse();
  msr = ModemStatusResponse();
  masterAddr = XBeeAddress64(MASTER_ADDR_HIGH, MASTER_ADDR_LOW);
  slaveAddr = XBeeAddress64(SLAVE_ADDR_HIGH, SLAVE_ADDR_LOW);
}

void InterComm::begin(int baud) {
  xbee.begin(baud);
}

void InterComm::SendCommand(uint8_t track) {
  uint8_t payload[] = {track};
  ZBTxRequest tx = ZBTxRequest(masterAddr,payload,sizeof(payload));
  //payload[0] = (1 >> 8) & 0xff;
  xbee.send(tx);
}

//TODO Return a struct or object instead, which would contain an outcome status or success flag, something like that
uint8_t InterComm::GetCommand() {
  xbee.readPacket(100);
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      
      if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
        // got a zb rx packet
        
        // now fill our zb rx class
        xbee.getResponse().getZBRxResponse(rx);
        
        return rx.getData(0);
        /*
        if (Track != 3 && rx.getData(0) == 3) {
          Track = 3;
          Play = 1;
        }
        */
        
      } else if (xbee.getResponse().isError()) {
        //display an error code maybe?
        return 0;
      }
    }
}
