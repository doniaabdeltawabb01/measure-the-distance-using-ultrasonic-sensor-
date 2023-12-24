#include"std_types.h"
#include"gpio.h"
//defines
#define ULTRASONIC_TRIGGER_PORT         PORTB_ID
#define ULTRASONIC_TRIGGER_PIN          PIN5_ID
//Prtotypes
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

