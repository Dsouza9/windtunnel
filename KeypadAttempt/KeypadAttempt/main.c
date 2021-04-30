/*
 * main.c
 * Micro-controller Code
 * Created: 1/25/2021 1:47:06 PM
 * Author : Dylan J. Souza
 */ 


#define F_CPU 16000000UL

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util/delay.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//--------------Beginning of LCD Code--------------------------------------------------------------------//
// Resources:The AVR Microcontroller and Embedded Systems Using Assembly and C Pg. 406-408,				 //		 //
// by Muhammad Ali Mazidi, Sarmad Naimi, and Sepher Naimi												 //
//																										 //
// CD-AVR-4d.c  - Use an HD44780U based LCD with an Atmel ATmega processor								 //
// Copyright (C) 2013 Donald Weiman (weimandn@alfredstate.edu)	Used under GNU General Public License	 //
//																										 //
///////////////////////////////////////////////////////////////////////////////////////////////////////////

// LCD interface, LCD RW pin GND

#define LCD_PORT     	PORTB                   
#define LCD_BIT_D7   	PORTB3					// LCD D7 connection to B3
#define LCD_BIT_D6   	PORTB2					// LCD D6 connection to B2
#define LCD_BIT_D4   	PORTB0					// LCD D4 connection to B0
#define LCD_DDR      	DDRB

#define LCD_PORT_EN     PORTC                   		// LCD Enable pin
#define LCD_BIT_EN      PORTC1					// LCD RS pin connection to C1
#define LCD_BIT_D5   	PORTC4					// LCD D5 connection to C4
#define LCD_DDR_EN      DDRC

#define LCD_PORT_RS     PORTC                   // LCD Register Select
#define LCD_BIT_RS      PORTC0			// LCD RS pin connection to C0
#define LCD_DDR_RS      DDRC

// LCD module information
#define LCD_lineOne     0x80                    // start of line 1
#define LCD_lineTwo     0xC0                    // start of line 2
#define LCD_lineThree   0x94                    // start of line 3 (20x4)
#define LCD_lineFour    0xD4                    // start of line 4 (20x4)

// LCD instructions
#define LCD_Clear           0x01        	    // replace all characters with ASCII 'space'
#define LCD_Home            0x02        	    // return cursor to first position on first line
#define LCD_entryMode       0x06                // shift cursor from left to right on read/write
#define LCD_displayOff      0x08                // turn display off
#define LCD_displayOn       0x0E                // display on, cursor on, don't blink character
#define LCD_functionReset   0x30                // reset the LCD
#define LCD_functionSet4bit 0x28                // 4-bit data, 2-line display, 5 x 7 font
#define LCD_setCursor       0x80                // set cursor position


// Function Prototypes
void lcd_write(unsigned char);
void lcd_write_instruction(unsigned char);
void lcd_write_data(unsigned char);
void lcd_print(char*);
void lcd_initialize(void);
void lcdGoToXY(unsigned char, unsigned char);

void lcd_initialize()
{
	_delay_ms(100);   
	// Set up the RS and E lines for the 'lcd_write_4' subroutine.
    LCD_PORT_RS &= ~(1<<LCD_BIT_RS);                // select the Instruction Register (RS low)
    LCD_PORT_EN &= ~(1<<LCD_BIT_EN);                  // make sure E is initially low
	// Reset the LCD controller
    lcd_write(LCD_functionReset);                 // first part of reset sequence
    _delay_ms(10);                                  // 4.1 mS delay (min)
    lcd_write(LCD_functionReset);                 // second part of reset sequence
    _delay_us(200);                                 // 100uS delay (min)
    lcd_write(LCD_functionReset);                 // third part of reset sequence
    //_delay_us(200);                                 // this delay is omitted in the data sheet
	lcd_write(LCD_functionSet4bit);               // set 4-bit mode
    _delay_us(80);                                  // 40uS delay (min)
	// Function Set instruction
    lcd_write_instruction(LCD_functionSet4bit);   // set mode, lines, and font
    _delay_us(80);                                  // 40uS delay (min)
	// Display On/Off Control instruction
    lcd_write_instruction(LCD_displayOff);        // turn display OFF
    _delay_us(80);                                  // 40uS delay (min)
	// Clear Display instruction
    lcd_write_instruction(LCD_Clear);             // clear display RAM
    _delay_ms(4);                                   // 1.64 mS delay (min)
	// ; Entry Mode Set instruction
    lcd_write_instruction(LCD_entryMode);         // set desired shift characteristics
    _delay_us(80);                                  // 40uS delay (min)
	// Display On/Off Control instruction
    lcd_write_instruction(LCD_displayOn);         // turn the display ON
    _delay_us(80);                                  // 40uS delay (min)
}

