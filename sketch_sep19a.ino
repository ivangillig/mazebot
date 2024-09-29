// Main

#include "motors.h"
#include "sensors.h"
#include "config.h"

// Variables globales
unsigned long previousSensorMillis = 0;
const long sensorInterval = 50; // Intervalo entre lecturas

void setup() {
  // Inicializar componentes
  initMotors();
  initSensors();
  
  // Configurar el pin del LED (usaremos el LED en el pin 13)
  pinMode(13, OUTPUT);

  // Iniciar el monitor serie
  Serial.begin(9600);
  Serial.println("Arduino Nano está funcionando correctamente");

  // Inicialmente, parar los motores
  stopMotors();
}

void loop() {
  unsigned long currentMillis = millis();


  // Leer las distancias de los sensores
  long distanciaFront = getDistance(trigPinFront, echoPinFront);
  delay(50);
  long distanciaIzq = getDistance(trigPinLeft, echoPinLeft);
  delay(50);
  long distanciaDer = getDistance(trigPinRight, echoPinRight);

  // Mostrar las distancias en el monitor serie
  imprimirDistancias(distanciaFront, distanciaIzq, distanciaDer);

  // Lógica de navegación siguiendo la pared izquierda
  if (distanciaIzq > umbral && distanciaFront > umbral && distanciaDer > umbral) {
    manejarEspacioEnTodasDirecciones();
  } else if (distanciaIzq > umbral) {
    manejarEspacioIzquierda();
  } else if (distanciaFront > umbral) {
    manejarEspacioFrente(distanciaIzq);
  } else if (distanciaDer > umbral) {
    manejarEspacioDerecha();
  } else {
    manejarCallejonSinSalida();
  }

  delay(200); // Pequeña pausa entre lecturas
}

// Función para imprimir las distancias en el monitor serie
void imprimirDistancias(long front, long izq, long der) {
  Serial.print("Front: ");
  Serial.print(front);
  Serial.print(" cm, Izq: ");
  Serial.print(izq);
  Serial.print(" cm, Der: ");
  Serial.print(der);
  Serial.println(" cm");
}

// Función para manejar cuando hay espacio en todas las direcciones
void manejarEspacioEnTodasDirecciones() {
  Serial.println("Espacio en todas las direcciones. Parece que salimos del laberinto.");
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
  stopMotors();
}

// Función para manejar cuando hay espacio a la izquierda
void manejarEspacioIzquierda() {
  Serial.println("Espacio a la izquierda. Girando a la izquierda y avanzando.");
  stopMotors();
  delay(200);
  turnLeft(150);
  delay(600); // Ajusta este tiempo para girar 90 grados
  stopMotors();
  delay(200);
  moveForward(150);
  delay(500); // Avanzar un poco después de girar
}

// Función para manejar cuando hay espacio al frente
void manejarEspacioFrente(long distanciaIzq) {
  Serial.println("Espacio al frente. Avanzando y corrigiendo dirección.");
  correctDirection(distanciaIzq);
}

// Función para manejar cuando hay espacio a la derecha
void manejarEspacioDerecha() {
  Serial.println("Espacio a la derecha. Girando a la derecha y avanzando.");
  stopMotors();
  delay(200);
  turnRight(150);
  delay(600); // Ajusta este tiempo para girar 90 grados
  stopMotors();
  delay(200);
  moveForward(150);
  delay(500); // Avanzar un poco después de girar
}

// Función para manejar cuando no hay espacio en ninguna dirección
void manejarCallejonSinSalida() {
  Serial.println("Callejón sin salida. Girando 180 grados.");
  stopMotors();
  delay(200);
  turnRight(150);
  delay(1200); // Ajusta este tiempo para girar 180 grados
  stopMotors();
  delay(200);
}
