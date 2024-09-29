#include "sensors.h"
#include "config.h" // Asegúrate de tener los pines definidos aquí
#include <Arduino.h>

void initSensors() {
  // Configurar los pines de los sensores ultrasónicos frontales y laterales
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);

  pinMode(trigPinLeft, OUTPUT);
  pinMode(echoPinLeft, INPUT);

  pinMode(trigPinRight, OUTPUT);
  pinMode(echoPinRight, INPUT);
}

long getDistance(int trigPin, int echoPin) {
  // Enviar un pulso de 10 µs al pin trig
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medir el tiempo que tarda el pulso en volver al pin echo
  long duration = pulseIn(echoPin, HIGH);

  // Calcular la distancia (en cm)
  long distance = duration * 0.034 / 2;

  return distance;
}
