#define ADC_PIN 34        // Pin ADC del ESP32
#define ADC_RES 4095.0    // Resolución ADC 12 bits
#define VREF 3.3          // Referencia ADC ESP32
#define SENSIBILITY 0.066 // V/A (66 mV/A)

float zeroCurrentVoltage = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);

  Serial.println("Calibrando cero...");
  delay(2000);

  // Calibración de cero
  float sum = 0;
  for (int i = 0; i < 1000; i++) {
    sum += analogRead(ADC_PIN);
    delay(5);
  }

  float adcZero = sum / 1000.0;
  zeroCurrentVoltage = adcZero * (VREF / ADC_RES);

  Serial.print("Voltaje cero: ");
  Serial.println(zeroCurrentVoltage, 3);
}

void loop() {
  unsigned long startTime = millis();
  float sumADC = 0;
  int samples = 0;

  // Tomar muestras durante 1 segundo
  while (millis() - startTime < 1000) {
    sumADC += analogRead(ADC_PIN);
    samples++;
    delay(5);  // pequeño delay para estabilidad
  }

  float adcAvg = sumADC / samples;
  float voltage = adcAvg * (VREF / ADC_RES);
  float current = (voltage - zeroCurrentVoltage) / SENSIBILITY;

  Serial.print("Muestras: ");
  Serial.print(samples);
  Serial.print(" | ADC prom: ");
  Serial.print(adcAvg, 1);
  Serial.print(" | Voltaje prom: ");
  Serial.print(voltage, 3);
  Serial.print(" V | Corriente prom: ");
  Serial.print(current, 2);
  Serial.println(" A");
}

