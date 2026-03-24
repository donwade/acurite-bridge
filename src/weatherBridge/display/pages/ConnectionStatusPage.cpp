
#include "weatherBridge/display/pages/ConnectionStatusPage.hpp"


static const unsigned char PROGMEM image_menu_tools_bits[] = {0x80, 0xe0, 0xc1, 0x60, 0x42, 0x80, 0x22, 0x8c, 0x13,
                                                              0x0c, 0x0a, 0xb4, 0x06, 0x48, 0x05, 0xf0, 0x0b, 0x00,
                                                              0x14, 0xe0, 0x29, 0xb0, 0x50, 0xd8, 0xa0, 0x6c, 0xc0,
                                                              0x34, 0x00, 0x1c, 0x00, 0x00};


static const unsigned char PROGMEM image_cloud_bits[] = {0x00, 0x00, 0x00, 0x07, 0xc0, 0x00, 0x08, 0x20, 0x00, 0x10,
                                                         0x10, 0x00, 0x30, 0x08, 0x00, 0x40, 0x0e, 0x00, 0x80, 0x01,
                                                         0x00, 0x80, 0x00, 0x80, 0x40, 0x00, 0x80, 0x3f, 0xff, 0x00,
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                         0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

static const unsigned char PROGMEM image_wifi_bits[] = {0x01, 0xf0, 0x00, 0x06, 0x0c, 0x00, 0x18, 0x03, 0x00, 0x21,
                                                        0xf0, 0x80, 0x46, 0x0c, 0x40, 0x88, 0x02, 0x20, 0x10, 0xe1,
                                                        0x00, 0x23, 0x18, 0x80, 0x04, 0x04, 0x00, 0x08, 0x42, 0x00,
                                                        0x01, 0xb0, 0x00, 0x02, 0x08, 0x00, 0x00, 0x40, 0x00, 0x00,
                                                        0xa0, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00};


ConnectionStatusPage::ConnectionStatusPage(MY_GFX &display) : DisplayPage(display) {}


void ConnectionStatusPage::paint(WeatherBridgeContext context) {
    // Wi-Fi details
	Home();

	delegate.setTextColor(TFT_YELLOW);
	delegate.setTextSize(1);
	delegate.setTextWrap(false);
	
    if (context.isConfigurationMode) {

        if (context.wifiApContext.isActive()) {
            lprintf( "SSID: %s", context.wifiApContext.getSsid());
        } else {
            lprintf( "AP_INIT_ERROR");
        }

        if (context.wifiApContext.isActive()) {
            if (context.wifiApContext.getPassword().isEmpty()) {
                lprintf("(No password)");
            } else {
                lprintf("PWD: %s", context.wifiApContext.getPassword());
            }
        }

        if (context.wifiApContext.isActive()) {
            lprintf(context.wifiApContext.getIp());
        } else {
            lprintf("AP idle");
        }
    } 
    else
    {
        const String &settingsSsid = context.settings.getWlanSsid();
        const String &activeSsid = context.wifiConnectionStatus.getSsid();
        bool isConnected = context.wifiConnectionStatus.isConnected();
        int rssi = context.wifiConnectionStatus.getRSSI();

        if (!activeSsid.isEmpty()) {
            lprintf("WLAN = %s", activeSsid.c_str());
        } else if (!settingsSsid.isEmpty()) {
            lprintf("SSID = %s", settingsSsid.c_str());
        } else {
            lprintf("Not Configured");
        }

		lprintf("SSID config %s", settingsSsid.isEmpty() ? "empty":"prgmd");
		lprintf("WLAN %s", activeSsid.isEmpty() ? "noconnect":"connected");
		
        if (isConnected) {
            lprintf("WLAN RSSI: %d", rssi);
        }
        

    }

    // Station details
    const String &stationId = context.settings.getSelectedStationId();
    bool isStationSelected = !stationId.isEmpty();
    int isConnected = context.measurementsStore.getRssi().hasValue();

	int rssi = context.wifiConnectionStatus.getRSSI();
    
    //int rssi =   isConnected 
    //		   ? context.measurementsStore.getRssi().getValue() 
    //		   : 0;

    //lprintf("STN: Acurite 5n1 %s config", isStationSelected ? "":"NOT");
  
    if (isStationSelected) {
        lprintf("ID: %s", stationId.c_str());
    }

    if (isConnected) {
        lprintf("WLAN RSSI: %d", rssi);
    } else if (isStationSelected) {
        lprintf("AP mode selected");
    }

}

