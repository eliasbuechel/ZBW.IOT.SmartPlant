#include <config/mqtt.h>
#include "environment.h"

/**
 * @file
 * @brief       Application Secrets Setup Default-Implementation
 *      
 *              This file holds the default setup for application specific
 *              MQTT settings. In order to create a local, custom configuration, 
 *              see instructions in `src\config\README`.
 * 
 * @warning     This is a template. DO NOT EDIT THIS FILE! (see description above)
 * 
 * @author      Ueli Niederer, ueli.niederer@niederer-engineering.ch         
 * @copyright   Copyright (c) 2021 by Niederer Engineering GmbH
 */

 /**
  * @brief  The client ID the MQTT client announces to the broker
  * 
  * @note   If left empty, a MAC address based client ID will be used to connect.
  *         @see MqttClient::connect
  */
ENV_WEAK const char *MQTT_CLIENT_ID = "";
 
 /**
  * @brief The MQTT broker's IP address to connect to.
  */
ENV_WEAK const char *MQTT_BROKER_IP = "172.20.10.11";

/**
 * @brief The MQTT broker's port to connect to.
 * 
 * @note  Remove this line from your local configuration in order to rely on the 
 *        default settings.
 */
ENV_WEAK const int MQTT_BROKER_PORT = 1883;

/**
 * @brief The Username used to authenticate with the MQTT broker
 * 
 * @note  Remove this line from your local configuration in order to rely on the 
 *        default settings.
 */
ENV_WEAK const char *MQTT_USERNAME = "";

/**
 * @brief The password used to authenticate with the MQTT broker
 * 
 * @note  Remove this line from your local configuration in order to rely on the 
 *        default settings.
 */
ENV_WEAK const char *MQTT_PASSWORD = "";
