// compiles MAR 01/02/2025
// have connection issues at work, so can't upload.

#include <Wire.h>
#include <WiFi.h>

#include <PubSubClient.h> // "PubSubClient" or https://github.com/knolleary/pubsubclient

#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();

#include "..\..\my_wifi.h"
//const char *ssid = "YOUR WIFI SSID";
//const char *password = "YOUR WIFI PASSWORD";
//const char *mqtt_server = "YOUR MQTT HOST";
const char *mqtt_channel = "Temp";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi()
{
    delay(10);
    // Connect to WiFi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
    String speed;
    for (int i = 0; i < length; i++)
    {
        speed += (char)payload[i];
    }
    tft.drawNumber(speed.toInt(), 100, 100, 7); // Draw the speed value
}

void reconnect()
{
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        if (client.connect("ESP32Client"))
        {
            Serial.println("connected");
            client.subscribe(mqtt_channel);
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

void setup()
{
    Serial.begin(115200);

    while(!Serial)
        delay(1);

    setup_wifi();
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);

}

void loop()
{
    if (!client.connected())
    {
        reconnect();
    }
    client.loop();
}
