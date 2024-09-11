#pragma once
#ifndef __HTTP_H_
#define __HTTP_H_

#include <string.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "WifiConnect.h"
#include "queueService.h"
#include <cJSON.h>
/* Constants for Wi-Fi connection */
//#define WIFI_SSID "Sv 2022"
//#define WIFI_PASS "@sv22022"

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "192.168.45.42"
#define WEB_PORT "5000"
#define WEB_PATH "/api/new-record"



static const char *TAG = "example";

/* Prepare the payload and headers */
extern char *payload;



void http_get_task(void *pvParameters);

int sendToServer(int socket, char* packet, int len);
char *copyString(char s[], int len);
char *createJsonBody(int timestamp, char *pir_id, char *pirs_vol);
#endif // __HTTP_H_


