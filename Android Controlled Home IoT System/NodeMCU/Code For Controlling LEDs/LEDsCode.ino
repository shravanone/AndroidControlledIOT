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
const char* host = "WebsiteURL";
const int httpsPort = 443;

WiFiClientSecure client;

Button* light1 = new Button("class=\"light1\">"," ","light1",LED1);
Button* light2 = new Button("class=\"light2\">"," ","light2",LED2);
Button* fan1 = new Button("class=\"fan1\">"," ","fan1",LED3);
Button* light3 = new Button("class=\"light3\">"," ","light3",LED4);
FanSpeedButton* fanspeed = new FanSpeedButton("id=\"currentspeed\">Current Speed : "," ","Fan Speed");

const char fingerprint[] PROGMEM = "WebsiteFingerprint";//If HTTPS

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

void loop() {
  String url = "/";
  if(client.connect(host, httpsPort))
  {
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "User-Agent: ESP8266\r\n" +
                "Connection: keep-alive\r\n\r\n");
    Serial.println("----------------------------");
    light1->update(client);
    light2->update(client);
    fan1->update(client);
    light3->update(client);
    fanspeed->update(client);
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
  }
  delay(5000);
}
