#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char* ssid = "yeetus";
const char* password = "mmmmmmmgej";

#define BOTtoken "6741792342:AAHTeQHVSVLbGgH1RY2YHqH4mUS78g7MR2A"  
#define CHAT_ID "-1002122009060"  // either personal or group -- personal poloski = 927601407   personal aniq = 892635013    group = -1002122009060  

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int vibr_Pin = D2;

void setup() {
  pinMode(vibr_Pin, INPUT);
  Serial.begin(115200);
  // Initialize Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi!");
  client.setInsecure();
  bot.sendMessage(CHAT_ID, "SAYA HIDUP YA", "");
}

void loop() {
  client.setInsecure();
  long measurement = TP_init();
  
  Serial.print("Measurement = ");
  Serial.println(measurement);

  delay(100);

  if (measurement > 25000) {
    if (bot.sendMessage(CHAT_ID, "Kemalangan Dikesan, Rider ini Skill issue.\nINI ADALAH SATU KEJAYAAN! Sila kutip ya!!!", "")){
       Serial.print("SUCCESS to send to Telegram.\n");
     }
     else {
       Serial.print("FAILED to send to Telegram.\n");
     };
  };
}

long TP_init() {
  delay(10);
  long measurement = pulseIn(vibr_Pin, HIGH);
  return measurement;
}
