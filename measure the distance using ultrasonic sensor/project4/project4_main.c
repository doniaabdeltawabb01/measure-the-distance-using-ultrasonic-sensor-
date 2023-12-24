#include"lcd.h"
#include"ultrasonic.h"
#include<avr/io.h>
#include<util/delay.h>
//prototype
void display(uint16 distance);

int main(){
	//variables
	uint16 distance=0;
	SREG |= (1<<7);//enable the interrupt
	//Initialize
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=     cm");

	while(1){
		 distance=Ultrasonic_readDistance();
		 display(distance);
		 _delay_ms(1);
	}
}
//display function
void display(uint16 distance){
	LCD_moveCursor(0,10);
	if(distance >= 100)
	{
		LCD_intgerToString(distance);
	}
	else
	{

		LCD_intgerToString(distance);
		/* In case the digital value is two or one digits print space in the next digit place */
		LCD_displayCharacter(' ');
	}

}
