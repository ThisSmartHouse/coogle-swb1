/*
  +----------------------------------------------------------------------+
  | Coogle WiFi 4x4 Keypad                                               |
  +----------------------------------------------------------------------+
  | Copyright (c) 2017-2019 John Coggeshall                              |
  +----------------------------------------------------------------------+
  | Licensed under the Apache License, Version 2.0 (the "License");      |
  | you may not use this file except in compliance with the License. You |
  | may obtain a copy of the License at:                                 |
  |                                                                      |
  | http://www.apache.org/licenses/LICENSE-2.0                           |
  |                                                                      |
  | Unless required by applicable law or agreed to in writing, software  |
  | distributed under the License is distributed on an "AS IS" BASIS,    |
  | WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or      |
  | implied. See the License for the specific language governing         |
  | permissions and limitations under the License.                       |
  +----------------------------------------------------------------------+
  | Authors: John Coggeshall <john@thissmarthouse.com>                   |
  +----------------------------------------------------------------------+
*/
#ifndef __APP_H_
#define __APP_H_

#include "buildinfo.h"
#include "rboot.h"
#include "ArduinoJson.h"
#include <rboot-api.h>
#include "CoogleIOT_Logger.h"
#include "CoogleIOT_Wifi.h"
#include "CoogleIOT_NTP.h"
#include "CoogleIOT_MQTT.h"
#include "CoogleIOT_OTA.h"
#include "CoogleIOT_Config.h"
#include "logger.h"
#include <PubSubClient.h>

#ifndef SERIAL_BAUD
#define SERIAL_BAUD 115200
#endif

#ifndef DEBUG_HOSTNAME
#define DEBUG_HOSTNAME "coogle-switch"
#endif

#ifndef APP_NAME
#define APP_NAME "Coogle SWB1 4-Relay Switch"
#endif

#ifndef MQTT_TOPIC_MAX_LEN
#define MQTT_TOPIC_MAX_LEN 64
#endif

#ifndef NUM_SWITCHES
#define NUM_SWITCHES 4
#endif

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

typedef struct app_config_t {
	coogleiot_config_base_t base;
	char mqtt_topic[MQTT_TOPIC_MAX_LEN + 1] = {NULL};
  char mqtt_state_topic[MQTT_TOPIC_MAX_LEN + 1] = {NULL};
  bool turn_on_at_boot = false;
};

app_config_t *app_config = NULL;

const size_t json_state_size = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(5) + 70;

static uint8_t switch_map[NUM_SWITCHES] = {
  12, 14, 15, 5
};

class CoogleIOT_Logger;
class CoogleIOT_Wifi;
class CoogleIOT_NTP;
class CoogleIOT_MQTT;
class CoogleIOT_OTA;
class CoogleIOT_Config;

CoogleIOT_Config *configManager = NULL;
CoogleIOT_Logger *_ciot_log = NULL;
CoogleIOT_Wifi *WiFiManager = NULL;
CoogleIOT_NTP *NTPManager = NULL;
CoogleIOT_MQTT *mqttManager = NULL;
CoogleIOT_OTA *otaManager = NULL;

PubSubClient *mqtt = NULL;

bool onParseConfig(DynamicJsonDocument&);

void onMQTTConnect();
void onMQTTCommand(const char *, byte *, unsigned int);
void logSetupInfo();

void onNTPReady();
void onNewFirmware();

void setupConfig();
void setupSerial();
void setupMQTT();
void setupNTP();
void setupLogging();
void setupWiFi();
void setupOTA();

void setup();
void loop();

#endif