void lcd_write(unsigned char theByte)
{
	LCD_PORT &= ~(1<<LCD_BIT_D7);                        // assume that data is '0'
    if (theByte & 1<<7) LCD_PORT |= (1<<LCD_BIT_D7);     // make data = '1' if necessary

    LCD_PORT &= ~(1<<LCD_BIT_D6);                        // repeat for each data bit
    if (theByte & 1<<6) LCD_PORT |= (1<<LCD_BIT_D6);

    LCD_PORT &= ~(1<<LCD_BIT_D5);
    if (theByte & 1<<5) LCD_PORT |= (1<<LCD_BIT_D5);

    LCD_PORT &= ~(1<<LCD_BIT_D4);
    if (theByte & 1<<4) LCD_PORT |= (1<<LCD_BIT_D4);

// write the data
                                                    // 'Address set-up time' (40 nS)
    LCD_PORT_EN |= (1<<LCD_BIT_EN);                   // Enable pin high
    _delay_us(1);                                   // implement 'Data set-up time' (80 nS) and 'Enable pulse width' (230 nS)
    LCD_PORT_EN &= ~(1<<LCD_BIT_EN);                  // Enable pin low
    _delay_us(1);                                   // implement 'Data hold time' (10 nS) and 'Enable cycle time' (500 nS)
}

void lcd_write_instruction(unsigned char Cmnd)
{
	LCD_PORT_RS &= ~(1<<LCD_BIT_RS);                // select the Instruction Register (RS low)
    LCD_PORT_EN &= ~(1<<LCD_BIT_EN);                  // make sure E is initially low
    lcd_write(Cmnd);                    // write the upper 4-bits of the data
    lcd_write(Cmnd << 4);               // write the lower 4-bits of the data
}

void lcd_write_data(unsigned char theData)
{
    LCD_PORT_RS |= (1<<LCD_BIT_RS);                 // select the Data Register (RS high)
    LCD_PORT_EN &= ~(1<<LCD_BIT_EN);                  // make sure E is initially low
    lcd_write(theData);                           // write the upper 4-bits of the data
    lcd_write(theData << 4);                      // write the lower 4-bits of the data
}

void lcd_print(char * str)
{
    unsigned char i = 0;                             // character counter
    while (str[i] != 0)
    {
        lcd_write_data(str[i]);
        i++;
        _delay_us(80);                              // 40 uS delay (min)
    }
}

void lcdGoToXY(unsigned char x, unsigned char y) // Column, Row
{
	unsigned char firstAddr[] = {0x80, 0xC0, 0x94, 0xD4};	// Table 12-4, pg. 401 20 x 4 LCD
	lcd_write_instruction(firstAddr[y - 1] + x - 1);
	_delay_us(100);
}

void backSpace() 
{
	lcdGoToXY(7,1);
	lcd_print("              ");
	lcdGoToXY(7,1);
}

