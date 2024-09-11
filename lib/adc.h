#pragma once
#ifndef __ADC__H_
#define __ADC__H_

#include <stdio.h>

#include "driver/adc.h"
#include "esp_system.h"
#include <string.h>
#include "cJSON.h"
#include "Timestamp.h"
// #include "queueService.h"
void adc_task(void *pvParameters);

int encodePIRVols(
    __uint8_t index,
    __uint16_t pir_vol0,
    __uint16_t pir_vol1,
    __uint16_t pir_vol2,
    __uint16_t pir_vol3,
    __uint16_t pir_vol4,
    __uint8_t *encodedData);

#endif
