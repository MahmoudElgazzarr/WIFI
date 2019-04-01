/*
 * Wifi.c
 *
 * Created: 4/1/2019 11:27:23 AM
 * Author : AVE-LAP-005
 */ 

#include <avr/io.h>
#include <stddef.h>
#include "uart_driver.h"
#include "ESP_Driver.h"
#include <avr/interrupt.h>

#define SYSTEM_FREQ	16000000UL
#define F_CPU 16000000UL

int main(void)
{
	/*Intalize LEDS As OUTPUT*/
	DDRB |= (1<<PINB4);
	DDRB |= (1<<PINB5);
	DDRB |= (1<<PINB6);
	
	/*Pointer To Recive Data In it*/
	int* DataReceived=NO_Response;
	
	/*Disable Interrupt*/
	Disable_Interrupts();
	/*Inalize UART With Baud Rate 9600*/
	UART_Init(9600,ESP_FillResponseBuffer);
	
	/*Enable Interrupts*/
	Enable_Interrupts();
	/*Intalize Wifi As Server*/
	WIFI_Service_Start(Server, "1234","Anonymouss","A123456789", NULL, NULL, NULL, NULL);
	while(OK_Status!=ESP_SendData("Wifi Demo Started","17"));
	*DataReceived=NO_Response;
	/*Loop Forever*/
	while(1)
	{
		DataReceived=ESP_ReceiveData();
		_delay_ms(1000);
		/*If data Recived Is W , Turn On LEDS*/
			if((*DataReceived) == 'W')
			{
				PORTB |=(1<<PINB4);
				PORTB |=(1<<PINB5);
				PORTB |=(1<<PINB6);
			}
			/*If Recived Data is S , Turn Off LEDS*/
			else if((*DataReceived) == 'S')
			{
				PORTB &=~(1<<PINB4);
				PORTB &=~(1<<PINB5);
				PORTB &=~(1<<PINB6);
			}
	}
}


