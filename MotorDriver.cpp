
#include "MotorDriver.h"

MotorDriver::MotorDriver() {
  this->ss = new SoftwareSerial(4,7); //rx, tx
}

void MotorDriver::init() {
  this->ss->begin(115200);
}

void MotorDriver::AllStop() { 
  this->ss->print("1F0\r");
  this->ss->print("2F0\r");
}

void MotorDriver::AllAheadFull() {
  this->ss->print("1F9\r");
  this->ss->print("2F9\r");
}

void MotorDriver::AllReverseFull() {
  this->ss->print("1R9\r");
  this->ss->print("2R9\r");
}

void MotorDriver::AllAheadLeft() {
  this->ss->print("1F9\r");
  this->ss->print("2F1\r");
}

void MotorDriver::AllAheadRight() {
  this->ss->print("1F1\r");
  this->ss->print("2F9\r");
}


void MotorDriver::AllReverseLeft() {
  this->ss->print("1R9\r");
  this->ss->print("2R1\r");
}

void MotorDriver::AllReverseRight() {
  this->ss->print("1R1\r");
  this->ss->print("2R9\r");
}

void MotorDriver::RotateLeft() {
  this->ss->print("1R9\r");
  this->ss->print("2F9\r");
}

void MotorDriver::RotateRight() {
  this->ss->print("1F9\r");
  this->ss->print("2R9\r");
}
