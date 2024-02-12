
#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include <avr/interrupt.h>
#include "keypad_driver.h"
#include "LCD.h"
#include "seven segment.h"
#include "Timer.h"
#include "button.h"
#include <math.h>
#include <stdio.h>
volatile unsigned short counter_sec = 0, counter_minute = 0, counter_hour = 0;
unsigned char value, F_digit, S_digit;
int main(void)
{
	keypad_vInit();
	LCD_vInit();
	seven_seg_vinit('A');
	button_vInit('B', 3);
	DIO_set_port_direction('C', 0x7f);
	LCD_vSend_string(" press POM to");
	LCD_movecursor(2,3);
	LCD_vSend_string(" set clock");
	timer2_overflow_init_interrupt();
   
   while (1)
   {
	   value = button_u8read('B', 3);
	   if(value == 1){
		   label_hours:
		   LCD_clearscreen();
		   LCD_vSend_string("hours = --");
		   LCD_movecursor(1, 9);
		   _delay_ms(500);
		   do 
		   {
			   F_digit = keypad_u8check_press();
		   } while (F_digit == NOTPRESSED);
		   LCD_vSend_char(F_digit);
		   _delay_ms(300);
		   do
		   {
			   S_digit = keypad_u8check_press();
		   } while (S_digit == NOTPRESSED);
		   LCD_vSend_char(S_digit);
		   _delay_ms(300);
		   counter_hour = (F_digit - '0') * 10 + (S_digit - '0');
		   if (counter_hour >= 24)
		   {
			   LCD_clearscreen();
			   LCD_movecursor(1, 5);
			   LCD_vSend_string("Error");
			   _delay_ms(1000);
			   LCD_clearscreen();
			   LCD_vSend_string("Please enter the");
			   LCD_movecursor(2,1);
			   LCD_vSend_string("hours from 0-23");
			   _delay_ms(2000);
			   goto label_hours;
		   }
		   
		   label_min:
		   LCD_clearscreen();
		   LCD_vSend_string("minutes = --");
		   LCD_movecursor(1, 11);
		   _delay_ms(500);
		   do
		   {
			   F_digit = keypad_u8check_press();
		   } while (F_digit == NOTPRESSED);
		   LCD_vSend_char(F_digit);
		   _delay_ms(300);
		   do
		   {
			   S_digit = keypad_u8check_press();
		   } while (S_digit == NOTPRESSED);
		   LCD_vSend_char(S_digit);
		   _delay_ms(300);
		   counter_minute = (F_digit - '0') * 10 + (S_digit - '0');
		   if (counter_minute >= 60)
		   {
			   LCD_clearscreen();
			   LCD_movecursor(1, 5);
			   LCD_vSend_string("Error");
			   _delay_ms(1000);
			   LCD_clearscreen();
			   LCD_vSend_string("Please enter min");
			   LCD_movecursor(2,1);
			   LCD_vSend_string(" from 0-59 ");
			   _delay_ms(2000);
			   LCD_clearscreen();
			   goto label_min;
		   }
		   
		    label_sec:
		    LCD_clearscreen();
		    LCD_vSend_string("seconds = --");
		    LCD_movecursor(1, 11);
		    _delay_ms(500);
		    do
		    {
			    F_digit = keypad_u8check_press();
		    } while (F_digit == NOTPRESSED);
		    LCD_vSend_char(F_digit);
		    _delay_ms(300);
		    do
		    {
			    S_digit = keypad_u8check_press();
		    } while (S_digit == NOTPRESSED);
		    LCD_vSend_char(S_digit);
		    _delay_ms(300);
		    counter_sec = (F_digit - '0') * 10 + (S_digit - '0');
		    if (counter_sec >= 60)
		    {
			    LCD_clearscreen();
			    LCD_movecursor(1, 5);
			    LCD_vSend_string("Error");
			    _delay_ms(1000);
			    LCD_clearscreen();
			    LCD_vSend_string("Please enter sec");
			    LCD_movecursor(2,1);
			    LCD_vSend_string(" from 0-59 ");
			    _delay_ms(2000);
			    LCD_clearscreen();
			    goto label_sec;
		    }
			LCD_clearscreen();
			LCD_vSend_string(" press POM to");
			LCD_movecursor(2,3);
			LCD_vSend_string(" set clock");
	   }
	   	DIO_write_port('C', 0x7e);
		seven_seg_write('A', counter_sec % 10);
		_delay_ms(5);
		DIO_write_port('C', 0x7d);
		seven_seg_write('A', counter_sec / 10);
		_delay_ms(5);
		DIO_write_port('C', 0x7b);
		seven_seg_write('A', counter_minute % 10);
		_delay_ms(5);
		DIO_write_port('C', 0x77);
		seven_seg_write('A', counter_minute / 10);
		_delay_ms(5);
		DIO_write_port('C', 0x6f);
		seven_seg_write('A', counter_hour % 10);
		_delay_ms(5);
		DIO_write_port('C', 0x5f);
		seven_seg_write('A', counter_hour / 10);
		_delay_ms(5);
		DIO_write_port('C', 0x7f);
		
		if (counter_sec==60)
		{
			counter_sec=0;
			counter_minute++;
		}
		if (counter_minute==60)
		{
			counter_minute=0;
			counter_hour++;
		}
		if (counter_hour==24)
		{
			counter_hour=0;
		}
			   
   }
}   

ISR(TIMER2_OVF_vect){
	counter_sec++;
}