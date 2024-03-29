#include "lcd_nhl.h"
#include "fonts_ai.h"


void write_pixel(int x, int y)
{	
	// set the cursor for desired pixel
	set_cursor(x,y);
	Set_Write_RAM_12864();
	// if divided by 2 write ff 00
	if (x % 2 == 0  )
	{
		lcd_send_data(0xff);
		lcd_send_data(0x00);
	}

	// 
	else {lcd_send_data(0x00);lcd_send_data(0xff);}

}



void write_char( uint16_t x, uint16_t y,char c) {
		// get the char index according to ASCI TABLE
    uint8_t char_index = c - 0x20; // c - 32
		// get the font width and height
    uint8_t char_width = FONT_WIDTH; // 8
		uint8_t char_height = FONT_HEIGHT; // 12
    uint8_t char_data[char_width];
		uint8_t xpos;
		uint8_t x2pos;
	// look char data
  
    
    // write each char 
    for (uint8_t i = 0; i < char_height; i++) { // 12
			// get the row data 
			uint8_t row_data = font[char_index][i];
			// go to each row data and determine to send FF or 00
			for (uint8_t j = 0; j < char_width ; j+=2) { // 8
					uint8_t xpos = row_data & (1 << (7-j)); // 1 or 0  // 0 2 4 6
					uint8_t x2pos = row_data & (1 << (6-j)); // 1 or 0 // 1 3 5 7
					set_cursor(x+j,y+i);
					Set_Write_RAM_12864();
				// for position send FF for which led's to light
					if (xpos && x2pos) {
							lcd_send_data(0xFF);
							lcd_send_data(0xFF);
					} else if (xpos && !x2pos) {
							lcd_send_data(0xFF);
							lcd_send_data(0x00);
					} else if (!xpos && x2pos) {
							lcd_send_data(0x00);
							lcd_send_data(0xFF);
					} else {
							lcd_send_data(0x00);
							lcd_send_data(0x00);
					}
			}
}
}


void write_text(uint8_t x, uint8_t y, char* str)
{
    uint8_t i = 0;
		uint8_t r = 0;
    uint8_t cursor_x = x;
    uint8_t cursor_y = y;
    
    // Loop each char
    while (str[i] != '\0') {
        // can it fit width?
        if (cursor_x + FONT_WIDTH <= SCREEN_WIDTH) {
            write_char(cursor_x, cursor_y, str[i]);
            cursor_x += FONT_WIDTH;
        }
        else {
            // next line
						r=+x;
            cursor_x = 0;
            cursor_y += FONT_HEIGHT;
						
            // Is there enough space
            if (cursor_y + FONT_HEIGHT > SCREEN_HEIGHT) {
                // no space exit
                break;
            }
            // if not write char
            write_char(cursor_x, cursor_y, str[i]);
            cursor_x += FONT_WIDTH;
        }
        //go to next char
        i++;
			
    }
			Clear_text_Back(x,y); // BACK CLEAR FUNCT
}
