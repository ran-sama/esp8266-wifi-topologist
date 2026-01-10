/*
please reference:
Ray Burnette http://www.hackster.io/rayburne/projects
RandDruid/esp8266-deauth (MIT) https://github.com/RandDruid/esp8266-deauth
kripthor/WiFiBeaconJam (no license) https://github.com/kripthor/WiFiBeaconJam
schneefux https://git.schneefux.xyz/schneefux/jimmiejammer/src/master/jimmiejammer.ino
further info http://www.esp8266.com/viewtopic.php?f=32&t=7025
*/

#include <ESP8266WiFi.h>
#include "./functions2.h"

#define disable 0
#define enable  1
// uint8_t channel = 1;
unsigned int channel = 1;

void setup() {
  Serial.begin(115200);
  Serial.println(" ");

  wifi_set_opmode(STATION_MODE);            // Promiscuous works only with station mode
  wifi_set_channel(channel);
  wifi_promiscuous_enable(disable);
  wifi_set_promiscuous_rx_cb(promisc_cb);   // Set up promiscuous callback
  wifi_promiscuous_enable(enable);
}

// 200ms scan intervals to have enough time to discover clients and APs (beacon interval is often 100ms)

void loop() {
  //Serial.println(channel);
  delay(200);
  if (channel < 13) {
    channel++;
    } else {
      channel = 1;
      }
  wifi_set_channel(channel);
  delay(1);
  }
