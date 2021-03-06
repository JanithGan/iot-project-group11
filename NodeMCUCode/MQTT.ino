// Initialize MQTT
void initMQTT()
{
  mqttClient.setServer(mqtt_server, 1883);
  mqttClient.setCallback(callbackMQTT);
}

// Reconnect to MQTT
void reconnectMQTT()
{
  while (!mqttClient.connected())
  {
    // Create a random MQTT client ID
    String mqttClientId = "ESP8266Client-";
    mqttClientId += String(random(0xffff), HEX);

    Serial.println("Attempting MQTT Connection...");
    Serial.print("MQTT Connection : ");

    if (mqttClient.connect(mqttClientId.c_str()))
    {
      Serial.println("Success!\n");

      mqttClient.publish(hello_topic, "Hello"); // Publish once

      mqttClient.subscribe(hello_topic); // Subscribe
      mqttClient.subscribe(AQI_topic);
      mqttClient.subscribe(time_zone_topic);
    }
    else
    {
      removeAlertLevel();
      Serial.print("Failed!, rc = ");
      Serial.println(mqttClient.state());
      Serial.println("Try Again in 5 Seconds...\n");
      delay(5000);
    }
  }
}

// MQTT callback function
void callbackMQTT(char *topic, byte *payload, unsigned int length)
{
  // Topic
  Serial.print("MQTT Message Arrived [");
  Serial.print(topic);
  Serial.print("] : ");

  getMQTTMessage(payload, length);

  if (!strcmp(topic, AQI_topic))
  {
    updateAQI();
  }
  else if (!strcmp(topic, time_zone_topic))
  {
    updateTimeZone();
  }
  else
  {
    Serial.println(mqttMsg);
  }
}

// Get message from MQTT payload
void getMQTTMessage(byte *payload, unsigned int length)
{
  mqttMsg = "";
  for (int i = 0; i < length; i++)
  {
    mqttMsg += (char)payload[i];
  }
}

// Publish to MQTT
void publishMQTT(char const *topic)
{
  if (!strcmp(topic, location_topic))
  {
    locationMsg.toCharArray(_mqtt_buf, BUF_SIZE);
    mqttClient.publish(location_topic, _mqtt_buf);
  }

  Serial.print("MQTT Message Published [");
  Serial.print(topic);
  Serial.print("] : ");
}
