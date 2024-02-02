#include <util/delay.h>
#include <string.h>

#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"

#include "../Include/MCAL/DIO/DIO_Interface.h"
#include "../Include/MCAL/GI/GI_interface.h"
#include "../Include/MCAL/UART/UART_Interface.h"
#include "../Include/MCAL/TIMERS/TIMERS_Interface.h"
#include "../include/MCAL/TWI/TWI_interface.h"

#include "../Include/HAL/LED/LED_Interface.h"
#include "../Include/HAL/LCD/LCD_Interface.h"
#include "../Include/HAL/EEPROM/EEPROM_Interface.h"

#include "../SMARTHOME/SMARTHOME_Interface.h"
#include "../SMARTHOME/SMARTHOME_Private.h"
#include "../SMARTHOME/SMARTHOME_Cfg.h"

#define F_CPU 8000000UL

// Function to verify the entered credentials
int VerifyCredentials(const char* enteredUsername, const char* enteredPassword, const User* user) {
	return (strcmp(enteredUsername, user->username) == 0 &&
			strcmp(enteredPassword, user->password) == 0 &&
			strlen(enteredPassword) == PASSWORD_SIZE);
}

int Smart_Home(u8 local_u8ReceivedData){

	switch(local_u8ReceivedData)
	{

	//first room
	case '1':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOn(DIO_PORTD, PIN2);
		MUART_voidSendStringSyncNonBlocking("Light ROOM1 ON\r\n");
		HLCD_voidDisplayString("Light ROOM1 ON");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

	case '2':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOff(DIO_PORTD, PIN2);
		MUART_voidSendStringSyncNonBlocking("Light ROOM1 OFF\r\n");
		HLCD_voidDisplayString("Light ROOM2 OFF");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

		//second room
	case '3':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOn(DIO_PORTD, PIN3);
		MUART_voidSendStringSyncNonBlocking("Light ROOM2 ON\r\n");
		HLCD_voidDisplayString("Light ROOM2 ON");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

	case '4':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOff(DIO_PORTD, PIN3);
		MUART_voidSendStringSyncNonBlocking("Light ROOM2 OFF\r\n");
		HLCD_voidDisplayString("Light ROOM2 OFF");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

		//third room
	case '5':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOn(DIO_PORTD, PIN4);
		MUART_voidSendStringSyncNonBlocking("Light ROOM3 ON\r\n");
		HLCD_voidDisplayString("Light ROOM3 ON");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;
	case '6':


		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOff(DIO_PORTD, PIN4);
		MUART_voidSendStringSyncNonBlocking("Light ROOM3 OFF\r\n");
		HLCD_voidDisplayString("Light ROOM3 OFF");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

		//fourth room
	case '7':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOn(DIO_PORTD, PIN6);
		MUART_voidSendStringSyncNonBlocking("Light ROOM4 ON\r\n");
		HLCD_voidDisplayString("Light ROOM4 ON");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

	case '8':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		HLED_voidTurnOff(DIO_PORTD, PIN6);
		MUART_voidSendStringSyncNonBlocking("Light ROOM4 OFF\r\n");
		HLCD_voidDisplayString("Light ROOM4 OFF");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

		//the door
	case 'o':
	case 'O':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		MTIMER1_voidSetOCR1AValue(1000);
		MUART_voidSendStringSyncNonBlocking("Door Is Opened\r\n");
		HLCD_voidDisplayString("Door Is Opened");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

	case 'c':
	case 'C':

		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		MTIMER1_voidSetOCR1AValue(2000);
		MUART_voidSendStringSyncNonBlocking("Door Is Cloosed\r\n");
		HLCD_voidDisplayString("Door Is Cloosed");
		_delay_ms(500);
		HLCD_voidClearDisplay();
		break;

	default:
	{
		MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_OUTPUT);
		MUART_voidSendByteSyncBlocking(local_u8ReceivedData);
		MUART_voidSendStringSyncNonBlocking("\r\n");
		MUART_voidSendStringSyncNonBlocking("Its wrong chois please try again.\r\n");
		HLCD_voidDisplayString("Wrong chois!!");
		MTIMER0_voidSetOCR0Value(10000);
		_delay_ms(500);
		MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_INPUT);
		HLCD_voidClearDisplay();
	}

	}
}

void Display_Menu(void){
	MUART_voidSendStringSyncNonBlocking("\r\n\r\nTo Turn ON the FirstRoom Press 1\r\nTo Turn OFF the FirstRoom Press 2\r\n");
	MUART_voidSendStringSyncNonBlocking("\r\nTo Turn ON the SecondRoom Press 3\r\nTo Turn OFF the SecondRoom Press 4\r\n");
	MUART_voidSendStringSyncNonBlocking("\r\nTo Turn ON the ThirdRoom Press 5\r\nTo Turn OFF the ThirdRoom Press 6\r\n");
	MUART_voidSendStringSyncNonBlocking("\r\nTo Turn ON the FourthRoom Press 7\r\nTo Turn OFF the FourthRoom Press 8\r\n");
	MUART_voidSendStringSyncNonBlocking("\r\nTo Open The Door Press o or O\r\nTo Close The Door Press c or C\r\n\r\n");
}

void Display_WelcomeMessage(void){
	MUART_voidSendStringSyncNonBlocking("Welcome to the Smart Home System!\r\n");
	HLCD_voidDisplayString("Welcome Home...");
	_delay_ms(2000);
	HLCD_voidClearDisplay();
}

void WrongInput(void){
	// If no user matched, show access denied message
	MUART_voidSendStringSyncNonBlocking("\r\n\r\nUsername Or Password incorrect.Please try again.\r\n\r\n");
	HLCD_voidDisplayString("Access Denied!");
	_delay_ms(500);
	HLCD_voidClearDisplay();
}

int BuzzerOn(const u8 Frequecy){
	MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_OUTPUT);
	MTIMER0_voidSetOCR0Value(Frequecy);
}

void BuzzerOff(void){
	MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_INPUT);
}





