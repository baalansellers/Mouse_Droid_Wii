#include <SoftwareSerial.h>
#include "WiiRemote.h"
#include "InterComm.h"
#include "AudioDriver.h"
#include "MotorDriver.h"


#define TRUCKTYPE TRUCKA

/* My Drivers */
InterComm intercomm = InterComm();
AudioDriver audiodriver = AudioDriver();
MotorDriver motordriver = MotorDriver();

/* WiiMote */
WiiRemote wiiremote;

void setup() {
  /* Xbee */
  intercomm.begin(9600);
  
  /* Wii Remote */
  wiiremote.init();
  
  /* Sparkfun Audio-Sound Breakout */
  audiodriver.init();
  
  /* Motor Driver */
  motordriver.init();
  
  /* Interrupts */
  attachInterrupt(0, listenToPlayCommand, FALLING);
}

void loop() {
  wiiremote.task(&GetCommand_Wii_12YAx);
  if (!(wiiremote.getStatus() & WIIREMOTE_STATE_CONNECTED)) {
    //Shut down motors
    motordriver.AllStop();
  }
  audiodriver.task();
}

void GetCommand_Wii_12YAx() {
  int Angle = getSteeringAngle();
  
  /* Forward Motion - Initiated by Button 2 */
  if (wiiremote.buttonPressed(WIIREMOTE_TWO) && !(wiiremote.buttonPressed(WIIREMOTE_ONE))) {
    if (Angle > 100) {
      motordriver.AllAheadFull();
    }
    else if (Angle < 80) {
      motordriver.AllAheadFull();
    }
    else {
      motordriver.AllAheadFull();
    }
  } 
  /* Backword Motion - Initiated by Button 1 */
  else if (wiiremote.buttonPressed(WIIREMOTE_ONE) && !(wiiremote.buttonPressed(WIIREMOTE_TWO))) {
    if (Angle > 100) {
      motordriver.AllReverseFull();
    }
    else if (Angle < 80) {
      motordriver.AllReverseFull();
    }
    else {
      motordriver.AllReverseFull();
    }
  }
 /* Rotate Motion - Initiated by Button 1+2 */
  else if (wiiremote.buttonPressed(WIIREMOTE_ONE) && wiiremote.buttonPressed(WIIREMOTE_TWO)) {
    if (Angle < 90) {
      motordriver.RotateLeft();
    } else if (Angle >= 90) {
      motordriver.RotateRight();
    }
  }
  else {
    motordriver.AllStop();
  }
  
  /* Audio Control */
  if (wiiremote.buttonPressed(WIIREMOTE_LEFT)) {
    //audiodriver.play(3);
    intercomm.SendCommand(3);
  }
  else if (wiiremote.buttonPressed(WIIREMOTE_RIGHT)) {
    //audiodriver.play(1);
    intercomm.SendCommand(1);
  }
  else if (wiiremote.buttonPressed(WIIREMOTE_DOWN)) {
    //audiodriver.play(2);
    intercomm.SendCommand(2);
  }
  else if (wiiremote.buttonPressed(WIIREMOTE_UP)) {
    //audiodriver.play(4);
    intercomm.SendCommand(4);
  }
  else if (wiiremote.buttonPressed(WIIREMOTE_MINUS)) {
    //audiodriver.play(0);
    intercomm.SendCommand(0);
  }
}

int getSteeringAngle() {
  double rad;
  double deg;

  rad = acos((double) wiiremote.Report.Accel.Y);
  deg = rad * 180.0 / PI;

  /* clipping */
  if (deg > STEERING_ANGLE_MAX) { deg = STEERING_ANGLE_MAX; }
  if (deg < STEERING_ANGLE_MIN) { deg = STEERING_ANGLE_MIN; }

  return (int) deg;
}

int getGasAngle() {
  double rad;
  double deg;
  
  rad = acos((double) wiiremote.Report.Accel.X);
  deg = rad * 180.0 / PI;
  
  /* clipping */
  //if (deg > STEERING_ANGLE_MAX) { deg = STEERING_ANGLE_MAX; }
  //if (deg < STEERING_ANGLE_MIN) { deg = STEERING_ANGLE_MIN; }
 
  //Serial.print("\r\nGas Angle = ");
  //Serial.print((int) deg);
 
  return (int) deg; 
}

void listenToPlayCommand() {
  //audiodriver.play(intercomm.GetCommand());
  audiodriver.play(2);
}