uint8_t Keypad()
{
	_delay_ms(10);
	uint8_t keypress = 0;
	
	PORTD = 0b01110000; // ROW 1
	
	_delay_ms(1); 
	PORTD = 0b01110111;
	if(PIND == 0b01110111)
	{
		keypress = 1;
	}
	_delay_ms(1);
	PORTD = 0b01111011;
	if(PIND == 0b01111011)
	{
		keypress = 2;
	}
	_delay_ms(1);
	PORTD = 0b01111101;
	if(PIND == 0b01111101)
	{
		keypress = 3;
	}
	_delay_ms(1);
	PORTD = 0b01111110;
	if(PIND == 0b01111110)
	{
		backSpace();
	}
	_delay_ms(1);
	
	PORTD = 0b10110000; // ROW 2
	
	_delay_ms(10);
	PORTD = 0b10110111; 
	if(PIND == 0b10110111)
	{
		keypress = 4;
	}
	_delay_ms(10);
	PORTD = 0b10111011;
	if(PIND == 0b10111011)
	{
		keypress = 5;
	}
	_delay_ms(1);
	PORTD = 0b10111101;
	if(PIND == 0b10111101)
	{
		keypress = 6;
	}
	_delay_ms(1);
	
	PORTD = 0b11010111; // ROW 3
	
	_delay_ms(10);
	PORTD = 0b11010111; 
	if(PIND == 0b11010111)
	{
		keypress = 7;
	}
	_delay_ms(1);
	PORTD = 0b11011011;
	if(PIND == 0b11011011)
	{
		keypress = 8;
	}
	_delay_ms(10);
	PORTD = 0b11011101;
	if(PIND == 0b11011101)
	{
		keypress = 9;
	}
	_delay_ms(1);
	
	PORTD = 0b11100000; // ROW 4
	
	_delay_ms(10);
	PORTD = 0b11101011; // CANT RETURN 0, CHECK MAIN
	if(PIND == 0b11101011)
	{
		lcd_print("0"); // Either single, double, or randomly appears
						// Bug due to the way program prints keypress var
						// "if(button != 0) "
	}
	_delay_ms(10);
	return keypress;
}


///////////////////////////////////////////////////////////////////////////////////////////
//--------------End of LCD Code----------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////////////////////////////////////////////////////////
//--------------Beginning of Main Code---------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	
	// configure the microprocessor pins for the data lines
    LCD_DDR |= (1<<LCD_BIT_D7);                  // 4 data lines - output
    LCD_DDR |= (1<<LCD_BIT_D6);
    LCD_DDR |= (1<<LCD_BIT_D5);
    LCD_DDR |= (1<<LCD_BIT_D4);
	
	// configure the microprocessor pins for the control lines
    LCD_DDR_EN |= (1<<LCD_BIT_EN);                    // E line - output
    LCD_DDR_RS |= (1<<LCD_BIT_RS);                    // RS line - output

	lcd_initialize();                                 // initialize the LCD display for a 4-bit interface
	
	lcd_print("F(HZ):"); 							  // display the first line of information
	lcdGoToXY(1,3);									  // set cursor to 3rd line
	_delay_us(80);									  // 40 uS delay (min)                             			
	
	lcd_print("Current RPM:");						  // display the 3rd line of information
	_delay_us(80);	
	lcdGoToXY(7,1);									  // set cursor after "F(HZ):"

	DDRD = 0xF0; // column pins are input, row pins are output
	_delay_ms(1);
	PORTD = 0x0F; // enables pull-ups on PORTD
	_delay_ms(1);
	
	// Must use TIMER1, PB0 1 or 2
	// Two output compare pins
	// Either h-to-l on compare match, 20ms freq with varying duty cycle 
	
	uint8_t button = 0;
	
	while(1)
	{	
		char show[8];
		while(1)
		{
			button = Keypad();
			if(button != 0) 
			{
				itoa(button,show,10);
				lcd_print(show);
				//location++;
				while(Keypad()!=0);
			}
			_delay_ms(20);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
//--------------End of Main Code---------------------------------------------------------//
///////////////////////////////////////////////////////////////////////////////////////////
