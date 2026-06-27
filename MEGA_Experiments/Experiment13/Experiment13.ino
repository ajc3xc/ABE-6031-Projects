
#include <DHT.h>
// ---------- Configuration ----------
#define DHTPIN 12 // DHT11 data pin
#define DHTTYPE DHT11 // DHT sensor type
DHT dht(DHTPIN, DHTTYPE);
const char* NODE_ID = "Node1"; // Unique node identifier
const unsigned long SEND_INTERVAL = 5000; // Send data every 5 seconds
unsigned long lastSendTime = 0;
// ---------- Setup ----------
void setup() {
Serial.begin(9600); // Serial communication with XBee
dht.begin();
Serial.println("DHT11 Node Initialized...");
}
// ---------- Main Loop ----------
void loop() {
unsigned long currentTime = millis();
// Send data at defined interval
if (currentTime - lastSendTime >= SEND_INTERVAL) {
lastSendTime = currentTime;
float humidity = dht.readHumidity();
float temperature = dht.readTemperature();
// Check for failed readings
if (isnan(humidity) || isnan(temperature)) {
Serial.println("Error reading from DHT11!");
return;
}
// Send data via Serial/XBee
// Format: NodeID,Temperature,Humidity
Serial.print(NODE_ID);
Serial.print(",");
Serial.print(temperature, 1);
Serial.print(",");
Serial.println(humidity, 1);
}
}
