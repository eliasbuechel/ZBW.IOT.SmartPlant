#include "Communication.h"

#include <config/secrets.h>
#include <config/mqtt.h>

ZbW::CommSubsystem::WiFiManager Communication::wifiManager = ZbW::CommSubsystem::WiFiManager();
ZbW::CommSubsystem::MqttClient Communication::mqttClient = ZbW::CommSubsystem::MqttClient(wifiManager);

void Communication::connecting()
{
    /*
    wifiManager.reset();
    mqttClient.reset();

    // WiFi
    Serial.println("WiFi: Initiating connection...");
    wifiManager.connect(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);

    // MQTT
    Serial.println("MQTT: Initiating connection...");
    mqttClient.CredentialsSet(MQTT_USERNAME, MQTT_PASSWORD);
    mqttClient.connect(MQTT_CLIENT_ID, MQTT_BROKER_IP, MQTT_BROKER_PORT);
    */


    Serial.print("Resetting WiFi...");
    wifiManager.reset();
    Serial.println("done");

    Serial.print("Resetting MQTT client...");
    mqttClient.reset();
    Serial.println("done");


    Serial.println("Initiating connection to WiFi");
    wifiManager.connect(SECRET_WIFI_SSID, SECRET_WIFI_PASSWORD);

    Serial.println("Initiating connection to MQTT broker");
    mqttClient.CredentialsSet(MQTT_USERNAME, MQTT_PASSWORD);
    mqttClient.connect(MQTT_CLIENT_ID, MQTT_BROKER_IP, MQTT_BROKER_PORT);
}

bool Communication::execute()
{
    wifiManager.run();

    if (!wifiManager.connected())
        return false;

    mqttClient.run();

    return true;
}