const char *sketchName =     "wifi_reconnect_bare"; 
const char *ver =     " Version 0.0.2";  

#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClient.h>

#include "soc/soc.h" //disable brownout problems
#include "soc/rtc_cntl_reg.h" //disable brownout problems
#include "driver/rtc_io.h"
#include "src/OV2640.h"

#include "wifikeys.h"
#include <WiFiUdp.h>

#include "ESP32_FTPClient.h"

// Select camera model
//#define CAMERA_MODEL_WROVER_KIT
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

#define ENABLE_FTP
// Enable Debug interface and serial prints over UART1
//#define DEGUB_ESP

#ifdef DEGUB_ESP
  #define DBG(x) Serial.println(x)
#else 
  #define DBG(...)
#endif

void ftp_connect(){
  #ifdef ENABLE_FTP
    Serial.println("enable ftp defined");
//    ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 5000, 2);
      ESP32_FTPClient ftp (ftp_server,ftp_user,ftp_pass, 10000, 2);
    ftp.OpenConnection();
    // Upload to ftp server
    ftp.InitFile("Type A");

    Serial.print("working dir: ");
    Serial.println(ftp_path);
    ftp.ChangeWorkDir(ftp_path);
    String response = "";
//  ftp.InitFile("Type A");
//  ftp.DownloadString("helloworld.txt", response);
//  Serial.println("The file content is: " + response);

  String list[128];
  ftp.ContentList("./", list);
  Serial.println("\nDirectory info: ");
  for(int i = 0; i < sizeof(list); i++)
  {
    if(list[i].length() > 0)
      Serial.println(list[i]);
    else
      break;
  }
  ftp.CloseConnection();

  #endif
}
void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Connected to AP successfully!");
}

void WiFiGotIP(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("WiFi connected");
  Serial.println(ssid);
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Signal WIFI: ");
  Serial.println(WiFi.RSSI());
}

void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  Serial.println("Disconnected from WiFi access point: ");
  Serial.println(ssid);
  Serial.print("WiFi lost connection. Reason: ");
  Serial.println(info.wifi_sta_disconnected.reason);
  Serial.println("Trying to Reconnect");
  WiFi.begin(ssid, password);
}

void setup(){
  Serial.begin(115200);
  // delete old config
  WiFi.disconnect(true);
  delay(1000);

  WiFi.onEvent(WiFiStationConnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_CONNECTED);
  WiFi.onEvent(WiFiGotIP, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_GOT_IP);
  WiFi.onEvent(WiFiStationDisconnected, WiFiEvent_t::ARDUINO_EVENT_WIFI_STA_DISCONNECTED);

  WiFi.begin(ssid, password);
    
  Serial.println();
  Serial.println();
  Serial.println("Wait for WiFi... ");
  delay(5000); // give time for wifi to settle down. 
  ftp_connect();
}


void loop(){
  
  delay(1000); // 10 seconds

}
