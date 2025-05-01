#include "RNG_Driver.h"
#include "stdint.h"

RNG_HandleTypeDef hrng;

// this was taken from main and put here. only way i could figure out how to use the RNG stuff as it was greyed out. 
void MX_RNG_Init(void)
{

  /* USER CODE BEGIN RNG_Init 0 */

  /* USER CODE END RNG_Init 0 */

  /* USER CODE BEGIN RNG_Init 1 */

  /* USER CODE END RNG_Init 1 */
  hrng.Instance = RNG;
  if (HAL_RNG_Init(&hrng) != HAL_OK)
  {
    while(1){

    }
  }
  /* USER CODE BEGIN RNG_Init 2 */

  /* USER CODE END RNG_Init 2 */

} 

// generate a random number and get that. that random number represents the column
uint32_t GenerateRNGNum(){
    uint32_t column;

    HAL_RNG_GenerateRandomNumber(&hrng, &column);

    return column % 7; //to get numbre 0-6 for num of columns
}
