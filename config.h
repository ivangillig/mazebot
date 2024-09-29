#ifndef CONFIG_H
#define CONFIG_H

// Definir los pines para los motores
#define motorIzqPin1 10
#define motorIzqPin2 9

#define motorDerPin1 5
#define motorDerPin2 11

// Definir los pines para los 5 sensores ultrasónicos

// Sensor frontal
#define trigPinFront 3
#define echoPinFront 2

// Sensor derecho
#define trigPinRight 4
#define echoPinRight 12

// Sensor izquierdo
#define trigPinLeft 6
#define echoPinLeft 7

// Sensor trasero
// #define trigPinBack 8
// #define echoPinBack 12


// Umbral de distancia para considerar "libre" o "bloqueado"
const int umbral = 15;

#endif
