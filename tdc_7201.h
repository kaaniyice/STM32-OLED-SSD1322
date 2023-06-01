#ifndef tdc_7201_H_
#define tdc_7201_H_

#include "stm32f0xx_hal.h"
#include "main.h"

#define TDC_CLK   8   //////////// 1- 8 - 16  // NOM 8
#define FILT_SIZE 64 // FILT_SIZE will provide more smoothing, but may also introduce more lag in the filtered measurements.
void trigger(void);
void finish(void);
double tof(void);
uint32_t read3(uint8_t reg_add);
void writeRegister(uint8_t reg_add, uint8_t data);
uint8_t readRegister(uint8_t reg_add);





enum reg_list
{																//reg address
  TDCx_CONFIG1=0x00,  							//00h
  TDCx_CONFIG2=0x01,								//01h
  TDCx_INT_STATUS=0x02,							//02h
  TDCx_INT_MASK=0x03,								//03h
  TDCx_COARSE_CNTR_OVF_H=0x04,			//04h
  TDCx_COARSE_CNTR_OVF_L=0x05,			//05h
  TDCx_CLOCK_CNTR_OVF_H=0x06,				//06h	
  TDCx_CLOCK_CNTR_OVF_L=0x07,				//07h
  TDCx_CLOCK_CNTR_STOP_MASK_H=0x08,	//08h
  TDCx_CLOCK_CNTR_STOP_MASK_L=0x09,	//09h
  TDCx_TIME1=0x10,				    			//10h
  TDCx_CLOCK_COUNT1=0x11,						//11h
  TDCx_TIME2=0x12,									//12h
  TDCx_CLOCK_COUNT2=0x13,						//13h
  TDCx_TIME3=0x14,									//14h
  TDCx_CLOCK_COUNT3=0x15,						//15h
  TDCx_TIME4=0x16,									//16h
  TDCx_CLOCK_COUNT4=0x17,						//17h
  TDCx_TIME5=0x18,									//18h
  TDCx_CLOCK_COUNT5=0x19,						//19h
  TDCx_TIME6=0x1A,									//1Ah
  TDCx_CALIBRATION1=0x1B,						//1Bh
  TDCx_CALIBRATION2=0x1C						//1Ch
};
enum states
{
  START,
  MEASURE
};


#endif /* tdc_7201_H_ */