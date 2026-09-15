// Define los pines a los que están conectados los botones
const int botonPin1 = 13;
const int botonPin2 = 27;
const int botonPin3 = 33;
const int botonPin4 = 34;

#define LED1 23  // Define el pin para el LED 1
#define LED2 22  // Define el pin para el LED 2
#define LED3 21 // Define el pin para el LED 3
#define LED4 19 // Define el pin para el LED 4

void setup() {
  // Inicializa los pines de los botones como entradas
  pinMode(botonPin1, INPUT_PULLDOWN);
  pinMode(botonPin2, INPUT_PULLDOWN);
  pinMode(botonPin3, INPUT_PULLDOWN);
  pinMode(botonPin4, INPUT_PULLDOWN);
  pinMode(LED1, OUTPUT);  // Configura el pin del LED 1 como salida
  pinMode(LED2, OUTPUT);  // Configura el pin del LED 2 como salida
  pinMode(LED3, OUTPUT);  // Configura el pin del LED 3 como salida
  pinMode(LED4, OUTPUT);  // Configura el pin del LED 4 como salida
  Serial.begin(115200);
}

void loop() {
  // Lee el estado de los botones
  int estadoBoton1 = digitalRead(botonPin1);
  int estadoBoton2 = digitalRead(botonPin2);
  int estadoBoton3 = digitalRead(botonPin3);
  int estadoBoton4 = digitalRead(botonPin4);

  // Verifica el estado de cada botón y toma acciones
  if (estadoBoton1 == HIGH) {
    Serial.println("Boton 1 presionado");
    digitalWrite(LED1, HIGH);  // Enciende el LED 1
     delay(1000);
  }
  else if (estadoBoton2 == HIGH) {
    Serial.println("Boton 2 presionado");
    digitalWrite(LED2, HIGH);  // Enciende el LED 2
    delay(1000);
  }
  else if (estadoBoton3 == HIGH) {
    Serial.println("Boton 3 presionado");
    digitalWrite(LED3, HIGH);  // Enciende el LED 3
    delay(1000);
  }
  else if (estadoBoton4 == HIGH) {
    Serial.println("Boton 4 presionado");
    digitalWrite(LED4, HIGH);  // Enciende el LED 4
    delay(1000);
  }
  else
  {
  digitalWrite(LED1, LOW);  // Apaga el LED 1
  digitalWrite(LED2, LOW);  // Apaga el LED 2
  digitalWrite(LED3, LOW);  // Apaga el LED 3
  digitalWrite(LED4, LOW);  // Apaga el LED 4
  }
  delay(100); // Puedes ajustar el tiempo de espera según tus necesidades
}