#include <WiFi.h>
#include <WiFiClient.h>
#include <ESPmDNS.h>
#include <WiFiAP.h>

// Wi-Fi credentials
const char* ssid = "2021_plus";
const char* password = "ztzz2023";

const int ledPin = LED_BUILTIN;  // Built-in LED pin

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);

  // Start blinking the LED
  blinkLED();

  // Connect to the Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    blinkLED();
    delay(500);
  }

  // Wi-Fi connected
  digitalWrite(ledPin, HIGH);
  Serial.println("Wi-Fi connected");

  // Keep the LED on for 5 seconds
  delay(5000);
  digitalWrite(ledPin, LOW);

  // Create Wi-Fi access point (extender)
  WiFi.softAP(ssid, password);
  Serial.println("Wi-Fi extender created with same SSID and password");

  // Handle new clients
  WiFi.onEvent(WiFiEvent);
}

void loop() {
  // Main loop does nothing, everything is handled by events
}

// Function to blink the LED
void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(250);
  digitalWrite(ledPin, LOW);
  delay(250);
}

// Wi-Fi event handler
void WiFiEvent(WiFiEvent_t event) {
  switch (event) {
    case SYSTEM_EVENT_AP_STACONNECTED:
      Serial.println("A device connected to the extender");
      // Turn on the LED for 3 seconds
      digitalWrite(ledPin, HIGH);
      delay(3000);
      // Blink the LED for 2 seconds
      for (int i = 0; i < 4; i++) {
        blinkLED();
      }
      digitalWrite(ledPin, LOW);
      break;
    default:
      break;
  }
}
