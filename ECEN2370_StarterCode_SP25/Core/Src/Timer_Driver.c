#include "Timer_Driver.h"
static uint32_t startTick;
static uint32_t stopTick;


void initTimer(){
    HAL_SetTickFreq(HAL_TICK_FREQ_DEFAULT);
}

void StartTimer(){
    startTick = HAL_GetTick();
}

void StopTimer(){
    stopTick = HAL_GetTick();
}

uint32_t GetTimer(){
    return (HAL_GetTick() - startTick) / MS_TO_S;
}

