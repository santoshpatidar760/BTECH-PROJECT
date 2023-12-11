#include <Stepper.h>

#define STEPS_PER_REVOLUTION 200 // Replace with the actual steps per revolution of your stepper motor
#define dirPin 8
#define stepPin 3
#define proximityPin 2 // Replace with the pin number connected to the proximity sensor

bool previousStatus = LOW; // Variable to store the previous proximity sensor status

Stepper stepper(STEPS_PER_REVOLUTION, dirPin, stepPin);

void setup() {
  pinMode(proximityPin, INPUT); // Set proximityPin as input
  digitalWrite(dirPin, HIGH); // Set the spinning direction CW/CCW
  Serial.begin(9600);

  // Delay after initializing the motor driver
  delay(50); // Adjust the delay time as needed

  stepper.setSpeed(400); // Set the speed of the stepper motor (in steps per second)
}

void loop() {
  int proximityStatus = digitalRead(proximityPin);

  // Debounce the proximity sensor
  delay(10);  // Adjust the delay time as needed
  proximityStatus = digitalRead(proximityPin);

  if (proximityStatus == HIGH && previousStatus == LOW) {
    stepper.step(1.5 * STEPS_PER_REVOLUTION); // Move the stepper motor one full revolution
    delay(10); // Delay to allow the motor to complete the revolution (adjust as needed)
  }

  previousStatus = proximityStatus; // Store the current status for comparison in the next iteration
}
