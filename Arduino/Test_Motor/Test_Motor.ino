#include <ESP32Encoder.h>
#include <DVR8851.h>
int MotA = 12;
int MotB = 13;
const int EncoderA = 32;  
const int EncoderB = 33; 
ESP32Encoder encoder;
int dutyCyle =0;
DVR8851 Motor(MotA,MotB,0,1);
void setup() {
  Serial.begin(115200);
  encoder.attachHalfQuad(EncoderA,EncoderB);
  pinMode(EncoderA,INPUT_PULLDOWN);
  pinMode(EncoderB,INPUT_PULLDOWN);
  encoder.setCount(0);
  Motor.forward();
  //Motor.backward();
}

void loop() {
  int estadoA = digitalRead(EncoderA);
  int estadoB = digitalRead(EncoderB);
  int count = encoder.getCount();
  Serial.print("Estado de entrada A: ");
  Serial.println(digitalRead(EncoderA));
  Serial.print("Estado de entrada B: ");
  Serial.println(digitalRead(EncoderB));
  Serial.print("Count: ");
}
