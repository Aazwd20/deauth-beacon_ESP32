#include <WiFi.h>
#include <esp_wifi.h>

const char* ssid = "2021_plus";
const char* password = "ztzz2023";

const int LED_PIN = 2;  // Use the correct pin number for the built-in LED

// Function to perform deauth attack
void deauthAttack(const char* targetSSID) {
  Serial.println("Starting deauth attack...");

  // Start scanning for APs
  WiFi.scanNetworks(true);
  delay(2000); // Wait for scan to complete

  int n = WiFi.scanComplete();
  for (int i = 0; i < n; i++) {
    if (WiFi.SSID(i) == targetSSID) {
      Serial.printf("Found target AP: %s\n", WiFi.SSID(i).c_str());
      // Extract BSSID
      uint8_t* bssid = WiFi.BSSID(i);
      // In a real scenario, you would send deauth packets here
      // Since `esp_wifi_deauth_sta` is not used in this high-level context, we simulate:
      Serial.println("Deauth attack simulated.");
      break;
    }
  }
  WiFi.scanDelete();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.println("Initializing...");

  // Start Access Point
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");
  
  // Start deauth attack
  deauthAttack(ssid);

  Serial.println("Setup complete.");
}

void loop() {
  // Check if any device is connected to the access point
  if (WiFi.softAPgetStationNum() > 0) {
    Serial.println("User connected to AP");
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    delay(3000);                 // Keep LED on for 3 seconds
    digitalWrite(LED_PIN, LOW);  // Turn off LED
    delay(2000);                 // Blink LED for 2 seconds
    for (int i = 0; i < 4; i++) { // Blink LED 4 times
      digitalWrite(LED_PIN, HIGH);
      delay(500);
      digitalWrite(LED_PIN, LOW);
      delay(500);
    }
  }
  delay(1000); // Check every second
}
