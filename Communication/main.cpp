#include <Arduino.h>
#include <WiFiMulti.h>
#include "PubSubClient.h"
#include "Motor.h"
#include "Sensorultra.h"

//Motors Instance
Motor motor_right(16, 17, 18);
Motor motor_left(25, 26, 27);

//Ultrasonic Instance (echo, trigger)
Sensorultra sensorsonic(22, 23);

const char *SSID = "LabTech";
const char *PWD = "#*1wesDI";

//Robot Name - Must be Unique
const char *ROBOT_NAME = "Ultra2";

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

#define mqttServer "10.1.32.16"
int mqttPort = 1883;

int period = 2;
unsigned long time_now = 0;

void connectToWiFi()
{

  Serial.print("Connecting to ");

  WiFi.begin(SSID, PWD);
  Serial.println(SSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.print("Connected.");
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
  }
}

void setupMQTT()
{
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}

void setup()
{
  Serial.begin(115200);

  Serial.println();

  connectToWiFi();
  setupMQTT();
}

void reconnect()
{
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected())
  {
    Serial.println("Reconnecting to MQTT Broker..");
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);

    if (mqttClient.connect(clientId.c_str()))
    {
      Serial.println("Connected.");
      // subscribe to topic
      //mqttClient.subscribe("/swa/commands");
    }
  }
}

void loop()
{
  // Getting the distance from ultrassonic sensor to dt
  int dt = sensorsonic.ultradistancia();
  // Create space to have a string message
  char msg[100];

  //MSG to InfluxDB
  sprintf(msg, "%s,tag=Distance value=%d", ROBOT_NAME, dt);
  if (!mqttClient.connected())
    reconnect();
  // Starting the connection to the server
  mqttClient.loop();
  // It publishs date through MQTT in period time.
  if (millis() >= time_now + period)
  {
    time_now += period;
     //Test: data that will be published
    //Serial.print(msg);
    mqttClient.publish("data/ultrasonic", msg);
  }
  //If obstacle is at more than 50 cm...
  if (dt > 50)
  {
    motor_left.avancar(180);
    motor_right.avancar(180);
  }
  //Otherwise...
  else
  {
    motor_left.recuar(180);
    motor_right.recuar(180);
    delay(100);
    //Randomizing turn - left or right?
    int rand = random(0, 10);
    if (rand < 5)
    {
      motor_left.avancar(180);
      motor_right.recuar(180);
      delay(200);
    }
    else
    {
      motor_left.recuar(180);
      motor_right.avancar(180);
      delay(200);
    }
  }
}
