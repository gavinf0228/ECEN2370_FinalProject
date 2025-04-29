#include "stm32f4xx_hal.h"
#include <stdint.h>
#define MS_TO_S     1000


void initTimer();
void StartTimer();
void StopTimer();
uint32_t GetTimer();
