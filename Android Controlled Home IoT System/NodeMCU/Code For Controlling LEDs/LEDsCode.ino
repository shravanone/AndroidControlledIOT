#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "Button.h"
#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "Password"
#define STATAUTHTOKEN "AuthenticationKey"
#endif

static const uint8_t LED1 = 14;
static const uint8_t LED2 = 12;
static const uint8_t LED3 = 13;
static const uint8_t LED4 = 15;

const char* authtoken = STATAUTHTOKEN;
const char* ssid = STASSID;
const char* password = STAPSK;
const char* host = "WebsiteAddress";
const int httpsPort = 443;

Button* light1 = new Button("class=\"light1\">"," ","light1",LED1);
Button* light2 = new Button("class=\"light2\">"," ","light2",LED2);
Button* fan1 = new Button("class=\"fan1\">"," ","fan1",LED3);
Button* light3 = new Button("class=\"light3\">"," ","light3",LED4);
FanSpeedButton* fanspeed = new FanSpeedButton("id=\"currentspeed\">Current Speed : "," ","Fan Speed");

const char fingerprint[] PROGMEM = "WEBSITES FINGERPRINT(IF HTTPS)";

WiFiClientSecure client;

void setup() {
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  Serial.begin(115200);
  randomSeed(analogRead(0));
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setFingerprint(fingerprint);
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
