#include "stm32f4xx_hal.h"

extern RNG_HandleTypeDef hrng;

void MX_RNG_Init(void);
uint32_t GenerateRNGNum();
void RNGMovement();