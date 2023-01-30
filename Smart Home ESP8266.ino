#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define WIFI_SSID "R_Kepala_Lab"
#define WIFI_PASSWORD "tanyaadminprodi"

#define DATABASE_URL "smarthome-4c16d-default-rtdb.asia-southeast1.firebasedatabase.app"
#define API_KEY "i3sYEXwrdIy4u97IOslAiZGAJ2VvZqKt5veUrLiQ"

FirebaseData fbdo;
FirebaseConfig config;

bool lampu1;
bool lampu2;

#define PIN_LAMPU1 5
#define PIN_LAMPU2 4

unsigned long current = 0;
unsigned long prevSecond = 0;

void setup() {

  Serial.begin(115200);

  pinMode(PIN_LAMPU1, OUTPUT);
  pinMode(PIN_LAMPU2, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  Firebase.begin(DATABASE_URL, API_KEY);

  Firebase.reconnectWiFi(true);
}

void loop() {
  current = millis();
  if (current - prevSecond >= 1000) {
    prevSecond = current;

    Serial.printf("Status lampu 1... %s\n", Firebase.getBool(fbdo, F("/lamp1"), &lampu1) ? lampu1 ? "true" : "false" : fbdo.errorReason().c_str());

    Serial.printf("Status lampu 2... %s\n", Firebase.getBool(fbdo, F("/lamp2"), &lampu2) ? lampu2 ? "true" : "false" : fbdo.errorReason().c_str());

    Serial.println();
  }

  if (lampu1) {
    digitalWrite(PIN_LAMPU1, HIGH);
  } else {
    digitalWrite(PIN_LAMPU1, LOW);
  }

  if (lampu2) {
    digitalWrite(PIN_LAMPU2, HIGH);
  } else {
    digitalWrite(PIN_LAMPU2, LOW);
  }
}