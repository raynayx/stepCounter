#include "IMU.h"
#include "types.h"

// #define DEBUG

#define X lsm.calcAccel(lsm.ax)
#define Y lsm.calcAccel(lsm.ay)
#define Z lsm.calcAccel(lsm.az)
#define TAB Serial.print(F("\t"))

void IMU::setupSensor()
{
    Wire.begin();

    if (!lsm.begin() ) // with no arguments, this uses default addresses (AG:0x6B, M:0x1E) and i2c port (Wire).
    {
    #ifdef DEBUG    
        Serial.println(F("Failed to communicate with LSM9DS1."));
        Serial.println(F("Double-check wiring."));
    #endif    
    while (1);
    }
    //  Wire.setClock(400000);
    lsm.settings.gyro.enabled = false;
    lsm.settings.mag.enabled = false;

    lsm.settings.accel.scale = 2;
    // SAMPLE RATE SETTINGS
    // 1 = 10 Hz    4 = 238 Hz
    // 2 = 50 Hz    5 = 476 Hz
    // 3 = 119 Hz   6 = 952 Hz
    lsm.settings.accel.sampleRate = 2;


    lsm.begin();
}

void IMU::configureLSM9DS1Interrupts()
{
   lsm.configAccelInt(XHIE_XL|YHIE_XL|ZHIE_XL, false);
  // 4. Configure accelerometer threshold:
  //   - 20: Threshold (raw value from accel)
  //     Multiply this value by 128 to get threshold value.
  //     (20 = 2600 raw accel value)
  //   - X_AXIS: Write to X-axis threshold
  //   - 10: duration (based on ODR)
  //   - false: wait (wait [duration] before interrupt goes low)
  lsm.configAccelThs(20, X_AXIS, 10, false);
  lsm.configAccelThs(25, Y_AXIS, 10, false);
  lsm.configAccelThs(200, Z_AXIS, 10, false);
  // 5. Configure INT1 - assign it to gyro interrupt
  //   - XG_INT1: Says we're configuring INT1
  //   - INT1_IG_G | INT1_IG_XL: Sets interrupt source to 
  //     both gyro interrupt and accel
  //   - INT_ACTIVE_LOW: Sets interrupt to active low.
  //         (Can otherwise be set to INT_ACTIVE_HIGH.)
  //   - INT_PUSH_PULL: Sets interrupt to a push-pull.
  //         (Can otherwise be set to INT_OPEN_DRAIN.)
  lsm.configInt(XG_INT1, INT1_IG_G | INT_IG_XL, INT_ACTIVE_LOW, INT_PUSH_PULL);

    ////////////////////////////////////////////////
  // Configure INT2 - Gyro and Accel Data Ready //
  ////////////////////////////////////////////////
  // Configure interrupt 2 to fire whenever new accelerometer
  // or gyroscope data is available.
  // Note XG_INT2 means configuring interrupt 2.
  // INT_DRDY_XL is OR'd with INT_DRDY_G
  lsm.configInt(XG_INT2, INT_DRDY_XL | INT_DRDY_G, INT_ACTIVE_LOW, INT_PUSH_PULL);
  
}

axes IMU::getAccelData()
{
    axes A;
    if(lsm.accelAvailable())
    {
        lsm.readAccel();
    }
    A.x = X;
    A.y = Y;
    A.z = Z;

    return A;
}

void IMU::fillBuffer(CB &buff)
{
    if(buff.isFull())
    {
        buff.push(getAccelData());
        return;
    }
    while(!buff.isFull())
    {
        buff.push(getAccelData());
    }
}



