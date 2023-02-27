#pragma once

#include "../Communication.h"

static void LogMessage(const char *topic, const void *data, size_t len) {
  const char *message = (const char *)data;
  
  Serial.print("Topic: '");
  Serial.print(topic);
  Serial.print("' Message: '");
  for (int i = 0;i < len;i++) {
    Serial.print(message[i]);
  }
  Serial.println("'");
}

void onIsAboveFreezingHandler(void *context, const char *topic, const void *data, size_t len)
{
  const char *payload = (const char *)data;

  LogMessage(topic, data, len);

  String str = String(payload);

  bool isAboveFreezing = str.toInt() == 0 ? false : true;

  if (isAboveFreezing)
    Serial.println("Is above freezing");
  else
    Serial.println("Is beneath freezing");
}


bool configureBrokerSubscriptions()
{
    Communication::mqttClient.subscribe("SmartPlant/WeatherData/isAboveFreezing", onIsAboveFreezingHandler, nullptr);
    return true;
}