
#include "AudioDriver.h"

AudioDriver::AudioDriver() {
  Track = -1;
  Play = 0;
}

void AudioDriver::init() {
  pinMode(CLK,OUTPUT);
  pinMode(DI,OUTPUT);
  //CLK and DI are High unless transmitting
  digitalWrite(CLK,HIGH);
  digitalWrite(DI,HIGH);
  
}

void AudioDriver::task() {
  if (Play) {
    audioCommand(Track);
    Play = 0;
    Track = -1;
  }
}

void AudioDriver::play(unsigned int track) {
  //sendCommand(0);
  if (Track != track) {
      Track = track;
      Play = 1;
  }
}

void AudioDriver::audioCommand(unsigned int Code) {
  /* Wave form is cycle HIGH 200uS LOW 200uS on CLK
     Transmit data bits on the CLK HIGH over DI pin
     CLK and DI should both be HIGH if no transmit */
  
  /* Pull CLK and DI LOW to initialize */
  digitalWrite(CLK,LOW);
  digitalWrite(DI,LOW);
  delay(2); //2 millisecond delay
  
  /* This will be used to track which digit of the
     transmitted 16-bits of data is being sent */
  unsigned int BinDigit = 32768;
  
  for (unsigned int i = 16; i > 0; i--) {
    
    /* Pull CLK HIGH */
    digitalWrite(CLK,HIGH); //Waveform high
    
    /* Start Data transmission */
    if (BinDigit & Code) {
      digitalWrite(DI,HIGH);
    } else {
      digitalWrite(DI,LOW);
    }
    
    delayMicroseconds(200); //200uS delay
    digitalWrite(CLK,LOW);  //Waveform low
    delayMicroseconds(200); //200uS delay
    
    //Setup next digit position in the 16-bits
    BinDigit = BinDigit / 2;
  }
  
  //Return both pins to high, we're done transmitting
  digitalWrite(CLK,HIGH);
  digitalWrite(DI,HIGH);
  
}

void AudioDriver::sendCommand(unsigned int command) {
  //Start bit Low level pulse.
  digitalWrite(CLK, LOW);
  delay(2);
  for (unsigned int mask = 0x8000; mask > 0; mask >>= 1) {
    //Clock low level pulse.
    digitalWrite(CLK, LOW);
    delayMicroseconds(50);
    //Write data setup.
    if (command & mask) {
      digitalWrite(DI, HIGH);
    }
    else {
      digitalWrite(DI, LOW);
    }
    //Write data hold.
    delayMicroseconds(50);
    //Clock high level pulse.
    digitalWrite(CLK, HIGH);
    delayMicroseconds(100);
    if (mask>0x0001){
      //Stop bit high level pulse.
      delay(2);      
    }
  }
  //Busy active high from last data bit latch.
  delay(20);
}
