    #include <I2Cdev.h>
    #include <MPU6050.h>

    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
    #endif

    MPU6050 mpu_0(0x68);
    MPU6050 mpu_1(0x68);
    MPU6050 mpu_2(0x68);

    int16_t ax_0, ay_0, az_0, ax_1, ay_1, az_1, ax_2, ay_2, az_2;
    int16_t gx_0, gy_0, gz_0, gx_1, gy_1, gz_1, gx_2, gy_2, gz_2;

    #define OUTPUT_READABLE_ACCELGYRO


    #define LED_PIN 13
    bool blinkState = false;

    int s0 = 9;
    int s1 = 10;
    int s2 = 11;

    int SIG_pin = 0;

    const int MPU=0x68;

    unsigned long time;





void setup() {



  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 

  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
  
  Serial.begin(115200);

  
  // ================= MPU: 0 =================
  
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  delay(5);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(15);
  mpu_0.initialize();
  //Serial.println("Eszkoz teszt (0) ...");
  //Serial.println(mpu_0.testConnection() ? "  MPU9250 (0) csatlakozas sikeres" :  "  MPU9250 (0) csatlakozas sikertelen");
  delay(5);

  
  // ================= MPU: 1 =================
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  delay(5);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(15);
  mpu_1.initialize();
  //Serial.println("Eszkoz teszt (1) ...");
  //Serial.println(mpu_1.testConnection() ? "  MPU9250 (1) csatlakozas sikeres" :  "  MPU9250 (1) csatlakozas sikertelen");
  delay(5);

  
  // ================= MPU: 2 =================
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  delay(5);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  delay(15);
  mpu_2.initialize();
  //Serial.println("Eszkoz teszt (2) ...");
  //Serial.println(mpu_2.testConnection() ? "  MPU9250 (3) csatlakozas sikeres" :  "  MPU9250 (2) csatlakozas sikertelen");
  delay(5);
  
  
  
  pinMode(LED_PIN, OUTPUT);
  }






void loop() {


  time = micros();


  // ================= MPU: 0 =================
  
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  delay(1);
  mpu_0.getMotion6(&ax_0, &ay_0, &az_0, &gx_0, &gy_0, &gz_0);
  #ifdef OUTPUT_READABLE_ACCELGYRO
      Serial.print(time); Serial.print("\t");
      Serial.print("0\t");
      Serial.print(ax_0); Serial.print("\t");
      Serial.print(ay_0); Serial.print("\t");
      Serial.print(az_0); Serial.print("\t\n");
      //Serial.print(gx_0); Serial.print("\t");
      //Serial.print(gy_0); Serial.print("\t");
      //Serial.println(gz_0);
    #endif
    delay(1);

  
  // ================= MPU: 1 =================
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);
  digitalWrite(s2, HIGH);
  delay(1);
  mpu_1.getMotion6(&ax_1, &ay_1, &az_1, &gx_1, &gy_1, &gz_1);
  #ifdef OUTPUT_READABLE_ACCELGYRO
      Serial.print(time); Serial.print("\t");
      Serial.print("1\t");
      Serial.print(ax_1); Serial.print("\t");
      Serial.print(ay_1); Serial.print("\t");
      Serial.print(az_1); Serial.print("\t\n");
      //Serial.print(gx_1); Serial.print("\t");
      //Serial.print(gy_1); Serial.print("\t");
      //Serial.println(gz_1);
  #endif
  delay(1);

  
  // ================= MPU: 2 =================
  
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, LOW);
  delay(1);
  mpu_2.getMotion6(&ax_2, &ay_2, &az_2, &gx_2, &gy_2, &gz_2);
  #ifdef OUTPUT_READABLE_ACCELGYRO
      Serial.print(time); Serial.print("\t");
      Serial.print("2\t");
      Serial.print(ax_2); Serial.print("\t");
      Serial.print(ay_2); Serial.print("\t");
      Serial.print(az_2); Serial.print("\t\n");
      //Serial.print(gx_2); Serial.print("\t");
      //Serial.print(gy_2); Serial.print("\t");
      //Serial.println(gz_2);
   #endif
   delay(1);


    blinkState = !blinkState;
    digitalWrite(LED_PIN, blinkState);
   }
