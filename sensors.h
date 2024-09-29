#ifndef SENSORS_H
#define SENSORS_H

// Función para inicializar los sensores
void initSensors();

// Leer la distancia de un sensor ultrasónico
long getDistance(int trigPin, int echoPin);

#endif
