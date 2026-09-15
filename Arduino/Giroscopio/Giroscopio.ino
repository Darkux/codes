#include <Wire.h>
#include <MPU6050.h>

MPU6050 Giroscopio;

int gx, gy, gz;
long Timer_Prev, Timer;
float accel_ang_x, accel_ang_y, accel_ang_z, girosc_ang_x, girosc_ang_y, girosc_ang_z;
int BPM_Sensor = 16;

void setup() {
  Wire.begin();
  Serial.begin(57600);
  Giroscopio.initialize();
  while (!Giroscopio.testConnection()) {
    Serial.println("Sensor No Conectado");
  }
  Serial.println("Sensor Conectado");
  Timer_Prev = millis();
  pinMode(BPM_Sensor, INPUT);
}

void loop() {
  Timer = millis();
  float dt = Timer - Timer_Prev; // Tiempo transcurrido desde la última iteración en milisegundos
  Timer_Prev = Timer;
  
  float ax = Giroscopio.getAccelerationX();
  float ay = Giroscopio.getAccelerationY();
  float az = Giroscopio.getAccelerationZ();
  girosc_ang_x = (Giroscopio.getRotationX() / 131.0) * dt / 1000.0 + girosc_ang_x;
  girosc_ang_y = (Giroscopio.getRotationY() / 131.0) * dt / 1000.0 + girosc_ang_y;
  girosc_ang_z = (Giroscopio.getRotationZ() / 131.0) * dt / 1000.0 + girosc_ang_z;
  accel_ang_x = atan(ax / sqrt(pow(ay, 2) + pow(az, 2))) * (180.0 / PI);
  accel_ang_y = atan(ay / sqrt(pow(ax, 2) + pow(az, 2))) * (180.0 / PI);
  accel_ang_z = atan(az / sqrt(pow(ay, 2) + pow(ax, 2))) * (180.0 / PI);

  int BPM = analogRead(BPM_Sensor);

  Serial.print("Latidos:");
  Serial.println(BPM);
  
  Serial.print("Inclinacion en X:");
  Serial.println(accel_ang_x);
  Serial.print("Inclinacion en Y:");
  Serial.println(accel_ang_y);
  Serial.print("Inclinacion en Z:");
  Serial.println(accel_ang_z);

  Serial.print("Rotacion en X:");
  Serial.println(girosc_ang_x);
  Serial.print("Rotacion en Y:");
  Serial.println(girosc_ang_y);
  Serial.print("Rotacion en Z:");
  Serial.println(girosc_ang_z);

  delay(100);
}
