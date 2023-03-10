#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Servo.h>
#include <ArduinoJson.h>

// ----------------
// Set your WiFi SSID and Password here
// ----------------
const char *ssid = "XXXXX";
const char *password = "YYYYY";

// ----------------
// configure servo pins
// ----------------
int servoPin = 5;
int sailsPin = 4;

// initialize servo pins
Servo rudder;
Servo sails;

// initialize variable to determine operation mode
enum operationMode
{
  MANUAL,
  HEADING,
  WAYPOINT
};

// initialize variable used for manual operation
int sailPower = 10;
int sailSetting = 90;
int rudderPower = 10;
int rudderSetting = 90;

// initialize variables used for automated steering
int factor = 10;

// initialize variables used for heading mode
int heading = 0;

// initialize variables used for waypoint mode
float waypoints[10];

ESP8266WebServer server(80);

const char *webpage =
#include "webPage.h"
    ;

void handleWaypoints()
{
  // Flush the coordinates array
  for (int i = 0; i < 10; i++)
  {
    waypoints[i] = 0;
  }

  // Parse the JSON data from the request body
  DynamicJsonDocument doc(1024);
  DeserializationError error = deserializeJson(doc, server.arg("plain"));

  // If the JSON is invalid, return a 400 Bad Request error
  if (error)
  {
    server.send(400, "text/plain", "Invalid JSON");
    return;
  }

  // Extract the coordinates from the JSON object and store them in the global variable
  JsonArray newWaypoints = doc.as<JsonArray>();
  for (int i = 0; i < newWaypoints.size(); i++)
  {
    waypoints[i] = newWaypoints[i];
  }

  // Send a success response
  server.send(200, "text/plain", "Coordinates saved");
}

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

  server.on("/heading", []()
            {
    String response = String(sailSetting);
    server.send(200, "text/plain", response); });

  server.on("/reach", []()
            {
    sailSetting += sailPower;
    sailSetting = constrain(sailSetting, 0, 180);
    sails.write(sailSetting);
    Serial.println("Take sails closer by: " + String(sailPower) + " from " + String(sailSetting - sailPower) + " to " + String(sailSetting));
    server.send(200, "text/plain", String(sailSetting)); });

  server.on("/run", []()
            {
    sailSetting -= sailPower;
    sailSetting = constrain(sailSetting, 0, 180);
    sails.write(sailSetting);
    Serial.println("Open the sails by: " + String(sailPower) + " from " + String(sailSetting + sailPower) + " to " + String(sailSetting));
    server.send(200, "text/plain", String(sailSetting)); });

  server.on("/starboard", []()
            {
    rudderSetting += rudderPower;
    rudderSetting = constrain(rudderSetting, 0, 180);
    rudder.write(rudderSetting);
    Serial.println("Set rudder to the right by : " + String(rudderPower) + " from " + String(rudderSetting - rudderPower) + " to " + String(rudderSetting));
    server.send(200, "text/plain", String(rudderSetting)); });

  server.on("/port", []()
            {
    rudderSetting -= rudderPower;
    rudderSetting = constrain(rudderSetting, 0, 180);
    rudder.write(rudderSetting);
    Serial.println("Set rudder to the left : " + String(rudderPower) + " from " + String(rudderSetting + rudderPower) + " to " + String(rudderSetting));
    server.send(200, "text/plain", String(rudderSetting)); });

  server.onNotFound(handleNotFound);

  server.on("/data", []()
            {
    StaticJsonDocument<200> data;

    Serial.println("Data requested");
    data["rudderSetting"] = rudderSetting;
    data["rudderPower"] = rudderPower;
    data["sailSetting"] = sailSetting;
    data["sailPower"] = sailPower;

    // Serialize the JSON object to a string
    String jsonString;
    serializeJson(data, jsonString);

    // Set the content type to JSON
    server.sendHeader("Content-Type", "application/json");

    // Send the JSON data as the response
    server.send(200, "application/json", jsonString); });

  // Register the endpoint for waypoint mode
  server.on("/waypoint", HTTP_POST, handleWaypoints);

  // Register the endpoint for waypoint mode
  server.on("/heading", HTTP_POST, handleHeading);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started");
}

void loop(void)
{
  server.handleClient();
}
