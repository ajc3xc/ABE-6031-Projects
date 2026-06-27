// www.elegoo.com
// Modified: 2025.09.26

#include "SR04.h"

// Pin definitions
#define TRIG_PIN 9
#define ECHO_PIN 8
#define BUZZER_PIN 11
#define RED_LED_PIN 7
#define GREEN_LED_PIN 6

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
long distance;

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
  distance = sr04.Distance();

  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 10) {
    // Danger zone: turn ON buzzer + red LED
    digitalWrite(RED_LED_PIN, HIGH);
    digitalWrite(GREEN_LED_PIN, LOW);

    digitalWrite(BUZZER_PIN, HIGH); // activate buzzer
  } else {
    // Safe zone: green LED ON, others OFF
    digitalWrite(RED_LED_PIN, LOW);
    digitalWrite(GREEN_LED_PIN, HIGH);

    digitalWrite(BUZZER_PIN, LOW); // deactivate buzzer
  }

  delay(200); // small delay for stability
}
