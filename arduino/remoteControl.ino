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

int sailPower = 10;

int sailSetting = 0;

int steeringPower = 10;

int steeringSetting = 90;

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char *ssid = "iPhone von Jonas";
const char *password = "12345678";

ESP8266WebServer server(80);

const char *webpage =
#include "webPage.h"
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

  server.on("/forward", []()
            {
    sailSetting += sailPower;
    sailSetting = constrain(sailSetting, 0, 180);
    sails.write(sailSetting);
    Serial.println("Take sails closer by: " + String(sailPower) + " from " + String(sailSetting - sailPower) + " to " + String(sailSetting));
    server.send(200, "text/plain", "forward"); });

  server.on("/driveStop", []()
            {
    Serial.println("driveStop");
    server.send(200, "text/plain", "driveStop"); });

  server.on("/back", []()
            {
    sailSetting -= sailPower;
    sailSetting = constrain(sailSetting, 0, 180);
    sails.write(sailSetting);
    Serial.println("Take sails closer by: " + String(sailPower) + " from " + String(sailSetting + sailPower) + " to " + String(sailSetting));
    server.send(200, "text/plain", "back"); });

  server.on("/right", []()
            {
    steeringSetting += steeringPower;
    steeringSetting = constrain(steeringSetting, 0, 180);
    rudder.write(steeringSetting);
    Serial.println("Set rudder to the right by : " + String(steeringPower) + " from " + String(steeringSetting - steeringPower) + " to " + String(steeringSetting));
    server.send(200, "text/plain", "right"); });

  server.on("/left", []()
            {
    steeringSetting -= steeringPower;
    steeringSetting = constrain(steeringSetting, 0, 180);
    rudder.write(steeringSetting);
    Serial.println("Set rudder to the left : " + String(steeringPower) + " from " + String(steeringSetting + steeringPower) + " to " + String(steeringSetting));
    server.send(200, "text/plain", "left"); });

  server.on("/steerStop", []()
            {
    Serial.println("steerStop");
    server.send(200, "text/plain", "steerStop"); });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  server.handleClient();
}
