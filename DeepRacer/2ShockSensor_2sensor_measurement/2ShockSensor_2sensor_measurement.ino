int vibr_Pin1 = 5; // Vibration sensor on D1
int vibr_Pin2 = 4; // Vibration sensor on D2

void setup() {
  pinMode(vibr_Pin1, INPUT); // Set vibr_Pin1 as an input for measurement
  pinMode(vibr_Pin2, INPUT); // Set vibr_Pin2 as an input for measurement
  Serial.begin(9600); // Initialize serial communication at 9600 baud
}

void loop() {
  long measurement1 = TP_init(vibr_Pin1);
  long measurement2 = TP_init(vibr_Pin2);

  // Serial.print("Measurement Sensor 1: ");
  // Serial.println(measurement1);
  // Serial.print("Measurement Sensor 2: ");
  // Serial.println(measurement2);

  if (measurement1 > 25000 || measurement2 > 25000) {
    Serial.println("Vibration detected on one or both sensors! Ya.. otw meet maker.. >o<");
    Serial.print("Measurement Sensor 1: ");
    Serial.println(measurement1);
    Serial.print("Measurement Sensor 2: ");
    Serial.println(measurement2);
  }

  delay(250);
}

long TP_init(int vibr_Pin) {
  delay(10);
  long measurement = pulseIn(vibr_Pin, HIGH); // Wait for the pin to go HIGH and return measurement
  return measurement;
}
