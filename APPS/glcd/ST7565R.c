/**
 * \file ST7565R.c
 * \brief Functions relating to ST7565R.
 * \author Andy Gock
 * \see glcd.h
 */ 

#include "stm32f1xx_hal.h"

#include "glcd.h"
#include "ST7565R.h"
#include "main.h"
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void glcd_init(void)
{

	/* Initialization of glcd module
	 * it can be work in 2ways:
	 * 	1. GPIO mode <---we use this method,
	 * 	2. SPI mode
	 * 	TODO: change to the SPI mode
	 * 	*/

	/* Send reset pulse to LCD */
	glcd_reset();
	HAL_Delay(GLCD_RESET_TIME);

	/*
	 * send HW-base commands
	 * in this place we can add some other LCD module
	 *  */
	glcd_ST7565R_init();

	/* Set all dots black and hold for 1s, then clear it, we do this so we can visually check init sequence is working */
	glcd_all_on();
	HAL_Delay(1000);
	glcd_normal();

	glcd_set_start_line(0);
	glcd_clear_now();

	glcd_select_buffer(glcd_buffer);
	glcd_clear();

}

/*
 * this is the write to glcd HW
 * it uses the GPIO mode but
 * TODO: change to the SPI mode
 * */
void glcd_spi_write(uint8_t c)
{
	 int8_t i;
	  for (i=7; i>=0; i--) {
			HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_RESET);

	    //SCLK_PORT &= ~_BV(SCLK);
	    if (c & (1<<i))
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_SET);

	      //SID_PORT |= _BV(SID);
	    else
			HAL_GPIO_WritePin(LCD_DATA_GPIO_Port, LCD_DATA_Pin, GPIO_PIN_RESET);

	      //SID_PORT &= ~_BV(SID);

		HAL_GPIO_WritePin(LCD_SCK_GPIO_Port, LCD_SCK_Pin, GPIO_PIN_SET);

	    //SCLK_PORT |= _BV(SCLK);
	  }
}


/*
 * this is the hard reset of glcd
 * use of low signal on reset pin of glcd
 * */
void glcd_reset(void)
{
	GLCD_SELECT();
	GLCD_RESET_LOW();
	HAL_Delay(GLCD_RESET_TIME);
	GLCD_RESET_HIGH();
	GLCD_DESELECT();
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void glcd_command(uint8_t c)
{
	GLCD_A0_LOW();
	glcd_spi_write(c);	
}

void glcd_data(uint8_t c)
{
	GLCD_A0_HIGH();
	glcd_spi_write(c);	
}

void glcd_set_contrast(uint8_t val) {
	/* Can set a 6-bit value (0 to 63)  */

	/* Must send this command byte before setting the contrast */
	glcd_command(ST7565_LCD_CMD_SET_VOLUME_FIRST);
	
	/* Set the contrat value ("electronic volumne register") */
	if (val > 63) {
		glcd_command(63);
	} else {
		glcd_command(val);
	}
	return;
}

void glcd_power_down(void)
{
	/* Command sequence as in ST7565 datasheet */
	glcd_command(ST7565_LCD_CMD_SET_STATIC_OFF);	// Static indicator off
	glcd_command(ST7565_LCD_CMD_SET_STATIC_REG);	// Static indicator register, not blinking
	glcd_command(ST7565_LCD_CMD_DISPLAY_OFF); // Display OFF
	glcd_command(ST7565_LCD_CMD_SET_ALLPTS_ON); // Display all points ON

	/* Display is now in sleep mode */
}

void glcd_power_up(void)
{
	glcd_command(ST7565_LCD_CMD_SET_ALLPTS_NORMAL); // Display all points OFF
	glcd_command(ST7565_LCD_CMD_SET_STATIC_ON);	// Static indicator ON
	glcd_command(ST7565_LCD_CMD_SET_STATIC_REG);	// Static indicator register, not Blinking
	glcd_command(ST7565_LCD_CMD_DISPLAY_ON);

	return;
}

void glcd_set_y_address(uint8_t y)
{
	glcd_command(ST7565_LCD_CMD_SET_PAGE | (0x0F & y)); /* 0x0F = 0b00001111 */
}

void glcd_set_x_address(uint8_t x)
{
	//glcd_set_column_upper(x);
	glcd_command(ST7565_LCD_CMD_SET_COLUMN_UPPER | (x >> 4));
	//glcd_set_column_lower(x);
	glcd_command(/*ST7565_LCD_CMD_SET_COLUMN_LOWER |*/ (0x0f & x));

}

void glcd_all_on(void)
{
	glcd_command(ST7565_LCD_CMD_DISPLAY_ON);
}

void glcd_normal(void)
{
	glcd_command(ST7565_LCD_CMD_SET_ADC_NORMAL);
}

void glcd_set_column_upper(uint8_t addr)
{
	glcd_command(ST7565_LCD_CMD_SET_COLUMN_UPPER | (addr >> 4));
}

void glcd_set_column_lower(uint8_t addr)
{
	glcd_command(ST7565_LCD_CMD_SET_COLUMN_LOWER | (0x0f & addr));
}

void glcd_set_start_line(uint8_t addr)
{
	glcd_command( ST7565_LCD_CMD_SET_DISP_START_LINE | (0x3F & addr)); /* 0x3F == 0b00111111 */
}

/** Clear the display immediately, does not buffer */
void glcd_clear_now(void)
{
	uint8_t page;
	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
		uint8_t col;
		glcd_set_y_address(page);
		glcd_set_x_address(0);
		for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
			glcd_data(0);
		}			
	}
}

