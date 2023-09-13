#include <stdint.h>
#include "gpio.h"

enum ButtonState {
	NONE,
	SHORT,
	LONG
};

void wait(uint32_t Delay);

_Bool Btn_Pressed();

enum ButtonState Get_Button_State();

void Animation(uint32_t over);
