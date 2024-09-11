
#include "adc.h"
// Task handler function
#include "http.h"

QueueHandle_t queue;

int encodePIRVols(
    __uint8_t index,
    __uint16_t pir_vol0,
    __uint16_t pir_vol1,
    __uint16_t pir_vol2,
    __uint16_t pir_vol3,
    __uint16_t pir_vol4,
    __uint8_t *encodedData);

void adc_task(void *pvParameters)
{

    // Configure ADC1 channels for full range with 11 dB attenuation
    adc1_config_width(ADC_WIDTH_BIT_12); // Set ADC resolution to 12 bits

    // Configure ADC1 channels for full range with 11 dB attenuation
    adc1_config_channel_atten(ADC1_CHANNEL_3, ADC_ATTEN_DB_11); // GPIO 39, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11); // GPIO 32, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_5, ADC_ATTEN_DB_11); // GPIO 33, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11); // GPIO 34, max input ~3.9V
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11); // GPIO 35, max input ~3.9V

   

  

    

    TickType_t GetTick = xTaskGetTickCount();
    while (1)
    {

        if (queue == NULL)
            xQueueCreate(ITEMS_NUM, ITEM_SIZE);

        time_t timestamp = get_current_timestamp();
        for (int i = 0; i < 100; i++)
        {
            int raw_data0 = adc1_get_raw(ADC1_CHANNEL_3);
            // sprintf(&StrPir0[i * 5], "%04d%c", raw_data0, (i != 99 ? '_' : '\0'));
            int raw_data1 = adc1_get_raw(ADC1_CHANNEL_4);

            

            // sprintf(&StrPir1[i * 5], "%04d%c", raw_data1, (i != 99 ? '_' : '\0'));
            int raw_data2 = adc1_get_raw(ADC1_CHANNEL_5);
            // sprintf(&StrPir2[i * 5], "%04d%c", raw_data2, (i != 99 ? '_' : '\0'));
            int raw_data3 = adc1_get_raw(ADC1_CHANNEL_6);
            // sprintf(&StrPir3[i * 5], "%04d%c", raw_data3, (i != 99 ? '_' : '\0'));
            int raw_data4 = adc1_get_raw(ADC1_CHANNEL_7);

            

            // sprintf(&StrPir4[i * 5], "%04d%c", raw_data4, (i != 99 ? '_' : '\0'));

            __uint8_t packet[12] = "";

            int rc = encodePIRVols(
                (__uint8_t) i,
                (__uint16_t) raw_data0,
                (__uint16_t) raw_data1,
                (__uint16_t) raw_data2,
                (__uint16_t) raw_data3,
                (__uint16_t) raw_data4,
                &packet
            );


            


            // Delay for 10 ms
            vTaskDelay(pdMS_TO_TICKS(10));
            // vTaskDelayUntil(&GetTick,10);
        }



      
      
    };
};

int encodePIRVols(
    __uint8_t index,
    __uint16_t pir_vol0,
    __uint16_t pir_vol1,
    __uint16_t pir_vol2,
    __uint16_t pir_vol3,
    __uint16_t pir_vol4,
    __uint8_t *encodedData)
{

    int sum = 0;
    // index
    encodedData[0] = index;

    // vol0
    encodedData[1] = (__uint8_t)(pir_vol0 >> 8);
    encodedData[2] = (__uint8_t)(pir_vol0);

    // vol1
    encodedData[3] = (__uint8_t)(pir_vol1 >> 8);
    encodedData[4] = (__uint8_t)(pir_vol1);

    // vol2
    encodedData[5] = (__uint8_t)(pir_vol2 >> 8);
    encodedData[6] = (__uint8_t)(pir_vol2);

    // vol3
    encodedData[7] = (__uint8_t)(pir_vol3 >> 8);
    encodedData[8] = (__uint8_t)(pir_vol3);

    // vol4
    encodedData[9] = (__uint8_t)(pir_vol4 >> 8);
    encodedData[10] = (__uint8_t)(pir_vol4);

    for (int i = 0; i <= 10; i++)
        sum += encodedData[i];

    encodedData[11] = (__uint8_t)(sum);

    return 12;
};
