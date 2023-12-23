#include "tdc_7201.h"
#include "SPI.h"
#include "main.h"



uint8_t readRegister(uint8_t reg_add) 
{
  uint8_t read_data = 0;
  uint8_t write_data = reg_add;

  CS1_RESET(); // CS TDC RESET
  HAL_SPI_Transmit(&hspi1, &write_data, sizeof(write_data), HAL_MAX_DELAY);
  HAL_SPI_Receive(&hspi1, &read_data, sizeof(read_data), HAL_MAX_DELAY);
  CS1_SET();   // CS TDC SET

  return read_data;
}

void writeRegister(uint8_t reg_add, uint8_t data) 
{
  uint8_t write_data[2] = {0};

  write_data[0] = (1<<6) | reg_add; // auto Increment off // write address on
  write_data[1] = data; // 2nd byte = data

	CS1_RESET();  // CS TDC RESET
  HAL_SPI_Transmit(&hspi2, write_data, sizeof(write_data), HAL_MAX_DELAY);
  CS1_SET();  // CS TDC SET
}

uint32_t read3(uint8_t reg_add)
{
  uint8_t write_data = reg_add;
  uint32_t read_data = 0;

  CS1_RESET(); // CS TDC RESET
  HAL_SPI_Transmit(&hspi2, &write_data, sizeof(write_data), HAL_MAX_DELAY);
  read_data |= (uint32_t)HAL_SPI_Receive(&hspi1, &read_data, sizeof(read_data), HAL_MAX_DELAY) << 16;
  read_data |= (uint32_t)HAL_SPI_Receive(&hspi1, &read_data, sizeof(read_data), HAL_MAX_DELAY) << 8;
  read_data |= (uint32_t)HAL_SPI_Receive(&hspi1, &read_data, sizeof(read_data), HAL_MAX_DELAY);
	CS1_SET();   // CS TDC SET

  return read_data;
}



double tof(void) // DATASHEET 7.4.2.1.1
{
  double tofn = (double)read3(TDCx_CALIBRATION2); // CALIBRATION 2
  tofn -= (double)read3(TDCx_CALIBRATION1); // CALIBRATION 1  //( CAL2 - CAL1)
  tofn /= (10.0 - 1.0); // CALIBRATION2_PERIODS - 1  // CALIBRATION2_PERIODS = TDCx_CONFIG2 second cycle(default 10)  // CALL COUNT
  tofn = (1000.0 / TDC_CLK) / tofn; // CLOCK PERIOD /  CALL COUNT 
  tofn *= (double)read3(TDCx_TIME1); // NORM LSB * TIMEn == TOFn
  return tofn; // TOFn
}

// 7.6.2 FOR STARTING MEASUREMENTS writeRegister(TDCx_CONFIG1, 0x01); << first bit to 1 is initialize [2:1] 00 = mode 1, S3= rising edge
//4= stop edge  5= trigg edge, 6 = PARITY_EN, 7 = FORCE_CALL  
