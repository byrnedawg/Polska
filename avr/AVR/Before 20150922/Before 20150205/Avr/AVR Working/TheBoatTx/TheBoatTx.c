// Place any #define statements here before you include ANY other files

// data buffer defines.
#define UART_TX_BUFFER_SIZE 52
#define UART_RX_BUFFER_SIZE 52

#define    SYNC_PACKET		        0x53
#define    END_PACKET		        0x54
#define    PS2_B_BTN_SELECT         0x00
#define    PS2_B_BTN_L3             0x01
#define    PS2_B_BTN_R3             0x02
#define    PS2_B_BTN_START          0x03
#define    PS2_B_DPAD_UP            0x04
#define    PS2_B_DPAD_RIGHT         0x05
#define    PS2_B_DPAD_DOWN          0x06
#define    PS2_B_DPAD_LEFT          0x07
#define    PS2_B_BTN_L2             0x08
#define    PS2_B_BTN_R2             0x09
#define    PS2_B_BTN_L1             0x0A
#define    PS2_B_BTN_R1             0x0B
#define    PS2_B_BTN_TRIANGLE       0x0C
#define    PS2_B_BTN_CIRCLE         0x0D
#define    PS2_B_BTN_X              0x0E
#define    PS2_B_BTN_SQUARE         0x0F
#define	   PS2_B_BTN_NOT			0xBD

/***********************************************************************************/
// You must ALWAYS specify the board you are using
// These are all in the 'sys' folder e.g.
#include "sys/atmega168.h" // I am using an Axon
// Now include any other files that are needed here
#include "uart.h"
#include "servos.h"
#include "rprintf.h"
#include "led.h"
#include "iopin.h"
#include "spisw.h"
#include "Controller/Sony/ps2.h"
#include "pwm.h"
#include "motorPWM.h"

// non WebbotLib includes:
//#include <avr/interrupt.h>            // needed because WebbotLib does not handle interrupts on INT[0-7] yet.
//#include <avr/wdt.h>                // haven't made use of this yet.
/***********************************************************************************/
// Now create any global variables such as motors, servos, sensors etc
// define variables

char left_x = 0;
char left_y = 0;
char right_x = 0;
char right_y = 0;
char xButton_pressure = 0;
char SqButton_pressure = 0;
char DL_Button_pressure = 0;
char DR_Button_pressure = 0;
char PS2_SELECT = PS2_B_BTN_NOT;
char PS2_L3 = PS2_B_BTN_NOT;
char PS2_R3 = PS2_B_BTN_NOT;
char PS2_START = PS2_B_BTN_NOT;
char PS2_UP = PS2_B_BTN_NOT;
char PS2_RIGHT = PS2_B_BTN_NOT;
char PS2_LEFT = PS2_B_BTN_NOT;
char PS2_DOWN = PS2_B_BTN_NOT;
char PS2_L2 = PS2_B_BTN_NOT;
char PS2_R2 = PS2_B_BTN_NOT;
char PS2_L1 = PS2_B_BTN_NOT;
char PS2_R1 = PS2_B_BTN_NOT;
char PS2_TRIANGLE = PS2_B_BTN_NOT;
char PS2_CIRCLE = PS2_B_BTN_NOT;
char PS2_X = PS2_B_BTN_NOT;
char PS2_SQUARE = PS2_B_BTN_NOT;
    
uint8_t i = 0;
uint8_t buttonPressed[0xFF];        // used to count how many frames button has been pressed for.
uint8_t buttonReleased[0xFF];        // contains how many frames button was held down for. used to de-bounce buttons
uint8_t SpotLightState = 0;

// Create a controller SELECTed using D6
SONY_PS2 controller1 = MAKE_SONY_PS2(D4);
// Create a list of devices on the SPI bus
static SPI_DEVICE_LIST spiBus_list[] = {&controller1._device_};
// Create a software SPI Bus using:-
// D5 = MOSI, D3=MISO, D2=Clock
SPI_SW spiBus = MAKE_SW_SPI(spiBus_list,D3,D2,D5);

