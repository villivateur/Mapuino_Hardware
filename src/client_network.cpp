#include "client_network.h"
#include "status_blink.h"
#include "user_data.h"
#include "func_button.h"

extern StatusBlink* statusLed;
extern UserData* userdataManager;
extern FuncButton* funcButton;

ClientNetwork::ClientNetwork()
{    
    WiFi.begin(userdataManager->GetWifiSsid(), userdataManager->GetWifiPasswd());

    statusLed->SetBlinkRate(StatusBlink::BlinkRate::Rate2Hz);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        funcButton->Scan();
    }
    statusLed->SetBlinkRate(StatusBlink::BlinkRate::RateAlwaysOff);
    url = "http://iot.vvzero.com/mapuino/hardwareAPI?UUID=";
    url += userdataManager->GetDeviceUuid();
    status = FAIL;
}

STATUS ClientNetwork::FetchNewData()
{
    status = FAIL;
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        http = new HTTPClient();
        if (http->begin(client, url)) {
            if (http->GET() == HTTP_CODE_OK) {
                if (deserializeJson(receivedData, http->getString().c_str()) == DeserializationError::Code::Ok) {
                    status = OK;
                }
            }
            http->end();
        }
        delete http;
    }
    return status;
}

uint32_t ClientNetwork::GetData0()
{
    if (status != OK) {
        return 0;
    } else {
        return (uint32_t)receivedData["DATA0"];
    }
}

uint32_t ClientNetwork::GetData1()
{
    if (status != OK) {
        return 0;
    } else {
        return (uint32_t)receivedData["DATA1"];
    }
}
