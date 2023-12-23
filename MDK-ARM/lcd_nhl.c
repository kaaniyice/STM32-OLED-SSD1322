#include "lcd_nhl.h"
#include "SPI.h"


void lcd_send_cmd (char cmd) 
{
		// Send cmd mode (3 wire)
		CS2_RESET();  // CS RESET
		GPIOB->ODR &= ~(1<<5); // DC RESET COMMAND
		HAL_SPI_Transmit(&hspi2,(uint8_t *)&cmd,1,100);
		// spi_transmit((uint8_t *)&cmd,8);
		CS2_SET();  // CS SET
	
	
}	
void lcd_send_data (char data) 
{
		// Send data mode (3 wire)
		CS2_RESET();   // CS RESET
		GPIOB->ODR |= (1<<5); // DC SET DATA

		HAL_SPI_Transmit(&hspi2,(uint8_t *)&data,sizeof(data),100);

		CS2_SET();  // CS SET
}

void Set_Column_Address_12864(unsigned char a, unsigned char b)
{
  lcd_send_cmd(0x15);  // Set Column Address
  lcd_send_data(a+28);        //   Default => 0x00
  lcd_send_data(b);        //   Default => 0x77
}
void Set_Row_Address_12864(unsigned char a, unsigned char b)
{
  lcd_send_cmd(0x75);  // Set Row Start and End Address
  lcd_send_data(a);        // Default => 0x00
  lcd_send_data(b);        // Default => 0x7F
}
void home()
{
	Set_Row_Address_12864(0x00, 0x77);  // 77 = 119
	Set_Column_Address_12864(0x00, 0x3F );  //3F = 63
		
}
void Set_Write_RAM_12864()
{
  lcd_send_cmd(0x5C);  // Enable MCU to Write DATA RAM
}
//--------------------------------------------------------------------------

void Set_Read_RAM_12864()
{
  lcd_send_cmd(0x5D);  // Enable MCU to Read DATA RAM
}
void NHD12864WDY3_Init(void){

GPIOB->ODR &= ~(1<<3);  //pull /RES (pin D3) low
HAL_Delay(1); //keep /RES low for minimum 200µs
GPIOB->ODR |= (1<<3);   //pull /RES (pin D3) high
HAL_Delay(1); //wait minimum 200µs before sending commands
lcd_send_cmd(0xAE); //display OFF SLEEP MODE
lcd_send_cmd(0xB3); //set CLK div. & OSC freq.
lcd_send_data(0x91);
lcd_send_cmd(0xCA); //set MUX ratio+
lcd_send_data(0x3F);
lcd_send_cmd(0xA2); //set offset +
lcd_send_data(0x00);
lcd_send_cmd(0xAB); //function selection
lcd_send_data(0x01);
lcd_send_cmd(0xA0); //set re-map
lcd_send_data(0x16);
lcd_send_data(0x11);
lcd_send_cmd(0xC7); //master contrast current+
lcd_send_data(0x0F);
lcd_send_cmd(0xC1); //set contrast current+
lcd_send_data(0x9F);
lcd_send_cmd(0xB1); //set phase length
lcd_send_data(0xF2);
lcd_send_cmd(0xBB); //set pre-charge voltage
lcd_send_data(0x1F);
lcd_send_cmd(0xB4); //set VSL
lcd_send_data(0xA0);
lcd_send_data(0xFD);
lcd_send_cmd(0xBE); //set VCOMH
lcd_send_data(0x04);

lcd_send_cmd(0xA6); //set display mode
lcd_send_cmd(0xAF); //display ON SLEEP MODE
}

void FillPixel_12864()    
{
  unsigned int i, j;
  Set_Read_RAM_12864();
  Set_Column_Address_12864(0x00 ,0x5D); //1C(28) & 5B(91) = DISPLAY Start & End address.
  Set_Row_Address_12864(0,0x3F);
	Set_Write_RAM_12864();
	for(i=0;i<4092;i++)   //Columns
  {
		lcd_send_data(0xff);
		
		lcd_send_data(0xff);
  }
}
void ClearPixel_12864()
{
  unsigned int i;
  Set_Column_Address_12864(0x00,0x5B);
  Set_Row_Address_12864(0x00,0x3F);
  Set_Write_RAM_12864();

	for(i=0;i<4100;i++)   //Columns
  {
	lcd_send_data(0x00);
	lcd_send_data(0x00);
	
  }
}
void Set_Column_Normal(unsigned char a, unsigned char b)
{
	lcd_send_cmd(0x15);  // Set Column Address
  lcd_send_data(a);        //   Default => 0x00
  lcd_send_data(b);
}
void Clear_text_Back(uint8_t x,uint8_t y)
{
	Set_Column_Normal((x/2+27),(x/2+27)); // 1 width
  Set_Row_Address_12864(y,y+9); // length
  Set_Write_RAM_12864();

	for(uint16_t i=0;i<10;i++)   //Columns
  {
	lcd_send_data(0x00);
	lcd_send_data(0x00);
	
  }
	Set_Column_Normal(91,91); // last column error
	Set_Row_Address_12864(y,y+12);
	Set_Write_RAM_12864();
	for(uint16_t i=0;i<10;i++)
	{
	lcd_send_data(0x00);
	lcd_send_data(0x00);}
}

void set_cursor (unsigned int x_pos,unsigned int y_pos)
{
		
    // Set the column address
		lcd_send_cmd(0x15);  // Set Column Address
		lcd_send_data((x_pos/2)+28);        //   Default => 0x00
		lcd_send_data(y_pos);        //   Default => 0x77
    
    // Set the row address
    Set_Row_Address_12864(y_pos,0x3F);
}
