#include <avr/io.h>
#include <util/delay.h>
#include<avr\interrupt.h>
#include <avr/wdt.h> 
#include "usart.h"

#define PSclock            2               // PD2
#define PSdata             3               // PD3
#define PSacknolage  4               // PD4
#define PScommand   5               // PD5
#define PSattention     6               // PD6 int main(void)

{
   // set the baud rate of the UART      // (needed for transmitting over radio module).
   //uartSetUp(2400);

   // set port pins to output for status leds:
   sbi(DDRC, PC0);                 // led.
   sbi(DDRC, PC1);                 // led
   sbi(DDRC, PC2);                 // led
   sbi(DDRC, PC3);                 // led
   sbi(DDRD, PD7);                 // led
   sbi(DDRB, PB0);                 // led
   sbi(DDRB, PB1);                 // led
   sbi(DDRB, PB2);                 // led

   // PSx controller I/O pin setup:
   sbi(DDRD, PD2);                 // clock. output. (blue)

   cbi(DDRD, PD3);                 // data. input. (brown)
   sbi(PORTD, PD3);               //    enable pullup resistor

   cbi(DDRD, PD4);                 // acknolage. input. (green)
   sbi(PORTD, PD4);               //    enable pullup resistor

   sbi(DDRD, PD5);                 // command. output. (orange)

   sbi(DDRD, PD6);                 // attention. output. (yellow)


   // enable interupts
   sei();

   // watchdog timer reset and enable
   //wdt_reset();
   //wdt_enable(0x02);

   timerInit();


   // this loop continues to put PSx controller into analouge mode untill the
   // controller responds with 0x73 in the 2nd byte.  
   // (PS2 controller responds with 0x73 when in analouge mode.)
   // the status LEDs will continue to count upwards untill a controller is found.
   // if everything is working correctly this should happen on the first pass of
   // this loop but occasionally errors occur and a 2nd or 3rd itteration happen.
   unsigned char chk_ana = 0, cnt = 0;
   while(chk_ana != 0x73){
       // put controller in config mode
       sbi(PORTD, PScommand);
       sbi(PORTD, PSclock);
       cbi(PORTD, PSattention);

       gameByte(0x01);
       gameByte(0x43);
       gameByte(0x00);
       gameByte(0x01);
       gameByte(0x00);

       sbi(PORTD, PScommand);
       delay_ms(1);
       sbi(PORTD, PSattention);

       delay_ms(10);

       // put controller in analouge mode
       sbi(PORTD, PScommand);
       sbi(PORTD, PSclock);
       cbi(PORTD, PSattention);

       gameByte(0x01);
       gameByte(0x44);
       gameByte(0x00);
       gameByte(0x01);
       gameByte(0x03);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);

       sbi(PORTD, PScommand);
       delay_ms(1);
       sbi(PORTD, PSattention);

       delay_ms(10);

       // exit config mode
       sbi(PORTD, PScommand);
       sbi(PORTD, PSclock);
       cbi(PORTD, PSattention);

       gameByte(0x01);
       gameByte(0x43);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x5A);
       gameByte(0x5A);
       gameByte(0x5A);
       gameByte(0x5A);
       gameByte(0x5A);

       sbi(PORTD, PScommand);
       delay_ms(1);
       sbi(PORTD, PSattention);

       delay_ms(10);

       // poll controller and check in analouge mode.
       sbi(PORTD, PScommand);
       sbi(PORTD, PSclock);
       cbi(PORTD, PSattention);

       gameByte(0x01);
       chk_ana = gameByte(0x42);            // the 2nd byte to be returned from the controller should = 0x73 for "red" analouge controller.
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);
       gameByte(0x00);

       sbi(PORTD, PScommand);
       delay_ms(1);
       sbi(PORTD, PSattention);
       delay_ms(10);

  // keep increasing counter to be dispalyed untill PSx controller confirms it's in analouge mode.
       display(cnt++);                    
       if (cnt > 254){ cnt=0;}
   }

   short int temp, data0, data1, data2, data3, data4, data5, i ,debounceSelect;
  // main program loop:
   while (1){

        sbi(PORTD, PScommand);                          // start communication with PSx controller
        sbi(PORTD, PSclock);
        cbi(PORTD, PSattention);

        gameByte(0x01);                                       // bite 0. header.
        temp = gameByte(0x42);                          // bite 1. header. (should possibly put test on this byte to detect unplugging of controller.)
        gameByte(0x00);                                       // bite 2. header.

        data0 = gameByte(0x00);                         // bite 3. first data bite.
        data1 = gameByte(0x00);                         // bite 4.
        data2 = gameByte(0x00);                         // bite 5.
        data3 = gameByte(0x00);                         // bite 6.
        data4 = gameByte(0x00);                         // bite 7.
        data5 = gameByte(0x00);                         // bite 8.

        delay_us(1);
        sbi(PORTD, PScommand);                      // close communication with PSx controller
        delay_us(1);
        sbi(PORTD, PSattention);                        // all done.



        if(!(data0 & _BV(0)) && !debounceSelect)        // capture one unique press of the "select" button
        {
                debounceSelect = 1;
        }
        else if ((data0 & _BV(0)) && debounceSelect)
        {
                if(i++ >= 5) i=0;
                debounceSelect = 0;
        }


        // this switch decides which data register to show on status LEDs depending on how many times
        // the "select" button on the PS2 controller has been pressed.
        switch(i)
        {
                case 0:
                        display(data0);
                        break;
                case 1:
                        display(data1);
                        break;
                case 2:
                        display(data2);
                        break;
                case 3:
                        display(data3);
                        break;
                case 4:
                        display(data4);
                        break;
                case 5:
                        display(data5);
        }        // this section calls my R/C transmit code (not included here).
        //tx_channel(0, data2);
        //tx_channel(1, data5);

   } // while(1)  
} //main
// PSx controller communication function.
// send a byte on the command line and receive one on the data line.
// needs Attention pin to have gone low before called to activate controller.
int gameByte(short int command)
{
        short int i ;
        delay_us(1);
        short int data = 0x00;                             // clear data variable to save setting low bits later.
        for(i=0;i<8;i++)
        {
                if(command & _BV(i)) sbi(PORTD, PScommand);       // bit bang "command" out on PScommand wire.
                else cbi(PORTD, PScommand);
                cbi(PORTD, PSclock);                             // CLOCK LOW
                delay_us(1);                                              // wait for output to stabilise
                if((PIND & _BV(PSdata))) sbi(data, i);  // read PSdata pin and store
                //else cbi(data, i);
                sbi(PORTD, PSclock);                             // CLOCK HIGH
        }
        sbi(PORTD, PScommand);

        delay_us(20);                                                   // wait for ACK to pass.

        return(data);
}


// put 1 byte on the 8 LEDs. obviously you need to change the output pins to // match your board.
void display(short int LEDs)
{
        if(LEDs & _BV(0)) cbi(PORTC, PD0);
        else sbi(PORTC, PD0);

        if(LEDs & _BV(1)) cbi(PORTC, PD1);
        else sbi(PORTC, PD1);

        if(LEDs & _BV(2)) cbi(PORTC, PD2);
        else sbi(PORTC, PD2);

        if(LEDs & _BV(3)) cbi(PORTC, PD3);
        else sbi(PORTC, PD3);

        if(LEDs & _BV(4)) cbi(PORTD, PD7);
        else sbi(PORTD, PD7);

        if(LEDs & _BV(5)) cbi(PORTB, PD0);
        else sbi(PORTB, PD0);

        if(LEDs & _BV(6)) cbi(PORTB, PD1);
        else sbi(PORTB, PD1);

        if(LEDs & _BV(7)) cbi(PORTB, PD2);
        else sbi(PORTB, PD2);

        return;
} 
