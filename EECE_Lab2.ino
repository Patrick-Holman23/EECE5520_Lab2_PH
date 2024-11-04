// MPU-6050 Short Example Sketch
//www.elegoo.com
//2016.12.9

#include<Wire.h>

const int X_pin = 1; // analog pin connected to X output
const int Y_pin = 0; // analog pin connected to Y output
const int buzzer = 3; // digital pin connected to buzzer

int incomingByte = 0;

const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Serial.begin(9600);

  pinMode(buzzer, OUTPUT);

}
void loop(){

  // Joystick Control Signals
  if (analogRead(X_pin) > 768) {
    Serial.print('d');
  }
  if (analogRead(X_pin) < 256) {
    Serial.print('a');
  }
  if (analogRead(Y_pin) > 768) {
    Serial.print('w');
  }
  if (analogRead(Y_pin) < 256) {
    Serial.print('s');
  }

  // MPU-6050 Control Signals
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);  // request a total of 14 registers
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
  Tmp=Wire.read()<<8|Wire.read();  // 0x41 (TEMP_OUT_H) & 0x42 (TEMP_OUT_L)
  GyX=Wire.read()<<8|Wire.read();  // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
  GyY=Wire.read()<<8|Wire.read();  // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
  GyZ=Wire.read()<<8|Wire.read();  // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)

  //Serial.print(" | AcX = "); Serial.println(AcX);
  //Serial.print(" | AcY = "); Serial.println(AcY);
  //Serial.print(" | AcZ = "); Serial.println(AcZ);
  //Serial.println("\n");

  if (GyX < -20000){
    Serial.print("d");
  }
  if (GyX > 20000){
    Serial.print("a");
  }
  if (GyY < -20000){
    Serial.print("s");
  }
  if (GyY > 20000){
    Serial.print("w");
  }  

  if (Serial.available() > 0) {
    // Read incoming byte when food eaten
    incomingByte = Serial.read();
    Serial.println(incomingByte);

    if(incomingByte == 'F') {
      // Turn on buzzer
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
    }
  }

  if (AcY < -14000){
    Serial.print("c");
  }
}
