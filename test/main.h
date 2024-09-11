#ifndef __MAIN__H_
#define __MAIN__H_

#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "protocol_examples_common.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
//#include "sdkconfig.h"

/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "192.168.1.83"
#define WEB_PORT "8080"
#define WEB_PATH "/"

static const char *TAG = "example";

/* Prepare the payload and headers */
static const char *payload = "Thong tin da den server chua?";
static const char *REQUEST_FORMAT = "POST %s HTTP/1.1\r\n"
    "Host: %s:%s\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: %d\r\n"
    "\r\n"
    "%s";


static void http_post_task(void *pvParameters);

#endif /* __MAIN__H_ */