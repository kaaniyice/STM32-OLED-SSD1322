#ifndef SPI_H_
#define SPI_H_
#include "stm32f0xx_hal.h"
#include "string.h"
#include "stdio.h"
#include "main.h"

extern SPI_HandleTypeDef hspi1;
extern SPI_HandleTypeDef hspi2;
void MX_SPI1_Init(void);
void MX_SPI2_Init(void);
void CS1_SET(void);
void CS1_RESET(void);
void CS2_SET(void);
void CS2_RESET(void);


#endif /* SPI_H_ */