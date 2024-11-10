#if defined(ESP32)
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Admin"
#define WIFI_PASSWORD "Kuk1Kuk2"

#define API_KEY "2ED6hmVB86KrCIEzgb3ygZwDbKwwGzC2lvjiacw5"
#define DATABASE_URL "https://early-flood-detection-system-default-rtdb.asia-southeast1.firebasedatabase.app/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
FirebaseJson json;
FirebaseData fidata;

int count;
int RXD2 = 16;
int TXD2 =  17;
void setup() {

  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
}

void loop() {
  String val = Serial2.readString();
  delay(200);
  if (Firebase.ready())
  {
    json.set("/Water_Level", val);
    Firebase.updateNode(fidata, "/SonarSensor", json);
    delay(2500);
  }
  Serial.println(val);
}
