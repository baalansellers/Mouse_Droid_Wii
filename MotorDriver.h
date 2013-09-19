#include <SoftwareSerial.h>


#define STEERING_ANGLE_MAX    360
#define STEERING_ANGLE_MIN    0
#define STEERING_ANGLE_CENTER 90
#define STEERING_ANGLE_STEP   5

class MotorDriver{
  public:
    MotorDriver(void);
    void init(void);
    void AllStop(void);
    void AllAheadFull(void);
    void AllReverseFull(void);
    void AllAheadLeft(void);
    void AllAheadRight(void);
    void AllReverseLeft(void);
    void AllReverseRight(void);
    void RotateLeft(void);
    void RotateRight(void);
    int getSteeringAngle(void);
    int getGasAngle(void);
    void GetCommand_Wii_12YAx(void);
    void GetCommand_Wii_XYAx(void);
  
  private:
    SoftwareSerial *ss;
};
