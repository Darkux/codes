float vref = 3.3;          // Voltaje real del ESP32
float r1 = 16000000.0;      // 9 MΩ
float r2 = 100000.0;       // 100 kΩ

const int adcPin = 34;     // GPIO ADC

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);        // 0–4095
  analogSetAttenuation(ADC_11db);  // Hasta ~3.3 V

  Serial.println("--------------------");
  Serial.println("DC VOLTMETER - ESP32");
  Serial.print("Maximum Voltage: ");
  Serial.print(vref / (r2 / (r1 + r2)));
  Serial.println(" V");
  Serial.println("--------------------");
  delay(2000);
}

void loop() {

  // ---- PROMEDIO DE 1 SEGUNDO ----
  unsigned long t0 = millis();
  long suma = 0;
  int muestras = 0;

  while (millis() - t0 < 1000) {
    suma += analogRead(adcPin);
    muestras++;
    delay(5);   // ~200 muestras por segundo
  }

  float adc_prom = (float)suma / muestras;

  // ---- CONVERSIÓN A VOLTAJE ----
  float v_adc = (adc_prom * vref) / 4095.0;
  float v_real = v_adc / (r2 / (r1 + r2));

  Serial.print("Muestras: ");
  Serial.print(muestras);
  Serial.print(" | ADC prom: ");
  Serial.print(adc_prom, 1);
  Serial.print(" | V: ");
  Serial.println(v_real, 2);
}
