#define ENCA1 2
#define ENCB1 3
#define IN1 5
#define IN2 4
#define PWM1 6

const int s0 = 12;
const int s1 = 13;
const int s2 = 9;
const int s3 = 10;
const int out = 8;
int rojo = 0;
int verde = 0;
int azul = 0;

volatile float PosFinal = 0, AnguloF = 0;
String Motor, Angulo, input;
float angulo1, angulo2;
float target = 0, target2 = 0;
volatile float pos = 0, pos2 = 0;
long prevT = 0, prevT2 = 0;
float eprev = 0, eprev2 = 0;
float eintegral = 0, eintegral2 = 0;

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(10, 11); // RX, TX

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  
  pinMode(ENCA1, INPUT_PULLUP);
  pinMode(ENCB1, INPUT_PULLUP);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(PWM1, OUTPUT);
  
  Serial.println("LABEL,color rojo, color verde, color azul, color final");
  attachInterrupt(digitalPinToInterrupt(ENCA1), readEncoder1, RISING);
  target = 0;

  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);
}

void loop() {
  if (Serial.available() > 1) {
    String input = Serial.readString();
    Motor = input.substring(0, 1);
    Angulo = input.substring(2);
  }

  color();
  Serial.print("   ");
  Serial.print(rojo, DEC);
  Serial.print("   ");
  Serial.print(verde, DEC);
  Serial.print("   ");
  Serial.print(azul, DEC);

  if (rojo < azul && verde > azul && rojo < 35) {
    Serial.println("   Rojo");
    BTSerial.println("Ficha roja detectada");
  } else if (azul < rojo && azul < verde && verde < rojo) {
    Serial.println("   Azul");
    BTSerial.println("Ficha azul detectada");
  } else if (rojo > verde && azul > verde) {
    Serial.println("   no hay nada");
  } else {
    Serial.println("  ");
  }

  if (Motor == "A") {
    angulo1 = Angulo.toFloat();
    target = ((angulo1) / (360.0) * (6250 / 10));
    float kp = 1.18;
    float ki = 0.00067;
    float kd = 0.12753;

    long currT = micros();
    long et = currT - prevT;
    float deltaT = ((float)(currT - prevT)) / 1.0e6;
    prevT = currT;
    float e = pos - target;
    float dedt = (e - eprev) / (deltaT);
    eintegral = eintegral + e * deltaT;
    float u = kp * e + kd * dedt + ki * eintegral;
    float pwr = fabs(u);

    if (pwr > 255) {
      pwr = 255;
    }
    int dir = 1;
    if (u < 0) {
      dir = -1;
    }
    setMotor1(dir, pwr, PWM1, IN1, IN2);
    eprev = e;

    Serial.print(angulo1);
    Serial.print(" ");
    Serial.print((target * 360) / (6250 / 10));
    Serial.print(" ");
    Serial.print((pos * 360) / (6250 / 10));
    Serial.print(" ");
  } else if (Motor == "B") {
    if (rojo < azul && verde > azul && rojo < 35) {
      target = ((300) / (360.0) * (625));
      float kp = 1.18;
      float ki = 0.00067;
      float kd = 0.12753;

      long currT = micros();
      long et = currT - prevT;
      float deltaT = ((float)(currT - prevT)) / 1.0e6;
      prevT = currT;
      float e = pos - target;
      float dedt = (e - eprev) / (deltaT);
      eintegral = eintegral + e * deltaT;
      float u = kp * e + kd * dedt + ki * eintegral;
      float pwr = fabs(u);

      if (pwr > 255) {
        pwr = 255;
      }
      int dir = 1;
      if (u < 0) {
        dir = -1;
      }
      setMotor1(dir, pwr, PWM1, IN1, IN2);
      eprev = e;
    } else if (azul < rojo && azul < verde && verde < rojo) {
      target = ((-330) / (360.0) * (625));
      float kp = 1.18;
      float ki = 0.00067;
      float kd = 0.12753;

      long currT = micros();
      long et = currT - prevT;
      float deltaT = ((float)(currT - prevT)) / 1.0e6;
      prevT = currT;
      float e = pos - target;
      float dedt = (e - eprev) / (deltaT);
      eintegral = eintegral + e * deltaT;
      float u = kp * e + kd * dedt + ki * eintegral;
      float pwr = fabs(u);

      if (pwr > 255) {
        pwr = 255;
      }
      int dir = 1;
      if (u < 0) {
        dir = -1;
      }
      setMotor1(dir, pwr, PWM1, IN1, IN2);
      eprev = e;
    } else if (rojo > verde && azul > verde) {
      target = ((0) / (360.0) * (6250));
      float kp = 1.18;
      float ki = 0.00067;
      float kd = 0.12753;

      long currT = micros();
      long et = currT - prevT;
      float deltaT = ((float)(currT - prevT)) / 1.0e6;
      prevT = currT;
      float e = pos - target;
      float dedt = (e - eprev) / (deltaT);
      eintegral = eintegral + e * deltaT;
      float u = kp * e + kd * dedt + ki * eintegral;
      float pwr = fabs(u);

      if (pwr > 255) {
        pwr = 255;
      }
      int dir = 1;
      if (u < 0) {
        dir = -1;
      }
      setMotor1(dir, pwr, PWM1, IN1, IN2);
      eprev = e;
    } else {
      Serial.println("  ");
    }
  }
  delay(100);
}

void setMotor1(int dir, int pwmVal, int pwm, int in1, int in2) {
  analogWrite(pwm, pwmVal);
  if (dir == 1) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  } else if (dir == -1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } else {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
  }
}

void readEncoder1() {
  int b = digitalRead(ENCB1);
  if (b > 0) {
    pos++;
  } else {
    pos--;
  }
}

void color() {
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  rojo = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite(s3, HIGH);
  azul = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  digitalWrite
