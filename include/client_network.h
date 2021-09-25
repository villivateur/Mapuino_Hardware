#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

class ClientNetwork
{
private:
    String url;
    StaticJsonDocument<512> receivedData;
    HTTPClient* http;
    STATUS status;

public:
    ClientNetwork();
    STATUS FetchNewData();
    uint32_t GetSeg0();
    uint32_t GetSeg1();
};