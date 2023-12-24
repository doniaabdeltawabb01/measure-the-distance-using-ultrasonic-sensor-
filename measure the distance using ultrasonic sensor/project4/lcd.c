#include"lcd.h"
#include<util/delay.h>
#include"gpio.h"
#include "common_macros.h" /* For GET_BIT Macro */

void LCD_init(void){
	GPIO_setupPinDirection(RS_PORT,RS_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(E_PORT,E_PIN,PIN_OUTPUT);
	_delay_ms(20);
#if(DATA_MODE==4)
	GPIO_setupPinDirection(DB_PORT,DB4_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DB_PORT,DB5_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DB_PORT,DB6_PIN,PIN_OUTPUT);
	GPIO_setupPinDirection(DB_PORT,DB7_PIN,PIN_OUTPUT);
	_delay_ms(20);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT1);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE_INIT2);
	LCD_SendCommand(LCD_TWO_LINES_FOUR_BITS_MODE);
#elif(DATA_MODE==8)
	GPIO_setupPortDirection(DB_PORT,PORT_OUTPUT);
	_delay_ms(20);
	LCD_SendCommand(LCD_TWO_LINES_EIGHT_BITS_MODE);

#endif
	LCD_SendCommand(LCD_CURSOR_OFF);
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}
void LCD_SendCommand(uint8 command){

	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);
#if(DATA_MODE==4)
	GPIO_writePin(DB_PORT,DB4_PIN,GET_BIT(command,4));
	GPIO_writePin(DB_PORT,DB5_PIN,GET_BIT(command,5));
	GPIO_writePin(DB_PORT,DB6_PIN,GET_BIT(command,6));
	GPIO_writePin(DB_PORT,DB7_PIN,GET_BIT(command,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DB_PORT,DB4_PIN,GET_BIT(command,0));
	GPIO_writePin(DB_PORT,DB5_PIN,GET_BIT(command,1));
	GPIO_writePin(DB_PORT,DB6_PIN,GET_BIT(command,2));
	GPIO_writePin(DB_PORT,DB7_PIN,GET_BIT(command,3));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
#elif(DATA_MODE==8)
	GPIO_writePort(DB_PORT,command);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
#endif
}
void LCD_displayCharacter(uint8 character){
	GPIO_writePin(RS_PORT,RS_PIN,LOGIC_HIGH);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);
#if(DATA_MODE==4)
	GPIO_writePin(DB_PORT,DB4_PIN,GET_BIT(character,4));
	GPIO_writePin(DB_PORT,DB5_PIN,GET_BIT(character,5));
	GPIO_writePin(DB_PORT,DB6_PIN,GET_BIT(character,6));
	GPIO_writePin(DB_PORT,DB7_PIN,GET_BIT(character,7));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_HIGH);
	_delay_ms(1);

	GPIO_writePin(DB_PORT,DB4_PIN,GET_BIT(character,0));
	GPIO_writePin(DB_PORT,DB5_PIN,GET_BIT(character,1));
	GPIO_writePin(DB_PORT,DB6_PIN,GET_BIT(character,2));
	GPIO_writePin(DB_PORT,DB7_PIN,GET_BIT(character,3));

	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
#elif(DATA_MODE==8)
	GPIO_writePort(DB_PORT,character);
	_delay_ms(1);
	GPIO_writePin(E_PORT,E_PIN,LOGIC_LOW);
	_delay_ms(1);
#endif
}

void LCD_displayString(uint8 *str){
	while(*str!='\0'){
		LCD_displayCharacter(*str++);

	}
}
void LCD_moveCursor(uint8 row,uint8 col){
	uint8 location;
	switch(row){
	case 0:
		location=col;
		break;
	case 1:
		location=col+0x40;
		break;
	case 2:
		location=col+0x10;
		break;
	case 3:
		location=col+0x50;
		break;
	}
	LCD_SendCommand(location|LCD_SET_CURSOR_LOCATION);
}
void LCD_displayStringRowColumn(uint8 row,uint8 col,const char *str){
	LCD_moveCursor(row,col);
	LCD_displayString(str);
}
void LCD_intgerToString(int data){
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}
void LCD_clearScreen(void){
	LCD_SendCommand(LCD_CLEAR_COMMAND);
}

