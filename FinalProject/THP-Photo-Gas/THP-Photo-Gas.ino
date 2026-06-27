#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SGP30.h>

#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Adafruit_SGP30 sgp;

const char* NODE_ID = "Node1";
const unsigned long SEND_INTERVAL = 5000;
unsigned long lastSendTime = 0;

const int PHOTO_PIN = A0;

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();

  Serial.println("Node Initialized...");

  if (!sgp.begin()) {
    Serial.println("SGP30 not found!");
  } else {
    Serial.println("SGP30 Initialized");

    // REQUIRED for proper operation
    sgp.IAQinit();

    Serial.println("SGP30 IAQ initialized. Warming up...");
  }
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = currentTime;

    // ---- DHT11 ----
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Error reading DHT11");
      return;
    }

    // ---- Photoresistor ----
    int light_raw = analogRead(PHOTO_PIN);

    // ---- SGP30 ----
    if (!sgp.IAQmeasure()) {
      Serial.println("SGP30 reading failed");
      return;
    }

    uint16_t eco2 = sgp.eCO2;
    uint16_t tvoc = sgp.TVOC;

    // ---- SEND ----
    Serial.print(NODE_ID);
    Serial.print(",");
    Serial.print(temperature, 1);
    Serial.print(",");
    Serial.print(humidity, 1);
    Serial.print(",");
    Serial.print(light_raw);
    Serial.print(",");
    Serial.print(eco2);
    Serial.print(",");
    Serial.println(tvoc);
  }
}
