#include"ultrasonic.h"
#include"icu.h"
#include<util/delay.h>

//Global variables
uint8 g_edgeCount = 0;
uint16 g_timeHigh = 0;

void Ultrasonic_init(void){
	ICU_ConfigType ICU_Configurations = {F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	//set the trigger port as output
	GPIO_setupPinDirection(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,PIN_OUTPUT);
}

void Ultrasonic_Trigger(void){
	//to trigger the pin send logic high then delay 1 us then send logic low
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(ULTRASONIC_TRIGGER_PORT,ULTRASONIC_TRIGGER_PIN,LOGIC_LOW);
}
uint16 Ultrasonic_readDistance(void){
	uint16 distance=0;
	Ultrasonic_Trigger();

		distance=g_timeHigh/58.8;

	return distance;
}
//call back function
void Ultrasonic_edgeProcessing(void){
	g_edgeCount++;
		if(g_edgeCount == 1)
		{
			/*
			 * Clear the timer counter register to start measurements from the
			 * first detected rising edge
			 */
			ICU_clearTimerValue();
			/* Detect falling edge */
			ICU_setEdgeDetectionType(FALLING);
		}
		else if(g_edgeCount == 2)
		{
			/* Store the High time value */
			g_timeHigh = ICU_getInputCaptureValue();
			g_edgeCount =0;

			/* Detect rising edge */
			ICU_setEdgeDetectionType(RAISING);
		}
}
