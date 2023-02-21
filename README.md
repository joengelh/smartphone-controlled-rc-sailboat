# smartphone-controlled-rc-sailboat

yep, that's that.
Work less, sail more.

## The concept

The ESP8266 has a builtin wifi module that can be used to access a smartphones hotspot network.
Thereby creating a direct, fast connection that, in the open, can reach for 100 meters and more.

The ESP8266 then can gernate a website through with the ship can be steered.

## Material used

1. Standard RC sailboat (1 servo to set the sails, 1 servo for steering)
2. ESP8266
3. Smartphone

## Setup

Connect the steering servo to port 5, the sail servo to pin 4
Fill in the wifi hotspot SSID and password, deploy to code, go to the arduinos webpage from your smartphone (could be 172.20.0.2 when its an iPhone), set sail

## Roadmap

Make the thing do waypoint missions :D
