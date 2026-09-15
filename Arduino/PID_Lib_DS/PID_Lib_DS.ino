#include "PID_Lib_DS.h"

// Definir objetos PID y configurar constantes
PID myPID;
float Kp = 1.0; // Ejemplo de constante proporcional
float Ki = 0.1; // Ejemplo de constante integral
float Kd = 0.05; // Ejemplo de constante derivativa

// Definir la función de callback para obtener el valor medido
float measuredValue; // Variable para almacenar el valor medido

void setup() {
  // Inicializar la comunicación serial
  Serial.begin(9600);

  // Configurar las constantes del PID
  myPID.SetPID(Ki, Kd, Kp);

  // Establecer la entrada del PID (puntero al valor medido)
  myPID.SetInput(&measuredValue);
}

void loop() {
  // Obtener el valor medido (por ejemplo, de un sensor)
  measuredValue = analogRead(A0); // Ejemplo: leyendo un valor analógico de A0

  // Configurar el valor objetivo para el controlador PID
  float targetValue = 500; // Ejemplo: valor objetivo deseado

  // Establecer el valor objetivo del PID
  myPID.GetTarget(targetValue);

  // Calcular y obtener la salida del PID
  float output = myPID.Compute();

  // Utilizar la salida del PID para controlar el sistema (por ejemplo, un actuador)
  // Aquí puedes poner tu código para controlar el sistema con la salida del PID

  // Imprimir el valor de salida del PID
  Serial.println(output);

  // Esperar un tiempo antes de la siguiente iteración
  delay(100);
}
