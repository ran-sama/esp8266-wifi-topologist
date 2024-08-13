/*
please reference:
Ray Burnette http://www.hackster.io/rayburne/projects
RandDruid/esp8266-deauth (MIT) https://github.com/RandDruid/esp8266-deauth
kripthor/WiFiBeaconJam (no license) https://github.com/kripthor/WiFiBeaconJam
schneefux https://git.schneefux.xyz/schneefux/jimmiejammer/src/master/jimmiejammer.ino
further info http://www.esp8266.com/viewtopic.php?f=32&t=7025
*/

extern "C" {
#include "user_interface.h"
  typedef void (*freedom_outside_cb_t)(uint8 status);
  int  wifi_register_send_pkt_freedom_cb(freedom_outside_cb_t cb);
  void wifi_unregister_send_pkt_freedom_cb(void);
  int  wifi_send_pkt_freedom(uint8 *buf, int len, bool sys_seq);
}

#include <ESP8266WiFi.h>
#include "./structures2.h"

#define MAX_APS_TRACKED 100

beaconinfo aps_known[MAX_APS_TRACKED];                    // Array to save MACs of known APs
int aps_known_count = 0;                                  // Number of known APs


int register_beacon(beaconinfo beacon)
{
  int known = 0;   // Clear known flag
  for (int u = 0; u < aps_known_count; u++)
  {
    if (! memcmp(aps_known[u].bssid, beacon.bssid, ETH_MAC_LEN)) {
      known = 1;
      break;
    }   // AP known => Set known flag
  }
  if (! known)  // AP is NEW, copy MAC to array and return it
  {
    memcpy(&aps_known[aps_known_count], &beacon, sizeof(beacon));
    aps_known_count++;

    if ((unsigned int) aps_known_count >=
        sizeof (aps_known) / sizeof (aps_known[0]) ) {
      //Serial.printf("exceeded max aps_known\n");
      aps_known_count = 0;
    }
  }
  return known;
}

void print_client(clientinfo ci)
{
  int u = 0;
  int known = 0;   // Clear known flag
  if (ci.err != 0) {
    // nothing
  } else {
    for (int i = 0; i < 6; i++) Serial.printf("%02x", ci.station[i]);
    Serial.printf(",");

    for (u = 0; u < aps_known_count; u++)
    {
      if (! memcmp(aps_known[u].bssid, ci.bssid, ETH_MAC_LEN)) {
        Serial.printf("%2s", aps_known[u].ssid);
        known = 1;     // AP known => Set known flag
        break;
      }
    }

    if (! known)  {
    //for (int i = 0; i < 6; i++) Serial.printf("%02x", ci.bssid[i]);
	Serial.printf("Unknown\n");
    } else {
      Serial.printf("\n");
    }
  }
}

void promisc_cb(uint8_t *buf, uint16_t len)
{
  int i = 0;
  uint16_t seq_n_new = 0;
  if (len == 12) {
    struct RxControl *sniffer = (struct RxControl*) buf;
  } else if (len == 128) {
    struct sniffer_buf2 *sniffer = (struct sniffer_buf2*) buf;
    struct beaconinfo beacon = parse_beacon(sniffer->buf, 112, sniffer->rx_ctrl.rssi);
    if (register_beacon(beacon) == 0) {
    // nothing
    }
  } else {
    struct sniffer_buf *sniffer = (struct sniffer_buf*) buf;
    //Is data or QOS?
    if ((sniffer->buf[0] == 0x08) || (sniffer->buf[0] == 0x88)) {
      struct clientinfo ci = parse_data(sniffer->buf, 36, sniffer->rx_ctrl.rssi, sniffer->rx_ctrl.channel);
      if (memcmp(ci.bssid, ci.station, ETH_MAC_LEN)) {
        print_client(ci);
      }
    }
  }
}
