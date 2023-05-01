/*
 * grantamaral@gmail.com
 * v. 0.1.1
 * standard opensource laughable license 2023
 * modified for pir
 * http post to mysql
 * from rui santos https://randomnerdtutorials.com/esp32-esp8266-raspberry-pi-lamp-server */

const char *sketchName = "http_post_log_pir";
const char *ver = "0.1.1";

#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi_keys.h"

const char* serverName = "http://grant.lan/birdbox/post_esp_data.php";

// Keep this API Key value to be compatible with the PHP code provided in the project page.
// If you change the apiKeyValue value, the PHP file /post_esp_data.php also needs to have the same key
String apiKeyValue = "tPmAT5Ab3j7F9";

unsigned long previousMillis = 0;
unsigned long interval = 30000;

// PIR motion sensor pin
//const int motionSensorPin = 13;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println("WiFi connected");
  Serial.println(ssid );
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}
void setup() {
  Serial.begin(115200);

  // added init
  initWiFi();
  Serial.print("Signal WIFI: ");
  Serial.println(WiFi.RSSI());

//  v 0.1.2 added
  Serial.print("sketch name: ");
  Serial.println(sketchName);
  Serial.print("Version: ");
  Serial.println(ver);

  // Set motion sensor pin as input
  // pinMode(motionSensorPin, INPUT);
}

void loop() {
  // Check WiFi connection status
   // reconnect
  unsigned long currentMillis = millis();
  // if WiFi is down, try reconnecting every CHECK_WIFI_TIME seconds
  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
  // end reconnect

  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      delay(1000); // probably not needed 
      esp_sleep_enable_ext0_wakeup(GPIO_NUM_13, 1); // 1 = High | 0 = Low
      


      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");

      String httpRequestData = "api_key=tPmAT5Ab3j7F9&sensor=BME280&location=Office&value1=24.75&value2=49.54&value3=1005.14";

      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
   
      if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
      
      Serial.println("Going to sleep now");
      // Wait for 1 second or 1000 miliseconds
      delay(1000);
      esp_deep_sleep_start();
    }
  
  else {
    Serial.println("WiFi Disconnected");
  }
}
