#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

// Wi-Fi credentials for original Wi-Fi
const char* ssid = "2021_plus";
const char* password = "ztzz2023";

// AP credentials (same as original Wi-Fi for extender functionality)
const char* ap_ssid = "2021_pl";
const char* ap_password = "ztzz2023";

// LED pin
const int ledPin = 2;

// Server and Client
WiFiServer server(80);
WiFiClient client;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);

  // Connect to the original Wi-Fi network
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Start blinking the LED while connecting to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    blinkLED(500);  // Blink every 500 ms
  }

  // Wi-Fi is connected
  Serial.println("WiFi connected!");

  // Print the original IP address
  Serial.print("Original IP address: ");
  Serial.println(WiFi.localIP());

  // Turn on the LED for 5 seconds to indicate successful connection
  digitalWrite(ledPin, HIGH);
  delay(5000);
  digitalWrite(ledPin, LOW);

  // Setup AP mode with the same SSID and password
  WiFi.softAP(ap_ssid, ap_password);

  // Start the server
  server.begin();

  // Change the AP IP address (optional)
  IPAddress local_IP(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Print the changed IP address (AP IP address)
  Serial.print("Changed IP address (AP): ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Check for incoming clients
  client = server.available();

  if (client) {
    Serial.println("New Client connected");
    // LED behavior: on for 3 seconds, then blink for 2 seconds
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(3000);                 // Keep the LED on for 3 seconds
    for (int i = 0; i < 2; i++) {
      blinkLED(500);  // Blink every 500 ms for 2 seconds
    }
    client.stop();
  }

  delay(1000);  // Add a delay to avoid multiple detections
}

// Function to blink LED
void blinkLED(int delayTime) {
  digitalWrite(ledPin, HIGH);
  delay(delayTime);
  digitalWrite(ledPin, LOW);
  delay(delayTime);
}
