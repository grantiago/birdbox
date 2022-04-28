/*
   ESP32cam_ftp
   Blog: http://www.gsampallo.com/blog/?p=686
   Twitter: @gsampallo.com
   using the formatted time from https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
*/
#include "esp_camera.h"
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include "ESP32_FTPClient.h"
#include <NTPClient.h> //For request date and time
#include <WiFiUdp.h>


const char* standBy = "5 minutes";
const char* ssid = "cfax2";
const char* password = "";
char ftp_server[] = "45.79.67.215";
char ftp_user[]   = "ftpWebcam";
char ftp_pass[]   = "";
char* ftp_path = "/birdbox/";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String formattedDate;
String dayStamp;
String timeStamp;

//NTPClient timeClient(ntpUDP, "pool.ntp.org");  // -3 to -6
//NTPClient timeClient(ntpUDP, "pool.ntp.org", (-3600*6), 60000);  // -3 to -6

ESP32_FTPClient ftp (ftp_server, ftp_user, ftp_pass, 5000, 2);

#define ONBOARD_LED  2 // blink the onboard led
// Pin definition for CAMERA_MODEL_AI_THINKER
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define FLASH_GPIO_NUM 4
camera_config_t config;

void setup() {
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector
  
  pinMode(33, OUTPUT); // Set the pin as output
  //pinMode(ONBOARD_LED,OUTPUT); // Set the onboard pin as output
  Serial.begin(115200);
  
  /*  IPAddress ip(192,168,1,23); // set the ip. cameras are in the 20s
  IPAddress gateway(192,168,1,1);
  IPAddress subnet(255,255,255,0);
  WiFi.config(ip, gateway, subnet);
  */ 

 
  WiFi.begin(ssid, password);
  Serial.println("Connecting Wifi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.println("Connecting to WiFi..");
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);
  timeClient.begin();
  timeClient.setTimeOffset(-25200); 

  initCamera();

  Serial.println(timeClient.getFormattedTime());
  //Serial.println(timeClient.getFullFormattedTimeForFile());
  Serial.println(timeClient.getEpochTime());

}

void loop() {
  ftp.OpenConnection(); // moved here inside the loop from 83
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  formattedDate = timeClient.getFormattedDate();
  //Serial.println(formattedDate);
  // blink
  digitalWrite(33, LOW); 
  delay(1000);
  digitalWrite(33, HIGH);
  delay(1000); //Wait 1 sec
  
  takePhoto();

  // 30000 30 seconds milliSec
  // 300000 = 5 minutes
  delay(300000); // 1000 = 1 second
}

void initCamera() {
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound()) {
    config.frame_size = FRAMESIZE_UXGA;//FRAMESIZE_UXGA; // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 10;
    config.fb_count = 2;
  } else {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }
  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void takePhoto() {

  camera_fb_t * fb = NULL;
  // Take Picture with Camera
  fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  /* Upload to ftp server */

  ftp.ChangeWorkDir(ftp_path);
  ftp.InitFile("Type I");
  // make the file name
  int splitT = formattedDate.indexOf("T");
  dayStamp = formattedDate.substring(0, splitT);
  // hour minute comes without the leading 0 - forget it.
  //int currentHour = timeClient.getHours();
  //int currentMin = timeClient.getMinutes();
  // Extract time
  timeStamp = formattedDate.substring(splitT + 1, formattedDate.length() - 1);
  //delay(1000);
  String myTrim = (timeStamp);
  
  String myTime = myTrim.substring(0, myTrim.length() - 3);
  myTime.replace(":", "-");
  Serial.print("trimmed and replaced :  ");
  Serial.println(myTime);
  //String myTime = (timeStamp);

  String myDate = String(dayStamp) + "_" + (myTime) + ".jpg";
  Serial.println(myDate);
  Serial.println("Subiendo " + myDate);
  int str_len = myDate.length() + 1;

  char char_array[str_len];
  myDate.toCharArray(char_array, str_len);

  ftp.NewFile(char_array);
  ftp.WriteData( fb->buf, fb->len );
  ftp.CloseFile();
  Serial.print("Waiting ");
  Serial.println(standBy);
  Serial.println("");

  /*  Free   */
  esp_camera_fb_return(fb);
}
