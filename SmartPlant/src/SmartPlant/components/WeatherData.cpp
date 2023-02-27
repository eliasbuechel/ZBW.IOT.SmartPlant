#include "WeatherData.h"

#include <WiFi.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <HTTPClient.h>

#include "../library/Communication.h"
#include <StopWatch.h>

// Replace with your OpenWeatherMap API key
static const char* apiKey = "f193083d7bbf5086f035245a734646bc";

// Replace with the city and country code you want weather data for
static const char* zipCode = "8001";
static const char* countryCode = "ch";

// Define the HTTP client object and API endpoint URL
static HTTPClient httpClient;
static String currentUrl = "http://api.openweathermap.org/data/2.5/weather?zip=" + String(zipCode) + "," + String(countryCode) + "&units=metric&appid=" + String(apiKey);
static String forecastUrl = "http://api.openweathermap.org/data/2.5/forecast?zip=" + String(zipCode) + "," + String(countryCode) + "&units=metric&appid=" + String(apiKey) + "&cnt=4";

static ZbW::StopWatch wetherRefreshTimer = ZbW::StopWatch(15000);
static bool startedTimer = false;

static int getWeatherData(String& wetherData, const String& url)
{
    int httpResponseCode;

    httpClient.begin(Communication::wifiManager.operator WiFiClient &(), url);
    httpResponseCode = httpClient.GET();

    if (httpResponseCode != HTTP_CODE_OK) {
        Serial.print("Failed to get weather data! HTTP response code: ");
        Serial.println(httpResponseCode);
        httpClient.end();
        return httpResponseCode;
    }

    wetherData = httpClient.getString();
    httpClient.end();

    return httpResponseCode;
}

static bool convertToJsonObject(JsonObject& jsonObject, const String& wetherData)
{
    static DynamicJsonDocument jsonDocument(4096); // declare static to reuse same object
    jsonDocument.clear(); // clear previous contents

    ArduinoJson6201_F1::DeserializationError deserializationError = deserializeJson(jsonDocument, wetherData);

    if (deserializationError.code() != ArduinoJson6201_F1::DeserializationError::Code::Ok)
    {
        Serial.print("Json-deserializion faild width code ");
        Serial.print((int)(deserializationError.code()));
        Serial.println(" and following input:");
        Serial.println(wetherData);
        return false;
    }

    jsonObject = jsonDocument.as<JsonObject>();

    return true;
}

static float getCurrentTemperature(JsonObject& current)
{
    float temperature = current["main"]["temp"];
    Serial.print("Current temperature: ");
    Serial.print(temperature);
    Serial.println("°C");

    return temperature;
}

static float getCurrentPropabilityOfRain(JsonObject& forecast)
{
    float propabilityOfRain = forecast["list"][0]["pop"];
    Serial.print("Current probability of rain: ");
    Serial.print(propabilityOfRain*100);
    Serial.println("%");

    return propabilityOfRain;
}

static float getForecastPropabilityOfRain_12h(JsonObject& forecast)
{
    float propabilityOfRain = 0;
    for (int i = 0; i <= 4; i++)
    {
        float currentPropabilityOfRain = forecast["list"][i]["pop"];
        propabilityOfRain += currentPropabilityOfRain;
    }
    propabilityOfRain /= 4;
    Serial.print("Probability of rain in the next 12 hours: ");
    Serial.print(propabilityOfRain*100);
    Serial.println("%");

    return propabilityOfRain;
}

static bool getCurrentWeatherData(JsonObject& weatherData)
{
    int httpResponseCode;
    String currentWeatherData;

    httpResponseCode = getWeatherData(currentWeatherData, currentUrl); 
    if (httpResponseCode != HTTP_CODE_OK)
    {
        Serial.print("Failed to get current wether data! HTTP-Response code: ");
        Serial.println(httpResponseCode);
        return false;
    }
    // Serial.println("Current wether data:");
    // Serial.println(currentWeatherData);

    weatherData.clear();
    if (!convertToJsonObject(weatherData, currentWeatherData))
        return false;

    return true;
}

static bool getForecastWeatherData(JsonObject& weatherData)
{
    int httpResponseCode;
    String forecastWeatherData;

    httpResponseCode = getWeatherData(forecastWeatherData, forecastUrl);
    if (httpResponseCode != HTTP_CODE_OK)
    {
        Serial.print("Failed to get forecast wether data! HTTP-Response code: ");
        Serial.println(httpResponseCode);
        return false;
    }
    // Serial.println("Forecast wether data:");
    // Serial.println(forecastWeatherData);

    weatherData.clear();
    if (!convertToJsonObject(weatherData, forecastWeatherData))
        return false;

    return true;
}

static bool refreshWeatherData()
{
    float currentTemperature;
    float currentPropabilityOfRain;
    float forecastPropabilityOfRain_12h;
    bool isAboveFreezing;

    JsonObject weatherData;

    if (!getCurrentWeatherData(weatherData))
        return false;

    currentTemperature = getCurrentTemperature(weatherData);
    isAboveFreezing = currentTemperature > 0.0f;

    if (!getForecastWeatherData(weatherData))
        return false;

    currentPropabilityOfRain = getCurrentPropabilityOfRain(weatherData);
    forecastPropabilityOfRain_12h = getForecastPropabilityOfRain_12h(weatherData);

    // send data to broker
    Communication::mqttClient.publish("SmartPlant/WeatherData/location/zipCode", String(zipCode));
    Communication::mqttClient.publish("SmartPlant/WeatherData/location/countryCode", String(countryCode));
    Communication::mqttClient.publish("SmartPlant/WeatherData/currentTemperature", String(currentTemperature));
    Communication::mqttClient.publish("SmartPlant/WeatherData/currentPropabilityOfRain", String(currentPropabilityOfRain));
    Communication::mqttClient.publish("SmartPlant/WeatherData/forecastPropabilityOfRain_12h", String(forecastPropabilityOfRain_12h));
    Communication::mqttClient.publish("SmartPlant/WeatherData/isAboveFreezing", String(isAboveFreezing));

    return true;
}

static bool testRefreshWeatherData()
{
    float currentTemperature = 0.73f;
    float currentPropabilityOfRain = 0.35f;
    float forecastPropabilityOfRain_12h = 0.12f;
    bool isAboveFreezing = currentTemperature > 0.0f;

    Communication::mqttClient.publish("SmartPlant/WeatherData/location/zipCode", String(zipCode));
    Communication::mqttClient.publish("SmartPlant/WeatherData/location/countryCode", String(countryCode));
    Communication::mqttClient.publish("SmartPlant/WeatherData/currentTemperature", String(currentTemperature));
    Communication::mqttClient.publish("SmartPlant/WeatherData/currentPropabilityOfRain", String(currentPropabilityOfRain));
    Communication::mqttClient.publish("SmartPlant/WeatherData/forecastPropabilityOfRain_12h", String(forecastPropabilityOfRain_12h));
    Communication::mqttClient.publish("SmartPlant/WeatherData/isAboveFreezing", String(isAboveFreezing));
    
    return true;
}

bool WetherData::execute()
{
    if (!startedTimer)
    {
        wetherRefreshTimer.restart();
        startedTimer = true;
    }

    if (!wetherRefreshTimer.isTimeout())
        return false;

    if (!Communication::wifiManager.connected())
        return false;

    wetherRefreshTimer.restart();
    return testRefreshWeatherData();
    // return refreshWeatherData();
}