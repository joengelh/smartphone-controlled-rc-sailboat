#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>

// Replace with your servo pin
int servoPin = 5;
int sailsPin = 4;

Servo rudder;
Servo sails;

int sailPower = 30;

int sailSetting = 90;

int rudderPower = 30;

int rudderSetting = 90;

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char *ssid = "bodenstation";
const char *password = "12345678";

ESP8266WebServer server(80);

const char *webpage =
#include "html/manual_control.h"
    ;

void handleRoot()
{
  server.send(200, "text/html", webpage);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  rudder.attach(servoPin);
  sails.attach(sailsPin);
  rudder.write(rudderSetting);
  sails.write(sailSetting);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("WifiCar"))
  {
    Serial.println("MDNS Responder Started");
  }

  server.on("/", handleRoot);

  server.on("/sailSetting", []()
            {
    String response = String(sailSetting);
    server.send(200, "text/plain", response); });

  server.on("/rudderSetting", []()
            {
    String response = String(rudderSetting);
    server.send(200, "text/plain", response); });

server.on("/sails", HTTP_POST, [](){
  if (server.hasArg("direction")) {
    String direction = server.arg("direction");
    if (direction == "open") {
      sailSetting -= sailPower;
    } else if (direction == "close") {
      sailSetting += sailPower;
    }
    sailSetting = constrain(sailSetting, 0, 180);
    sails.write(sailSetting);
    Serial.println("Set sails to " + direction + " : " + String(sailPower) + " from " + String(sailSetting - sailPower) + " to " + String(sailSetting));
    server.send(200, "text/plain", String(sailSetting));
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
});

server.on("/rudder", HTTP_POST, [](){
  if (server.hasArg("direction")) {
    String direction = server.arg("direction");
    if (direction == "left") {
      rudderSetting += rudderPower;
    } else if (direction == "right") {
      rudderSetting -= rudderPower;
    }
    rudderSetting = constrain(rudderSetting, 0, 180);
    rudder.write(rudderSetting);
    Serial.println("Set rudder to " + direction + " : " + String(rudderPower) + " from " + String(rudderSetting - rudderPower) + " to " + String(rudderSetting));
    server.send(200, "text/plain", String(rudderSetting));
  } else {
    server.send(400, "text/plain", "Bad Request");
  }
});

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  server.handleClient();
}