/*
 * lcd.h
 *
 *  Created on: Oct 3, 2023
 *      Author: Donia
 */

#ifndef LCD_H_
#define LCD_H_

#include"std_types.h"

#define DATA_MODE  8
#if(DATA_MODE!=8&&DATA_MODE!=4)
#error "The number of bits must be 4 or 8"
#endif

#define RS_PORT    PORTB_ID
#define RS_PIN     PIN0_ID



#define E_PORT    PORTB_ID
#define E_PIN     PIN1_ID
#define DB_PORT   PORTA_ID

#if(DATA_MODE==4)
#define DB4_PIN     PIN3_ID
#define DB5_PIN     PIN4_ID
#define DB6_PIN     PIN5_ID
#define DB7_PIN     PIN6_ID
#endif
/*lcd defines*/
#define LCD_CLEAR_COMMAND              0x01
#define LCD_GO_TO_HOME                 0x02
#define LCD_TWO_LINES_EIGHT_BITS_MODE  0x38
#define LCD_TWO_LINES_FOUR_BITS_MODE   0x28
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT1   0x33
#define LCD_TWO_LINES_FOUR_BITS_MODE_INIT2   0x32
#define LCD_CURSOR_OFF                 0x0C
#define LCD_CURSOR_ON                  0x0E
#define LCD_SET_CURSOR_LOCATION        0x80

/*functions prototype*/
void LCD_SendCommand(uint8 command);
void LCD_displayCharacter(uint8 character);
void LCD_init(void);
void LCD_displayString(uint8 *str);
void LCD_moveCursor(uint8 row,uint8 col);
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str);
void LCD_clearScreen(void);
void LCD_intgerToString(int data);
#endif /* LCD_H_ */
