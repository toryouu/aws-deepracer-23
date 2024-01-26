#define VIBRATION_SENSOR_PIN D2
 
int motion_detected = LOW;
 
void setup() {
  Serial.begin(115200);
}
 
void loop() {
  motion_detected = digitalRead(VIBRATION_SENSOR_PIN);
  delay(1000);

  if (motion_detected == 1)
  Serial.println("Rakan anda telah kemalangan! Sila pickup ya.");
}