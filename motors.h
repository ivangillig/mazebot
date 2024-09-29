#ifndef MOTORS_H
#define MOTORS_H

// Inicializar los motores
void initMotors();

// Funciones de movimiento
void moveForward(int velocidad);
void moveBackward(int velocidad);
void turnLeft(int velocidad);
void turnRight(int velocidad);
void stopMotors();
void correctDirection(long distanciaIzq);
void smoothTurnLeft(int velocidad);
void smoothTurnRight(int velocidad);

#endif
