float Sensibilidad=0.065; //sensibilidad en Voltios/Amperio para sensor de 5A
int ACS = 25;
void setup() {
  
  Serial.begin(9600);
}

void loop() {
  
  float I=get_corriente(1000);//obtenemos la corriente promedio de 500 muestras 
  Serial.print("Corriente: ");
  Serial.println(I,3); 
  delay(100);     
}

float get_corriente(int n_muestras)
{
  float voltajeSensor;
  float corriente=0;
  for(int i=0;i<n_muestras;i++)
  {
    voltajeSensor = analogRead(ACS) * (3.333/ 4096.0);////lectura del sensor
    corriente=corriente+(voltajeSensor-2.26)/Sensibilidad; //Ecuación  para obtener la corriente
  }
  corriente=corriente/n_muestras;
  return(corriente);
}