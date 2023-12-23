#ifndef LCD_nhl_H_
#define LCD_nhl_H_

#include "stm32f0xx_hal.h"
#include "main.h"


#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64



	void Set_Column_Address_12864(unsigned char a, unsigned char b);
	void Set_Column_Normal(unsigned char a, unsigned char b);
	void Set_Row_Address_12864(unsigned char a, unsigned char b);
	void lcd_send_cmd (char cmd);
	void lcd_send_data (char data);
	void Set_Write_RAM_12864();
	void Set_Read_RAM_12864();
	void FillPixel_12864();
	void ClearPixel_12864();
	void Clear_text_Back(uint8_t x,uint8_t y);
	void set_cursor (unsigned int x_pos,unsigned int y_pos);
	void home();
	void NHD12864WDY3_Init(void);
	//uint8_t get_value_2pixel(unsigned int x_p,unsigned int y_p);
	//uint8_t glcd_read_current_data();


#endif /* LCD_nhl_H_ */