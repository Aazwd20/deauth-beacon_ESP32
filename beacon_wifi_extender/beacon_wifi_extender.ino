#include <WiFi.h>
#include <esp_wifi.h>

const char* ssid = "2021_plus";
const char* password = "ztzz2023";

const int LED_BUILTIN = 2;  // Adjust if needed

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Blink LED
    delay(500);
  }
  
  // Wi-Fi connected
  digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
  Serial.println("\nConnected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  
  // Keep LED on for 5 seconds
  delay(5000);
  digitalWrite(LED_BUILTIN, LOW);

  // Start the Access Point with the same credentials
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");

  // Wait for a user to connect to the AP
  // In practice, you may want to handle this more elegantly
  while (true) {
    if (WiFi.softAPgetStationNum() > 0) { // Check if a station is connected
      Serial.println("User connected to AP");
      digitalWrite(LED_BUILTIN, HIGH); // Turn on LED
      delay(3000);                     // Keep LED on for 3 seconds
      digitalWrite(LED_BUILTIN, LOW);  // Turn off LED
      delay(2000);                     // Blink LED for 2 seconds
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);
    }
    delay(1000); // Check every second
  }
}

void loop() {
  // Nothing here, all work done in setup
}
