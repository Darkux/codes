
const int PWM[6] ={7,6,5,4,3,2};
const int InA[6]={12,10,8,14,17,19};
const int InB[6]={13,11,9,15,16,18}; 

int velocidades[6] = {0};
int direcciones[6] = {0};

float distA, distB, distC, distD;

const int PWM_TEST = 255;      // amplitud PWM
const int T_ON  = 1000;        // ms excitación
const int T_OFF = 3000;        // ms reposo


void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 6; i++) {
    pinMode(PWM[i], OUTPUT);
    pinMode(InA[i], OUTPUT);
    pinMode(InB[i], OUTPUT);
  }
  
}


int motor_actual = -1;
int estado = 0;
unsigned long t0 = 0;

void loop()
{
  // ===============================
  // 1) Leer motor desde MATLAB
  // ===============================
  if (Serial.available() > 0)
  {
    int m = Serial.parseInt();
    int b = Serial.parseInt(); 
    if (m >= 0 && m < 6)
    {
      motor_actual = m;
      estado = 0;
      Serial.print("Motor seleccionado: ");
      Serial.println(motor_actual);
    }
  }

  if (motor_actual < 0) return;

  // ===============================
  // 2) Máquina de estados
  // ===============================
  switch (estado)
  {
    case 0:  // BLOQUEO INICIAL
    delay(1000);
      for (int i = 0; i < 6; i++) {
        digitalWrite(InA[i], HIGH);
        digitalWrite(InB[i], HIGH);
        analogWrite(PWM[i], 0);
      }
      t0 = millis();
      estado = 1;
      break;

    case 1:  // ESPERA
      if (millis() - t0 > 300) {
        t0 = millis();
        estado = 2;
      }
      break;

    case 2:  // +PWM
      digitalWrite(InA[motor_actual], HIGH);
      digitalWrite(InB[motor_actual], LOW);
      analogWrite(PWM[motor_actual], PWM_TEST);
      t0 = millis();
      estado = 3;
      break;

    case 3:  // BLOQUEO POST +PWM
      if (millis() - t0 > T_ON) {
        analogWrite(PWM[motor_actual], 0);
        digitalWrite(InA[motor_actual], HIGH);
        digitalWrite(InB[motor_actual], HIGH);
        t0 = millis();
        estado = 4;
      }
      break;

    case 4:  // ESPERA
      if (millis() - t0 > 300) {
        t0 = millis();
        estado = 5;
      }
      break;

    case 5:  // -PWM
      digitalWrite(InA[motor_actual], LOW);
      digitalWrite(InB[motor_actual], HIGH);
      analogWrite(PWM[motor_actual], PWM_TEST);
      t0 = millis();
      estado = 6;
      break;

    case 6:  // BLOQUEO FINAL
      if (millis() - t0 > T_ON) {
        analogWrite(PWM[motor_actual], 0);
        digitalWrite(InA[motor_actual], HIGH);
        digitalWrite(InB[motor_actual], HIGH);
        t0 = millis();
        estado = 7;
      }
      break;

    case 7:  // FIN
      if (millis() - t0 > T_OFF) {
        Serial.println("FIN");
        motor_actual = -1;
        estado = -1;
      }
      break;
  }
}