// LEDS
LED RightRed = MAKE_LED(D7,FALSE);
LED LeftRed = MAKE_LED(B0,FALSE);
LED SpotLightWhite = MAKE_LED(B1,FALSE);
LED PowerGreen = MAKE_LED(B2,FALSE);

void SendData()
{
	rprintfChar(SYNC_PACKET);
	rprintfChar(right_x);
	rprintfChar(right_y);
	rprintfChar(left_x);
	rprintfChar(left_y);
	rprintfChar(PS2_SELECT);        
	rprintfChar(PS2_L3);           
	rprintfChar(PS2_R3);             
	rprintfChar(PS2_START);          
	rprintfChar(PS2_UP);            
	rprintfChar(PS2_RIGHT);
	rprintfChar(DR_Button_pressure);         
	rprintfChar(PS2_DOWN);          
	rprintfChar(PS2_LEFT);
	rprintfChar(DL_Button_pressure);          
	rprintfChar(PS2_L2);            
	rprintfChar(PS2_R2);             
	rprintfChar(PS2_L1);             
	rprintfChar(PS2_R1);             
	rprintfChar(PS2_TRIANGLE);       
	rprintfChar(PS2_CIRCLE);         
	rprintfChar(PS2_X);              
	rprintfChar(xButton_pressure);
	rprintfChar(PS2_SQUARE); 
	rprintfChar(SqButton_pressure);                  
	rprintfChar(END_PACKET);
}

/***********************************************************************************/
// This routine is called once only and allows you to do set up the hardware
// Dont use any 'clock' functions here - use 'delay' functions instead

