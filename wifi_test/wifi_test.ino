// This example uses an Arduino/Genuino Zero together with
// a WiFi101 Shield or a MKR1000 to connect to shiftr.io.
//
// IMPORTANT: This example uses the new WiFi101 library.
//
// You can check on your device after a successful
// connection here: https://shiftr.io/try.
//
// by Gilberto Conti
// https://github.com/256dpi/arduino-mqtt

#include <WiFi101.h>
#include <MQTT.h>

const char ssid[] = "Andrés";
const char pass[] = "12345678";

WiFiClient net;
MQTTClient client;

unsigned long lastMillis = 0;

void connect() {
  Serial.print("checking wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }

  Serial.print("\nconnecting...");
  while (!client.connect("Roboy", "try", "try")) {
    Serial.print(".");
    delay(1000);
  }

  Serial.println("\nconnected!");

  client.subscribe("/kalimbot_midi");
  // client.unsubscribe("/hello");
}

void messageReceived(String &topic, String &payload) {
  Serial.println("incoming: " + topic + " - " + payload);
  Serial1.println(payload);
}

char mystr[10];

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
  WiFi.begin(ssid, pass);

  // Note: Local domain names (e.g. "Computer.local" on OSX) are not supported by Arduino.
  // You need to set the IP address directly.
  client.begin("192.168.137.251", net);
  client.onMessage(messageReceived);

  connect();
}

void loop() {
  client.loop();

  if (!client.connected()) {
    connect();
  }
}
