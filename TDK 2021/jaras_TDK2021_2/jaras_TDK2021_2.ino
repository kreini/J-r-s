/*
Advanced_I2C.ino
Brian R Taylor
brian.taylor@bolderflight.com

Copyright (c) 2017 Bolder Flight Systems

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the "Software"), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, 
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "MPU9250.h"

// an MPU9250 object with the MPU-9250 sensor on I2C bus 0 with address 0x68
MPU9250 IMU1(Wire,0x68);
MPU9250 IMU2(Wire,0x69);
int status1;
int status2;
int t = 1;
void setup() {
  // serial to display data
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  delay(100);
  digitalWrite(13, HIGH);
  delay(100);

  // start communication with IMU 
  status1 = IMU1.begin();
  if (status1 < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status1);
    while(1) {}
  }
  status2 = IMU2.begin();
  if (status2 < 0) {
    Serial.println("IMU initialization unsuccessful");
    Serial.println("Check IMU wiring or try cycling power");
    Serial.print("Status: ");
    Serial.println(status2);
    while(1) {}
  }
  IMU1.setSrd(0);
  IMU2.setSrd(0);
  IMU1.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  IMU1.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  IMU1.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  IMU2.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  IMU2.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  IMU2.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
}



void loop() {
  // read the sensor
  
  Serial.print(millis());
  Serial.print("\t");
  Serial.print("11\t");
  IMU1.readSensor();
  Serial.print(IMU1.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU1.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU1.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU1.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU1.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU1.getGyroZ_rads(),6);
  Serial.print("\n");

  //delay(t);
  Serial.print(millis());
  Serial.print("\t");
  Serial.print("10\t");
  IMU2.readSensor();
  Serial.print(IMU2.getAccelX_mss(),6);
  Serial.print("\t");
  Serial.print(IMU2.getAccelY_mss(),6);
  Serial.print("\t");
  Serial.print(IMU2.getAccelZ_mss(),6);
  Serial.print("\t");
  Serial.print(IMU2.getGyroX_rads(),6);
  Serial.print("\t");
  Serial.print(IMU2.getGyroY_rads(),6);
  Serial.print("\t");
  Serial.print(IMU2.getGyroZ_rads(),6);
  Serial.print("\n");
}
