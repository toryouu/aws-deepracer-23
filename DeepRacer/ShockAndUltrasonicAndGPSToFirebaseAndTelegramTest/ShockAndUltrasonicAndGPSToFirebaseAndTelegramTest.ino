#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// WiFi configuration
#define WIFI_SSID "yeetus"
#define WIFI_PASSWORD "mmmmmmmgej"

// Firebase configuration
#define FIREBASE_HOST "esp8266-vibration-test-default-rtdb.asia-southeast1.firebasedatabase.app"
#define FIREBASE_AUTH "jrsvIFk264RDmZ3rnJABB8bZ0XSWM6wdvlPkpSMi"

// Telegram configuration
#define token "6741792342:AAHTeQHVSVLbGgH1RY2YHqH4mUS78g7MR2A"
#define chatId "-1002122009060"    // either personal or group -- personal poloski = 927601407   personal aniq = 892635013    group = -1002122009060 

// Vibration and Ultrasonic pin configuration
#define VIBRATION_PIN D2
#define TRIG_PIN D3
#define ECHO_PIN D4
#define CRASH_IMPACT_THRESHOLD_MS 500  // Set crash impact threshold in m/s^2  lowest min value 65000 
#define ULTRASONIC_THRESHOLD_CM 5  // Set ultrasonic sensor threshold in centimeters

//GPS Module RX pin to NodeMCU D5
//GPS Module TX pin to NodeMCU D6
const int RXPin = 14, TXPin = 12;

//Define FirebaseESP8266 data object
FirebaseData firebaseData;
FirebaseJson json;

WiFiClientSecure client;
UniversalTelegramBot bot(token, client);

SoftwareSerial neo6m(RXPin, TXPin);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);  // Initialize serial communication for debugging

  neo6m.begin(9600);

  Serial.begin(115200);  // Initialize serial communication for ultrasonic sensor

  pinMode(VIBRATION_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  connectToWiFi();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  client.setInsecure();
  bot.sendMessage(chatId, "SAYA HIDUP YA", "");
}

void loop() {
  smartdelay_gps(1000);

  float distanceCm = readUltrasonicSensor();

  Serial.print("Ultrasonic Distance (cm): ");
  Serial.println(distanceCm);

  // Check for distance of ultrasonic distance
  if (distanceCm <= ULTRASONIC_THRESHOLD_CM) {
    if (Firebase.setString(firebaseData, "/status", "ON")) {
      Serial.println("Helmet turned ON");
    }
    long measurement = readVibrationSensor();

    Serial.print("Vibration Measurement: ");
    Serial.println(measurement);

    sendToFirebase(measurement);

    if (measurement >= CRASH_IMPACT_THRESHOLD_MS) {
      if (Firebase.setString(firebaseData, "helmet/condition", "Crash detected")) {
        if (gps.location.isValid()) {
          float latitude = gps.location.lat();
          float longitude = gps.location.lng();

          if (Firebase.setFloat(firebaseData, "/GPS/f_latitude", latitude)) {
            print_ok();
          } else {
            print_fail();
          }

          if (Firebase.setFloat(firebaseData, "/GPS/f_longitude", longitude)) {
            print_ok();
          } else {
            print_fail();
          }

          // Send GPS coordinates to Telegram
          sendGPSCoordinatesToTelegram(latitude, longitude);

          Serial.println("Crash detected. Data sent to Firebase.");
        } else {
          Serial.println("No valid GPS data found.");
        }
        // Delay until next reading if crash value is met.
        delay(15000);
      } else {
        Serial.println("Failed to set status in Firebase.");
      }
    } else {
      if (Firebase.setString(firebaseData, "helmet/condition", "Normal")) {
        Serial.println("Normal. Data sent to Firebase.");
      }
    }
  } else {
    if (Firebase.setString(firebaseData, "/status", "OFF"))
      Serial.println("Ultrasonic threshold not met. Data not sent to Firebase.");
  }

  delay(1000);
}

void sendGPSCoordinatesToTelegram(float latitude, float longitude) {
  String message = "Crash detected!\n";
  message += "GPS Coordinates: " + String(latitude, 6) + ", " + String(longitude, 6);

  // Create a Google Maps link
  String googleMapsLink = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);

  // Add the Google Maps link to the message
  message += "\nGoogle Maps: " + googleMapsLink;

  if (bot.sendMessage(chatId, message)) {  // Remove the third argument here
    Serial.println("GPS coordinates and Google Maps link sent to Telegram.");
  } else {
    Serial.println("Failed to send GPS coordinates to Telegram.");
  }
}

static void smartdelay_gps(unsigned long ms) {
  unsigned long start = millis();
  do {
    while (neo6m.available())
      gps.encode(neo6m.read());
  } while (millis() - start < ms);
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
  if (Firebase.setInt(firebaseData, "helmet/vibration", data)) {
    Serial.println("Data sent to Firebase successfully");
  } else {
    Serial.println("Failed to send data to Firebase");
  }
}

void print_ok() {
  Serial.println("------------------------------------");
  Serial.println("OK");
  Serial.println("PATH: " + firebaseData.dataPath());
  Serial.println("TYPE: " + firebaseData.dataType());
  Serial.println("ETag: " + firebaseData.ETag());
  Serial.println("------------------------------------");
  Serial.println();
}

void print_fail() {
  Serial.println("------------------------------------");
  Serial.println("FAILED");
  Serial.println("REASON: " + firebaseData.errorReason());
  Serial.println("------------------------------------");
  Serial.println();
}