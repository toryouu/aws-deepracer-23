#include <Servo.h>

Servo servo;

void setup() {
servo.attach(2); //D4
servo.write(0);
delay(2000);
}

void loop() {
servo.write(45);
delay(3000);
servo.write(0);
delay(3000);
}