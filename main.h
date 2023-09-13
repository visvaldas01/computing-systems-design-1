#include <stdint.h>
#include "gpio.h"

enum ButtonState {
	NONE,
	SHORT,
	LONG
};

void wait(uint32_t Delay)
{
  uint32_t tickstart = HAL_GetTick();
  uint32_t wait = Delay;

  /* Add a freq to guarantee minimum wait */
  if (wait < HAL_MAX_DELAY)
  {
    wait += (uint32_t)(uwTickFreq);
  }

  while((HAL_GetTick() - tickstart) < wait)
  {
  }
}

_Bool Btn_Pressed() {
	return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_15) == GPIO_PIN_RESET;
}

enum ButtonState Get_Button_State() {
	uint32_t longThreshold = 600;
	uint32_t shortThreshold = 250;
	if (Btn_Pressed())
	    wait(shortThreshold);
	if (!Btn_Pressed())
	    return NONE;
	uint32_t start = HAL_GetTick();
	while (HAL_GetTick() - start < (longThreshold - shortThreshold))
	    if (!Btn_Pressed()) return SHORT;
	return LONG;
}

void Animation(int over) {
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	wait(300);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_SET);
	wait(300);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_14, GPIO_PIN_RESET);
	wait(300);
	for (int i = 0; i < over; i++) {
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_SET);
		wait(300);
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_13, GPIO_PIN_RESET);
		wait(300);
	}
}
