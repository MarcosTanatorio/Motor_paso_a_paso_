#include <AccelStepper.h>

// Definir los pines del motor
#define motorPin1 8
#define motorPin2 9
#define motorPin3 10
#define motorPin4 11

// Definir el pin del pulsador
#define buttonPin 2

// Crear un objeto AccelStepper
AccelStepper stepper(AccelStepper::FULL4WIRE, motorPin1, motorPin2, motorPin3, motorPin4);

// Definir las posiciones predefinidas
const int positions[] = {0, 100, 500, 1000, 1500};  // Incluimos la posición 0 para la vuelta completa
const int numPositions = sizeof(positions) / sizeof(positions[0]);

int currentPosition = 0;

void setup() {
  // Configurar el pin del pulsador como entrada
  pinMode(buttonPin, INPUT_PULLUP);

  // Establecer la velocidad máxima y la aceleración para el motor
  stepper.setMaxSpeed(1000.0);
  stepper.setAcceleration(500.0);
}

void loop() {
  // Verificar el pulsador
  if (digitalRead(buttonPin) == LOW) {
    // Incrementar la posición actual y volver a la posición 0 si se alcanza el final
    currentPosition = (currentPosition + 1) % numPositions;

    // Mover el motor a la nueva posición
    moveToPosition(positions[currentPosition]);

    delay(500);  // Pequeño retardo para evitar múltiples lecturas por un solo botón
  }
}

void moveToPosition(int targetPosition) {
  // Mover el motor a la posición objetivo
  stepper.moveTo(targetPosition);

  // Realizar el movimiento
  while (stepper.distanceToGo() != 0) {
    stepper.run();

    // Verificar si el motor ha completado una vuelta
    if (stepper.currentPosition() == 0 && targetPosition != 0) {
      break;  // Salir del bucle si ha completado una vuelta y no está volviendo a la posición 0
    }
  }

  // Detener el motor al llegar a la posición objetivo
  stepper.stop();
  stepper.runToPosition();
}
