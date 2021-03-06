/*
 * I2C_MMA8452.c
 *
 * Created: 9/9/2014 8:28:02 AM
 *  Author: gregory.byrne
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <compat/twi.h>


#define MAX_TRIES 50
#define MMA8452_ID    0x0D  // MMA8452 Device Identifier
#define MMA8452_ADDR  0x1D  // MMA8452 Device Address
#define IODIR 0x00           // MMA8452 I/O Direction Register
#define GPIO  0x09           // MMA8452 General Purpose I/O Register
#define OLAT  0x0A           // MMA8452 Output Latch Register

#define OUT_X_MSB 0x01
#define XYZ_DATA_CFG  0x0E
#define WHO_AM_I   0x0D
#define CTRL_REG1  0x2A
#define GSCALE 2

#define I2C_START 0
#define I2C_DATA 1
#define I2C_DATA_ACK 2
#define I2C_STOP 3
#define ACK 1
#define NACK 0
#define DATASIZE 32

#define LED PB1
#define output_low(port,pin) port &= ~(1<<pin)
#define output_high(port,pin) port |= (1<<pin)

#define set_input(portdir,pin) portdir &= ~(1<<pin)
#define set_output(portdir,pin) portdir |= (1<<pin)

/* START I2C Routine */
unsigned char i2c_transmit(unsigned char type) {
  switch(type) {
     case I2C_START:    // Send Start Condition
       TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
       break;
     case I2C_DATA:     // Send Data with No-Acknowledge
       TWCR = (1 << TWINT) | (1 << TWEN);
       break;
     case I2C_DATA_ACK: // Send Data with Acknowledge
       TWCR = (1 << TWEA) | (1 << TWINT) | (1 << TWEN);
       break;
     case I2C_STOP:     // Send Stop Condition
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
	return 0;
  }
  // Wait for TWINT flag set on Register TWCR
  while (!(TWCR & (1 << TWINT)));
  // Return TWI Status Register, mask the prescaler bits (TWPS1,TWPS0)
  return (TWSR & 0xF8);
}
char i2c_start(unsigned int dev_id, unsigned int dev_addr, unsigned char rw_type)
{
  unsigned char n = 0;
  unsigned char twi_status;
  char r_val = -1;
i2c_retry:
  if (n++ >= MAX_TRIES) return r_val;
  // Transmit Start Condition
  twi_status=i2c_transmit(I2C_START);

  // Check the TWI Status
  if (twi_status == TW_MT_ARB_LOST) goto i2c_retry;
  if ((twi_status != TW_START) && (twi_status != TW_REP_START)) goto i2c_quit;
  // Send slave address (SLA_W)
  TWDR = (dev_id & 0xF0) | (dev_addr & 0x0E) | rw_type;
  // Transmit I2C Data
  twi_status=i2c_transmit(I2C_DATA);
  // Check the TWSR status
  if ((twi_status == TW_MT_SLA_NACK) || (twi_status == TW_MT_ARB_LOST)) goto i2c_retry;
  if (twi_status != TW_MT_SLA_ACK) goto i2c_quit;
  r_val=0;
i2c_quit:
  return r_val;
}
void i2c_stop(void)
{
  unsigned char twi_status;
  // Transmit I2C Data
  twi_status=i2c_transmit(I2C_STOP);
}
char i2c_write(char data)
{
  unsigned char twi_status;
  char r_val = -1;
  // Send the Data to I2C Bus
  TWDR = data;
  // Transmit I2C Data
  twi_status=i2c_transmit(I2C_DATA);
  // Check the TWSR status
  if (twi_status != TW_MT_DATA_ACK) goto i2c_quit;
  r_val=0;
i2c_quit:
  return r_val;
}
char i2c_read(char *data,char ack_type)
{
  unsigned char twi_status;
  char r_val = -1;               

  if (ack_type) {
    // Read I2C Data and Send Acknowledge
    twi_status=i2c_transmit(I2C_DATA_ACK);
    if (twi_status != TW_MR_DATA_ACK) goto i2c_quit;
  } else {
    // Read I2C Data and Send No Acknowledge
    twi_status=i2c_transmit(I2C_DATA);
    if (twi_status != TW_MR_DATA_NACK) goto i2c_quit;
  }
  // Get the Data
  *data=TWDR;
  r_val=0;
i2c_quit:
  return r_val;
}
void Write_MMA8452(unsigned char reg_addr,unsigned char data)
{
   // Start the I2C Write Transmission
   i2c_start(MMA8452_ID,MMA8452_ADDR,TW_WRITE);
   // Sending the Register Address
   i2c_write(reg_addr);
   // Write data to MMA8452 Register
   i2c_write(data);
   // Stop I2C Transmission
   i2c_stop();
}
unsigned char Read_MMA8452(unsigned char reg_addr)
{
   char data;
   // Start the I2C Write Transmission
   i2c_start(MMA8452_ID,MMA8452_ADDR,TW_WRITE);
   // Read data from MMA8452 Register Address
   i2c_write(reg_addr);
   // Stop I2C Transmission
   i2c_stop();

   // Re-Start the I2C Read Transmission
   i2c_start(MMA8452_ID,MMA8452_ADDR,TW_READ);
   i2c_read(&data,NACK);

   // Stop I2C Transmission
   i2c_stop();

   return data;
}
void i2c_init(void)
{
  // Initial ATMega328P TWI/I2C Peripheral
  TWSR = 0x00;         // Select Prescaler of 1
  // SCL frequency = 11059200 / (16 + 2 * 48 * 1) = 98.743 kHz
  TWBR = 0x30;        // 48 Decimal
}

int main(void)
{
	char data = 0;	  
	// Initial Master I2C
	i2c_init();
	// Initial the MMA8452 to active mode
	Write_MMA8452(CTRL_REG1, 0x01);
	set_output(DDRB, LED);
    while(1)
    {
        //PORTB |= 0x02;
		output_high(PORTB, LED);
		_delay_ms(2000);
		
		// Read MMA8452 xoutmsb Register
		 //data=Read_MMA8452(OUT_X_MSB);
		_delay_ms(10);
		
		//PORTB &= ~0x02;
		output_low(PORTB, LED);
		//setPinLow(&PORTB, 1);
		_delay_ms(2000);
    }
}