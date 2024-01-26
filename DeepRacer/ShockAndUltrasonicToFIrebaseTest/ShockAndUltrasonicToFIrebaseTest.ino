#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Firebase configuration
#define FIREBASE_HOST "xxx"
#define FIREBASE_AUTH "xxx"

// WiFi configuration
#define WIFI_SSID "xxx"
#define WIFI_PASSWORD "xxx"

// Pin configuration
#define VIBRATION_PIN D2
#define TRIG_PIN D3
#define ECHO_PIN D4
#define ULTRASONIC_THRESHOLD_CM 4 // Set your ultrasonic sensor threshold in centimeters

FirebaseData firebaseData;

void setup() {
  Serial.begin(9600); // Initialize serial communication for debugging
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  connectToWiFi();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  Serial.begin(115200); // Initialize serial communication for ultrasonic sensor
}

void loop() {
  float distanceCm = readUltrasonicSensor();

  Serial.print("Ultrasonic Distance (cm): ");
  Serial.println(distanceCm);
  
  // Check for distance of ultrasonic distance
  if (distanceCm <= ULTRASONIC_THRESHOLD_CM) {
    long measurement = readVibrationSensor();

    Serial.print("Vibration Measurement: ");
    Serial.println(measurement);

    sendToFirebase(measurement);

    if (measurement >= 35000) {
      if (Firebase.setString(firebaseData, "/status", "Crash detected")) {
        Serial.println("Crash detected. Data sent to Firebase.");
      } 
      else {
        Serial.println("Failed to set status in Firebase.");
      }
      // Delay until next reading if crash value is met.
      delay(99999);
    } 
    else {
      if (Firebase.setString(firebaseData, "/status", "Normal")) {
        Serial.println("Normal. Data sent to Firebase.");
      } 
      else {
        Serial.println("Failed to set status in Firebase.");
      }
    }
  } 
  else {
    Serial.println("Ultrasonic threshold not met. Data not sent to Firebase.");
  }

  delay(1000);
}

void connectToWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

long readVibrationSensor() {
  delay(10);
  long measurement = pulseIn(VIBRATION_PIN, HIGH);
  return measurement;
}

float readUltrasonicSensor() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distanceCm = duration * 0.034 / 2.0;
  return distanceCm;
}

void sendToFirebase(long data) {
  // Set the vibration data to Firebase as an integer
  if (Firebase.setInt(firebaseData, "/vibration", data)) {
    Serial.println("Data sent to Firebase successfully");
  } else {
    Serial.println("Failed to send data to Firebase");
  }
}

