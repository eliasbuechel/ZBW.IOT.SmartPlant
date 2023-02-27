#pragma once

#include <WiFi/WiFiManager.h>
#include <MQTT/MqttClient.h>

namespace Communication
{
  extern ZbW::CommSubsystem::WiFiManager wifiManager;
  extern ZbW::CommSubsystem::MqttClient mqttClient;

  void connecting();
  bool execute();
}