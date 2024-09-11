#include <stdio.h>

#include "driver/adc.h"
#include "esp_system.h"
#include <string.h>
#include "adc.h"
#include "Timestamp.h"
#include "WifiConnect.h"
#include "http.h"

void app_main()
{
    // adcQueue = xQueueCreate(10, sizeof(char *));

    // QueueHandle_t adcQueue = xQueueCreate(10, sizeof(int));
    ESP_ERROR_CHECK(nvs_flash_init());
    connect_to_wifi();
    initialize_sntp();
  

    wait_for_time();

   
    xTaskCreatePinnedToCore(adc_task, "adc_task", 8196, NULL, 1, NULL, 0); // Chạy task adc_task ở core 0
    xTaskCreatePinnedToCore(http_get_task, "http_post_task", 8192, NULL, 13, NULL, 1); // Chạy task http_post_task ở core 1

    
}
