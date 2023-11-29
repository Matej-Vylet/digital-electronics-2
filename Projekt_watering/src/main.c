
/***********************************************************************
 * 
 * The I2C (TWI) bus scanner tests all addresses and detects devices
 * that are connected to the SDA and SCL signals.
 * 
 * ATmega328P (Arduino Uno), 16 MHz, PlatformIO
 *
 * Copyright (c) 2023 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/


/* Defines -----------------------------------------------------------*/
#ifndef F_CPU
# define F_CPU 16000000  // CPU frequency in Hz required for UART_BAUD_SELECT
#endif


/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include <twi.h>            // I2C/TWI library for AVR-GCC
#include <uart.h>           // Peter Fleury's UART library
#include <stdlib.h>         // C library. Needed for number conversions
#include <oled.h>
#include <gpio.h>
#include <stdio.h>

/* Global variables --------------------------------------------------*/
// Declaration of "dht12" variable with structure "DHT_values_structure"
struct DHT_values_structure {
   uint16_t hum_int;
   uint16_t hum_dec;
   uint16_t temp_int;
   uint16_t temp_dec;
   uint16_t checksum;
   uint32_t cap_hum;
} dht12;
uint16_t dry_max = 900;
uint16_t wet_max = 670;
uint16_t value = 0;

// Flag for printing new data from sensor
volatile uint8_t new_sensor_data = 0;


// Slave and internal addresses of temperature/humidity sensor DHT12
#define SENSOR_ADR 0x5c
#define SENSOR_HUM_MEM 0
#define SENSOR_TEMP_MEM 2
#define SENSOR_CHECKSUM 4
#define AN PC0
#define RELE PD2



/* Function definitions ----------------------------------------------*/
/**********************************************************************
* Function: Main function where the program execution begins
* Purpose:  Wait for new data from the sensor and sent them to UART.
* Returns:  none
**********************************************************************/
int main(void)
{
    GPIO_mode_output(&DDRD, RELE);
    
    ADMUX |= (1<<REFS0);
    ADMUX &= ~(1<<REFS1);
    ADMUX &= ~((1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0) );

    // Enable ADC module
    ADCSRA |= (1<<ADEN);
    // Enable conversion complete interrupt
    ADCSRA |= (1<<ADIE);
    // Set clock prescaler to 128
    ADCSRA |= (1<<ADPS2 | 1<<ADPS1 | 1<<ADPS0);

    ICR1 = 20000;
    OCR1A = AN;

    oled_init(OLED_DISP_ON);
    oled_clrscr();

    // Copy buffer to display RAM
    oled_display();
    char string[2];  // String for converting numbers by itoa()
    
    // TWI
    twi_init();
    
    // UART
    uart_init(UART_BAUD_SELECT(115200, F_CPU));

    // Test if sensor is ready
    if (twi_test_address(SENSOR_ADR) == 0)
      {
        uart_puts("I2C sensor detected\r\n");
        uart_puts("Teperature\t");
        uart_puts("Humidity\r\n");
      }
    else {
        uart_puts("[ERROR] I2C device not detected\r\n");
        while (1);
    }

    // Timer1
    TIM1_OVF_1SEC
    TIM1_OVF_ENABLE

    sei(); // Needed for UART

    // Infinite loop
    while (1) {
        if (new_sensor_data == 1)
          {
            oled_gotoxy(0,0);
            oled_charMode(NORMALSIZE);

            itoa(dht12.temp_int, string, 10);
            oled_puts("Temperature: ");
            oled_puts(string);
            uart_puts(string);
            uart_puts(".");
            oled_puts(".");

            itoa(dht12.temp_dec, string, 10);
            uart_puts(string);
            uart_puts(",");
            oled_puts(string);
            oled_puts(" °C \r\n\n");

            itoa(dht12.cap_hum,string,10);
            oled_puts("Humidity: ");
            uart_puts(string);
            uart_puts("\r\n");
            oled_puts(string);
            oled_puts(" % \r\n\n");

            if( dht12.cap_hum<45) //je sucho
              {
                GPIO_write_low(&PORTD, RELE);
                oled_puts("Watering: ON ");                 
              }
            if(dht12.cap_hum>85)
              {
                GPIO_write_high(&PORTD, RELE);
                oled_puts("Watering: OFF");  
              }

            // Do not print it again and wait for the new data
            new_sensor_data = 0;
            oled_display();
          }
  }
    // Will never reach this
    return 0;
}


/* Interrupt service routines ----------------------------------------*/
/**********************************************************************
* Function: Timer/Counter1 overflow interrupt
* Purpose:  Read temperature and humidity from DHT12, SLA = 0x5c.
**********************************************************************/
ISR(TIMER1_OVF_vect)
{
    // Test ACK from sensor
    twi_start();
    if (twi_write((SENSOR_ADR<<1) | TWI_WRITE) == 0) 
      {
        // Set internal memory location
        twi_write(0x00);
        twi_stop();

        // Read data from internal memory
        twi_start();
        twi_write((SENSOR_ADR<<1) | TWI_READ);
        dht12.hum_int = twi_read(TWI_ACK);
        dht12.hum_dec = twi_read(TWI_ACK);
        dht12.temp_int = twi_read(TWI_ACK);
        dht12.temp_dec = twi_read(TWI_NACK);
        twi_stop();

        ADCSRA |= (1<<ADSC);
        new_sensor_data = 1;
      }
    twi_stop();
}

ISR(ADC_vect)
{
    static uint16_t value;
    
    char string[4];  // String for converted numbers by itoa()

    // Read converted value
    // Note that, register pair ADCH and ADCL can be read as a 16-bit value ADC
    value = ADC;
    dht12.cap_hum =(950-value)*100/300;  
}

