#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Button.h"
#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "Password"
#define STATAUTHTOKEN "AuthenticationKey"
#endif

static const uint8_t SWITCH1 = 0;
static const uint8_t SWITCH2 = 1;
static const uint8_t SWITCH3 = 2;
static const uint8_t SWITCH4 = 3;
static const uint8_t SWITCH5 = 4;

const char* authtoken = STATAUTHTOKEN;
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "WebsiteURL";
const int httpsPort = 443;

const char fingerprint[] PROGMEM = "WEBSITEFINGERPRINT(IF HTTPS)";

Button* light1 = new Button("class=\"light1\">"," ","light1",SWITCH1);
Button* light2 = new Button("class=\"light2\">"," ","light2",SWITCH2);
Button* fan1 = new Button("class=\"fan1\">"," ","fan1",SWITCH3);
Button* light3 = new Button("class=\"light3\">"," ","light3",SWITCH4);
FanSpeedButton* fanspeed = new FanSpeedButton("id=\"currentspeed\">Current Speed : "," ","Fan Speed",SWITCH5);

WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(0));
  pwm.begin();
  pwm.setPWMFreq(50);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setFingerprint(fingerprint);
  yield();
}

void connectToWifi();

void loop() {
  String url = "/";
  if(client.connect(host, httpsPort))
  {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "User-Agent: ESP8266\r\n" +
                "Connection: keep-alive\r\n\r\n");
    Serial.println("----------------------------");
    if(client.find(light1->loc))
    {
      client.readBytes(light1->value, 1); 
      light1->found();
    }
    if(client.find(light2->loc))
    {
      client.readBytes(light2->value, 1); 
      light2->found();
    }
    if(client.find(fan1->loc))
    {
      client.readBytes(fan1->value, 1); 
      fan1->found();
    }     
    if(client.find(light3->loc))
    {
      client.readBytes(light3->value, 1); 
      light3->found();
    }     
    if(client.find(fanspeed->loc))
    {
      client.readBytes(fanspeed->value, 1); 
      fanspeed->found();
    }
    int temp = random(22,50);
    String tempurl = String("/temp.php?temp=") + String(temp) + String("&authkey=") + String(authtoken);
    client.print(String("GET ") + tempurl + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "User-Agent: ESP8266\r\n" +
                "Connection: close\r\n\r\n");
    Serial.println("Temperature is "+String(temp)+" Degrees");
    Serial.println("----------------------------");
  }
  else
  {
    Serial.println("Error Connecting");
    connectToWifi();
  }
  delay(5000);
}

void connectToWifi(){
  WiFi.mode(WIFI_OFF);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
}