void appInitHardware(void){
// Initialize the servo controller

// Initialize the SPI bus
spiBusInit(&spiBus,true);


//servosInit(&bank1, TIMER1);
// Set UART0 to 9600 baud
uartInit(UART0, 9600);
// Tell rprintf to output to UART0
rprintfInit(&uart0SendByte);

}
/***********************************************************************************/
// This routine is called once to allow you to set up any other variables in your
//program
// You can use 'clock' function here.
// The loopStart parameter has the current clock value in �S
TICK_COUNT appInitSoftware(TICK_COUNT loopStart){

    LED_off(&RightRed); 
    LED_off(&LeftRed); 
    LED_off(&SpotLightWhite); 
    LED_on(&PowerGreen);

    sonyPS2_setAnalogMode(&controller1);
    sonyPS2_calibrate(&controller1, 25);

return 0; // dont pause after
}
/***********************************************************************************/
// This routine is called repeatedly - its your main loop
TICK_COUNT appControl(LOOP_COUNT loopCount, TICK_COUNT loopStart){
    

if(sonyPS2_read(&controller1)) 
{
    xButton_pressure = sonyPS2_buttonPressure(&controller1, PS2_BTN_X);
    SqButton_pressure = sonyPS2_buttonPressure(&controller1, PS2_BTN_SQUARE);
    
    DL_Button_pressure = sonyPS2_buttonPressure(&controller1, PS2_DPAD_LEFT);
    DR_Button_pressure = sonyPS2_buttonPressure(&controller1, PS2_DPAD_RIGHT);
    
    if(sonyPS2_setAnalogMode(&controller1))
	{
		left_x = sonyPS2_joystick(&controller1, PS2_STICK_LEFT_X);
		left_y = sonyPS2_joystick(&controller1, PS2_STICK_LEFT_Y);
		right_x = sonyPS2_joystick(&controller1, PS2_STICK_RIGHT_X);
		right_y = sonyPS2_joystick(&controller1, PS2_STICK_RIGHT_Y);
	}
	if(sonyPS2_buttonHeld(&controller1, PS2_BTN_R1))
    {
		PS2_R1 = PS2_B_BTN_R1;
		LED_on(&RightRed);
    }
	else if(sonyPS2_buttonHeld(&controller1, PS2_DPAD_RIGHT))
	{
		PS2_RIGHT = PS2_B_DPAD_RIGHT;
		LED_on(&RightRed);
	}
    else
    {
        PS2_R1 = PS2_B_BTN_NOT;
		PS2_RIGHT = PS2_B_BTN_NOT;
		LED_off(&RightRed);
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_L1))
    {
		PS2_L1 = PS2_B_BTN_L1;
		LED_on(&LeftRed);
    }
	else if(sonyPS2_buttonHeld(&controller1, PS2_DPAD_LEFT))
	{
		PS2_LEFT = PS2_B_DPAD_LEFT;
		LED_on(&LeftRed);
	}
    else
    {
        PS2_L1 = PS2_B_BTN_NOT;
		PS2_LEFT = PS2_B_BTN_NOT;
		LED_off(&LeftRed);
    }
    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_R2))
    {
		PS2_R2 = PS2_B_BTN_R2;
	}
    else
    {
        PS2_R2 = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_L2))
    {
		PS2_L2 = PS2_B_BTN_L2;
    }
    else
    {
        PS2_L2 = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_TRIANGLE))
    {		
		SpotLightState++;
		PS2_TRIANGLE = PS2_B_BTN_TRIANGLE;
		if(SpotLightState % 2 == 0)
		{
			LED_off(&SpotLightWhite);
		}
		else
		{
			LED_on(&SpotLightWhite);
		}
    }
    else
    {
        PS2_TRIANGLE = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_CIRCLE))
    {
		PS2_CIRCLE = PS2_B_BTN_CIRCLE;
    }
    else
    {
		PS2_CIRCLE = PS2_B_BTN_NOT;
    }
	
    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_SQUARE))
    {
		PS2_SQUARE = PS2_B_BTN_SQUARE;
		LED_on(&RightRed);
		LED_on(&LeftRed);
		if(SqButton_pressure == 255)
        {
        	sonyPS_setRumble(&controller1, SqButton_pressure/2, false);
        }
        else
        {
            sonyPS_setRumble(&controller1, SqButton_pressure/2, false);
        }
    }
    else if(sonyPS2_buttonHeld(&controller1, PS2_BTN_X))
    {
		PS2_X = PS2_B_BTN_X;
		LED_off(&RightRed);
		LED_off(&LeftRed);
		if(xButton_pressure == 255)
        {
        	sonyPS_setRumble(&controller1, xButton_pressure/2, false);
        }
        else
        {
        	sonyPS_setRumble(&controller1, xButton_pressure/2, false);
        }
    }
    else
    {
        PS2_SQUARE = PS2_B_BTN_NOT;
		PS2_X = PS2_B_BTN_NOT;
		sonyPS_setRumble(&controller1, 0, false);
    }
    
    if(sonyPS2_buttonHeld(&controller1, PS2_DPAD_UP))
    {
       PS2_UP = PS2_B_DPAD_UP;
    }
	else
	{
		PS2_UP = PS2_B_BTN_NOT;
	}
	if(sonyPS2_buttonHeld(&controller1, PS2_DPAD_DOWN))
    {
		PS2_DOWN = PS2_B_DPAD_DOWN;
    }
    else
    {
        PS2_DOWN = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_SELECT))
    {
		PS2_SELECT = PS2_B_BTN_SELECT;		
    }
    else
    {
		PS2_SELECT = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_START))
    {
		PS2_START = PS2_B_BTN_START;
    }
    else
    {
		PS2_START = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_L3))
    {
		PS2_L3 = PS2_B_BTN_L3;
    }
    else
    {
		PS2_L3 = PS2_B_BTN_NOT;
    }

    if(sonyPS2_buttonHeld(&controller1, PS2_BTN_R3))
    {
		PS2_R3 = PS2_B_BTN_R3;
    }
    else
    {
		PS2_R3 = PS2_B_BTN_NOT;
    }
}
else
{
	
}
        
 SendData();   
return 200000; // wait for 1 second before calling me again. 1000000us = 1
//second
}
