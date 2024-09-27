#pragma once
#ifndef __QUEUE_SERVICE
#define __QUEUE_SERVICE

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

// #pragma once 
#define Q_BEGIN_VAL "$"
#define Q_BEGIN 0
#define Q_TIMESTAMP 1
#define Q_PIR0 2
#define Q_PIR1 3
#define Q_PIR2 4
#define Q_PIR3 5
#define Q_PIR4 6
#define ITEMS_NUM 20
#define ITEM_SIZE 16
extern QueueHandle_t queue;


#endif 

