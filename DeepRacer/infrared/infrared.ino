#include <IRremote.h>
#define IR D2
bool ir;

void setup() {
  Serial.begin(9600);
  pinMode(IR, INPUT);
}

void loop() {
  ir = digitalRead(IR);
  delay(2000);
  if(ir == 1)
  {
  Serial.println("Object is present");
  }
  else if (ir == 0)
  {
  Serial.println("Empty");
  }
}