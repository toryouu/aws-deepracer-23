#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Firebase configuration
#define FIREBASE_HOST "esp8266-vibration-test-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "jrsvIFk264RDmZ3rnJABB8bZ0XSWM6wdvlPkpSMi"

// WiFi configuration
#define WIFI_SSID "yeetus"
#define WIFI_PASSWORD "mmmmmmmgej"

#define VIBRATION_PIN D2

FirebaseData firebaseData;

void setup() {
  pinMode(VIBRATION_PIN, INPUT);
  Serial.begin(9600);

  connectToWiFi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
}

void loop() {
  long measurement = readVibrationSensor();
  delay(10);

  Serial.println(measurement);
  sendToFirebase(measurement);

  // Check if the measurement exceeds 35,000
  if (measurement > 35000) {
    // If it does, set the value in Firebase to "Crash detected"
    if (Firebase.setString(firebaseData, "/status", "Crash detected")) {
      Serial.println("Crash detected. Data sent to Firebase.");
    } else {
      Serial.println("Failed to set status in Firebase.");
    }

    delay(99999);
  } else {
    // If it doesn't exceed 35,000, set the value in Firebase to "Normal"
    if (Firebase.setString(firebaseData, "/status", "Normal")) {
      Serial.println("Normal. Data sent to Firebase.");
    } else {
      Serial.println("Failed to set status in Firebase.");
    }
  }
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

void sendToFirebase(long data) {
  // Set the vibration data to Firebase as an integer
  if (Firebase.setInt(firebaseData, "/vibration", data)) {
    Serial.println("Data sent to Firebase successfully");
  } else {
    Serial.println("Failed to send data to Firebase");
  }
}