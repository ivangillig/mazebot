#include "motors.h"
#include "config.h"
#include <Arduino.h>

// Inicializa los motores configurando los pines como salidas
void initMotors() {
  pinMode(motorIzqPin1, OUTPUT);
  pinMode(motorIzqPin2, OUTPUT);
  pinMode(motorDerPin1, OUTPUT);
  pinMode(motorDerPin2, OUTPUT);

  // Detiene los motores inicialmente
  stopMotors();
}

// Controla el motor izquierdo
void setMotorIzq(int velocidad) {
  if (velocidad > 0) {
    // Avanzar
    analogWrite(motorIzqPin1, velocidad);
    digitalWrite(motorIzqPin2, LOW);
  } else if (velocidad < 0) {
    // Retroceder
    digitalWrite(motorIzqPin1, LOW);
    analogWrite(motorIzqPin2, -velocidad); // Convierte velocidad a positiva
  } else {
    // Detener
    digitalWrite(motorIzqPin1, LOW);
    digitalWrite(motorIzqPin2, LOW);
  }
}

// Controla el motor derecho
void setMotorDer(int velocidad) {
  if (velocidad > 0) {
    // Avanzar
    analogWrite(motorDerPin1, velocidad);
    digitalWrite(motorDerPin2, LOW);
  } else if (velocidad < 0) {
    // Retroceder
    digitalWrite(motorDerPin1, LOW);
    analogWrite(motorDerPin2, -velocidad); // Convierte velocidad a positiva
  } else {
    // Detener
    digitalWrite(motorDerPin1, LOW);
    digitalWrite(motorDerPin2, LOW);
  }
}

// Avanza hacia adelante a una velocidad específica
void moveForward(int velocidad) {
  setMotorIzq(velocidad);
  setMotorDer(velocidad);
}

// Retrocede a una velocidad específica
void moveBackward(int velocidad) {
  setMotorIzq(-velocidad);
  setMotorDer(-velocidad);
}

// Gira a la izquierda sobre su propio eje
void turnLeft(int velocidad) {
  setMotorIzq(-velocidad); // Motor izquierdo retrocede
  setMotorDer(velocidad);  // Motor derecho avanza
}

// Gira a la derecha sobre su propio eje
void turnRight(int velocidad) {
  setMotorIzq(velocidad);   // Motor izquierdo avanza
  setMotorDer(-velocidad);  // Motor derecho retrocede
}

// Detiene ambos motores
void stopMotors() {
  setMotorIzq(0);
  setMotorDer(0);
}

// Corrección de dirección basada en las distancias de los sensores
void correctDirection(long distanciaIzq) {
  const int distanciaDeseada = 7; // Distancia deseada de la pared en cm
  int error = distanciaDeseada - distanciaIzq; // Error respecto a la pared izquierda

  int velocidadBase = 150;
  int factorCorreccion = 2; // Ajusta este valor según sea necesario
  int diferenciaMaxima = 30; // Diferencia máxima permitida entre las velocidades

  int ajuste = error * factorCorreccion;

  // Limitar el ajuste para que no exceda la diferencia máxima
  ajuste = constrain(ajuste, -diferenciaMaxima, diferenciaMaxima);

  int velocidadIzq = velocidadBase + ajuste;
  int velocidadDer = velocidadBase - ajuste;

  // Limita los valores de velocidad
  velocidadIzq = constrain(velocidadIzq, 0, 255);
  velocidadDer = constrain(velocidadDer, 0, 255);

  // Imprimir valores de depuración
  Serial.print("DistanciaIzq: ");
  Serial.print(distanciaIzq);
  Serial.print(" cm, Error: ");
  Serial.print(error);
  Serial.print(", Ajuste: ");
  Serial.print(ajuste);
  Serial.print(", velocidadIzq: ");
  Serial.print(velocidadIzq);
  Serial.print(", velocidadDer: ");
  Serial.println(velocidadDer);

  setMotorIzq(velocidadIzq);
  setMotorDer(velocidadDer);
}



// Giro suave a la izquierda
void smoothTurnLeft(int velocidad) {
  setMotorIzq(velocidad - 50);  // Motor izquierdo va más lento
  setMotorDer(velocidad);       // Motor derecho a velocidad normal
}

// Giro suave a la derecha
void smoothTurnRight(int velocidad) {
  setMotorIzq(velocidad);       // Motor izquierdo a velocidad normal
  setMotorDer(velocidad - 50);  // Motor derecho va más lento
}
