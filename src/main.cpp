#include <Arduino.h>
#include "display.h"
#include "client_network.h"
#include "monitor_items.h"
#include "status_blink.h"
#include "config_manager.h"
#include "user_data.h"
#include "func_button.h"

DisplayPanel* displayPanel;
ClientNetwork* netClient;
StatusBlink* statusLed;
UserData* userdataManager;
ConfigManager* configManager;
FuncButton* funcButton;

void setup()
{
    statusLed = new StatusBlink();
    userdataManager = new UserData();
    displayPanel = new DisplayPanel();
    funcButton = new FuncButton();

    if (!userdataManager->UserDataValid()) {
        configManager = new ConfigManager();
        configManager->ProcessConfig();
    } else {
        netClient = new ClientNetwork();
    }
}

void loop()
{
    static uint32_t tickCount = 0;

    delay(1000);
    tickCount++;
    funcButton->Scan();

    if (tickCount % 60 == 0) {
        if (netClient->FetchNewData() != OK) {
            return;
        }
        displayPanel->DisplayLedMap(netClient->GetSeg0(), netClient->GetSeg1());
    }
}
