#include <WiFi.h>
#include <esp_wifi.h>

// Wi-Fi credentials
const char* ssid = "2021_plus";
const char* password = "ztzz2023";

// LED pin
const int ledPin = 2;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Initialize the LED pin
  pinMode(ledPin, OUTPUT);

  // Start blinking the LED while connecting to Wi-Fi
  Serial.println("Connecting to WiFi...");
  WiFi.begin(ssid, password);

  // Wait for the Wi-Fi connection
  while (WiFi.status() != WL_CONNECTED) {
    blinkLED(500);  // Blink every 500 ms
  }

  // Wi-Fi is connected
  Serial.println("WiFi connected!");

  // Print the original IP address
  Serial.print("Original IP address: ");
  Serial.println(WiFi.localIP());

  // Turn on the LED for 5 seconds
  digitalWrite(ledPin, HIGH);
  delay(5000);
  digitalWrite(ledPin, LOW);

  // Setup AP mode with the same SSID and password
  WiFi.softAP(ssid, password);

  // Change the IP address (optional)
  IPAddress local_IP(192, 168, 1, 1);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(local_IP, gateway, subnet);

  // Print the changed IP address (AP IP address)
  Serial.print("Changed IP address (AP): ");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  // Check if a client has connected to the AP
  if (WiFi.softAPgetStationNum() > 0) {
    // A client has connected
    Serial.println("A device has connected!");

    // Collect and print the connected device's IP address
    wifi_sta_list_t stationList;
    esp_wifi_ap_get_sta_list(&stationList);
    for (int i = 0; i < stationList.num; i++) {
      wifi_sta_info_t station = stationList.sta[i];
      Serial.print("Device MAC Address: ");
      Serial.println(macToStr(station.mac).c_str());
    }

    // LED behavior: on for 3 seconds, then blink for 2 seconds
    digitalWrite(ledPin, HIGH);  // Turn on the LED
    delay(3000);                 // Keep the LED on for 3 seconds
    for (int i = 0; i < 2; i++) {
      blinkLED(500);  // Blink every 500 ms for 2 seconds
    }
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

// Convert MAC address to string
String macToStr(const uint8_t* mac) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  return String(macStr);
}
