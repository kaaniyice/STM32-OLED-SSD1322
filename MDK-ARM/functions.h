#ifndef functions_H_
#define functions_H_

#include "stm32f0xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

void write_pixel(int x, int y);
void write_char(uint16_t x, uint16_t y,char c);
void write_text(uint8_t x, uint8_t y, char* str);


#endif /* functions_H_ */