void glcd_pattern(void)
{
	uint8_t page;
	for (page = 0; page < GLCD_NUMBER_OF_BANKS; page++) {
		uint8_t col;
		glcd_set_y_address(page);
		glcd_set_x_address(0);
		for (col = 0; col < GLCD_NUMBER_OF_COLS; col++) {
			glcd_data( (col / 8 + 2) % 2 == 1 ? 0xff : 0x00 );
		}			
	}
}

void glcd_write()
{

	uint8_t bank;

	for (bank = 0; bank < GLCD_NUMBER_OF_BANKS; bank++) {
		// Each bank is a single row 8 bits tall /
		uint8_t column;		
		
		if (glcd_bbox.y_min >= (bank+1)*8) {
			continue; // Skip the entire bank /
		}
		
		if (glcd_bbox.y_max < bank*8) {
			break;    // No more banks need updating /
		}
		
		glcd_set_y_address(bank);
		glcd_set_x_address(glcd_bbox.x_min);

		for (column = glcd_bbox.x_min; column <= glcd_bbox.x_max; column++)
		{
			glcd_data( glcd_buffer_selected[GLCD_NUMBER_OF_COLS * bank + column] );
		}
	}

	glcd_reset_bbox();

}

//#define GLCD_INIT_NHD_C12832A1Z_FSW_FBW_3V3
//#define GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT
//#define GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M
//#define GLCD_INIT_ZOLEN_12864_FFSSWE_NAA
#define GLCD_INIT_UC1705

void glcd_ST7565R_init(void) {
	
#if defined(GLCD_INIT_NHD_C12832A1Z_FSW_FBW_3V3)

	/* Init sequence based on datasheet example code for NHD-C12832A1Z-FSW-FBW-3V3 */
	/* Datasheet says max SCK frequency 20MHz for this LCD */
	/* We use "reverse direction" for common output mode, as opposed to datasheet specifying "normal direction" */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x21); /* Internal resistor ratio, set to: 1 */
	glcd_set_contrast(40); /* Set contrast, value experimentally determined, can set to 6-bit value, 0 to 63 */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT)

	/* Init sequence based on datasheet example code for NHD-C12864A1Z-FSW-FBW-HTT */
	/* Datasheet says max SCK frequency 2.5MHz for this LCD */
	/* We use "reverse direction" for common output mode, as opposed to datasheet specifying "normal direction" */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x26); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(20); /* Set contrast, value experimentally determined */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_NHD_C12864WC_FSW_FBW_3V3_M)

	/* Init sequence for NHD-C12864WC-FSW-FBW-3V3-M */

	glcd_command(ST7565R_RESET); /* Internal reset */
	glcd_command(0xa2); /* 1/9 bias */
	glcd_command(0xa0); /* ADC select, normal */
	glcd_command(0xc8); /* Com output reverse */
	glcd_command(0xa4); /* Display all points normal */
	glcd_command(0x40); /* Display start line set */
	glcd_command(0x25); /* Internal resistor ratio */
	glcd_set_contrast(45); /* Set contrast value, experimentally determined, value 0 to 63 */
	glcd_command(0x2f); /* Power controller set */
	glcd_command(0xaf); /* Display on */
	
#elif defined(GLCD_INIT_ZOLEN_12864_FFSSWE_NAA)
	/* Init sequence for Zolen 128x64 module with
	 * size 40x35mm. Chip ST7567 */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa3); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x26); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(35); /* Set contrast, value experimentally determined, value 0 to 63 */
	glcd_command(0xaf); /* Display on */

#elif defined(GLCD_INIT_UC1705)
	/* Init sequence based on datasheet example code for UC1705 */

	glcd_command(ST7565_LCD_CMD_SET_ADC_NORMAL); /* ADC select in normal mode */
	glcd_command(ST7565_LCD_CMD_DISPLAY_OFF); /* Display OFF */
	glcd_command(ST7565_LCD_CMD_SET_COM_REVERSE); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(ST7565_LCD_CMD_SET_BIAS_9); /* LCD bias set at 1/9 */
	glcd_command(ST7565_LCD_CMD_SET_POWER_CONTROL | 0x7); /* Power control set to operating mode: 7 */
	glcd_command(ST7565_LCD_CMD_SET_RESISTOR_RATIO | 0x4); /* Internal resistor ratio, set to: 1 */
	glcd_command(ST7565_LCD_CMD_SET_VOLUME_FIRST); /* Set contrast, value experimentally determined, can set to 6-bit value, 0 to 63 */
	glcd_command(ST7565_LCD_CMD_SET_VOLUME_SECOND); /* Set contrast, value experimentally determined, can set to 6-bit value, 0 to 63 */
	glcd_command(ST7565_LCD_CMD_DISPLAY_ON); /* Display on */

#else

	/* Default init sequence */
	/* Currently just set the same as GLCD_INIT_NHD_C12864A1Z_FSW_FBW_HTT */

	glcd_command(0xa0); /* ADC select in normal mode */
	glcd_command(0xae); /* Display OFF */
	glcd_command(0xc8); /* Common output mode select: reverse direction (last 3 bits are ignored) */
	glcd_command(0xa2); /* LCD bias set at 1/9 */
	glcd_command(0x2f); /* Power control set to operating mode: 7 */
	glcd_command(0x26); /* Internal resistor ratio, set to: 6 */
	glcd_set_contrast(20); /* Set contrast, value experimentally determined, value 0 to 63 */
	glcd_command(0xaf); /* Display on */

#endif

}
