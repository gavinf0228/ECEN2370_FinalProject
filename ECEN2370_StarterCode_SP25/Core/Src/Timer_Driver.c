#include "Timer_Driver.h"
static uint32_t startTick;
static uint32_t stopTick;

//initializes the timer
void initTimer(){
    HAL_SetTickFreq(HAL_TICK_FREQ_DEFAULT);
}
//starts the timer
void StartTimer(){
    startTick = HAL_GetTick();
}
//stops the timer
void StopTimer(){
    stopTick = HAL_GetTick();
}
//get back the timer and converts the MS to S to be displayed
uint32_t GetTimer(){
    return (HAL_GetTick() - startTick) / MS_TO_S;
}

