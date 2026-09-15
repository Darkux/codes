#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();  // SDA = 21, SCL = 22 por defecto
  mpu.initialize();
  
  if (mpu.testConnection()) {
    Serial.println("MPU6050 conectado correctamente!");
  } else {
    Serial.println("Error al conectar con MPU6050!");
  }
}
void loop() {
  int16_t raw_ax = mpu.getAccelerationX();
  Serial.println(raw_ax);  // Cada muestra en una línea
  //int16_t raw_ay = mpu.getAccelerationY();
  //Serial.println(raw_ay);  // Cada muestra en una línea
  //int16_t raw_az = mpu.getAccelerationZ();
  //Serial.println(raw_az);  // Cada muestra en una línea
  delay(5);  // Ajusta la frecuencia de muestreo (~200Hz)
}
