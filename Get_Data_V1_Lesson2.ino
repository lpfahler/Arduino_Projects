// Sketch for Reading Data from Adafruit BNO055 Sensor
// Lesson 2 - McWhorter Lessons
// Lori Pfahler
// April 2022

// Include libaries
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define BNO055_SAMPLERATE_DELAY_MS (100)

// create sensor object
Adafruit_BNO055 myIMU = Adafruit_BNO055();

int delayTime = 2000;

void setup() {
// set baud rate higher due to amount of data that needs to pass through
  Serial.begin(115200);
  myIMU.begin();
// give a delay to get sensor stabilized
  delay(3000);
  // get temperature from IMU and put it in "temp"
  // int8_t is a very efficient data type
  // it is a signed char, 8 bytes, range of values:-128 .. 127
  int8_t temp=myIMU.getTemp();
  // some code to check on temps for debugging
  // Serial.print("Temperature: ");
  // Serial.println(temp);
  myIMU.setExtCrystalUse(true);
}

void loop() {
  // Get the 9 axes of data
  imu::Vector<3> acc = myIMU.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

  imu::Vector<3> gyro = myIMU.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

  imu::Vector<3> mag = myIMU.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

  Serial.print("Accel: ");
  Serial.print(acc.x());
  Serial.print(", ");
  Serial.print(acc.y());
  Serial.print(", ");
  Serial.print(acc.z());


  Serial.print("  Gryo: ");
  Serial.print(gyro.x());
  Serial.print(", ");
  Serial.print(gyro.y());
  Serial.print(", ");
  Serial.print(gyro.z());

  Serial.print("  Mag: ");
  Serial.print(mag.x());
  Serial.print(", ");
  Serial.print(mag.y());
  Serial.print(", ");
  Serial.println(mag.z());


  delay(BNO055_SAMPLERATE_DELAY_MS);
}
