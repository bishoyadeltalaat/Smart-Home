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

#define F_CPU 8000000UL

// Set your initial users
User validUsers[MAX_USERS] = {
		{"user0", "0000"},
		{"user1", "1111"},
		{"user2", "2222"},
		{"user3", "3333"},
		{"user4", "4444"},
		{"user5", "5555"},
		{"user6", "6666"},
		{"user7", "7777"},
		{"user8", "8888"},
		{"user9", "9999"}
};
u8 local_u8ReceivedData = 255;
int attempts = 3;

int main(void) {
	MDIO_voidInit();
	MUART_voidInit();
	MTIMER0_voidInit();
	MTIMER1_voidInit();
	HLCD_voidInit();

	Display_WelcomeMessage();

	// Loop until the correct credentials are entered or maximum attempts reached
	do {
		MUART_voidSendStringSyncNonBlocking("\r\nEnter username: ");
		MUART_voidReceiveStringSync(enteredUsername);

		MUART_voidSendStringSyncNonBlocking("\r\nEnter password: ");
		MUART_voidReceiveStringSync(enteredPassword);

		// Check if the entered credentials are correct
		for (int i = 0; i < MAX_USERS; ++i) {
			if (VerifyCredentials(enteredUsername, enteredPassword, &validUsers[i])) {

				MUART_voidSendStringSyncNonBlocking("\r\nAccess Granted!\r\n\r\n");
				HLCD_voidDisplayString("Access Granted!");
				_delay_ms(1000);
				HLCD_voidClearDisplay();

				while(1){
					Display_Menu();
					local_u8ReceivedData = MUART_u8ReadByteSyncBlocking();
					Smart_Home(local_u8ReceivedData);
				}

				_delay_ms(400);
				HLCD_voidClearDisplay();
			}

		}

		attempts--;

		BuzzerOn(10000);
		_delay_ms(500);
		BuzzerOff ();

		WrongInput();

		if (attempts == 0) {
			BuzzerOn(200);
			_delay_ms(300);

			BuzzerOn(0);
			_delay_ms(300);

			BuzzerOn(200);
			_delay_ms(300);

			BuzzerOn(0);
			_delay_ms(300);

			BuzzerOn(200);
			_delay_ms(300);

			BuzzerOff ();

			attempts=3;
		}

	}while(1);
	return 0;
}





//#include <util/delay.h>
//#include <string.h>
//
//#include "../Include/LIB/STD_TYPES.h"
//#include "../Include/LIB/BIT_MATH.h"
//
//#include "../Include/MCAL/DIO/DIO_Interface.h"
//#include "../Include/MCAL/GI/GI_interface.h"
//#include "../Include/MCAL/UART/UART_Interface.h"
//#include "../Include/MCAL/TIMERS/TIMERS_Interface.h"
//#include "../include/MCAL/TWI/TWI_interface.h"
//
//#include "../Include/HAL/LED/LED_Interface.h"
//#include "../Include/HAL/LCD/LCD_Interface.h"
//#include "../Include/HAL/EEPROM/EEPROM_Interface.h"
//
//#define F_CPU 8000000UL
//
//int main(void) {
//	MDIO_voidInit();
//	MUART_voidInit();
//	MTIMER0_voidInit();
//	MTIMER1_voidInit();
//	u8 local_u8ReceivedData = 255;
//
//	HLCD_voidInit();
//
//
//	HLCD_voidDisplayString("Welcome Home...");
//	_delay_ms(1000);
//	HLCD_voidClearDisplay();
//
//	while(1){
//
//		local_u8ReceivedData = MUART_u8ReadByteSyncBlocking();
//
//		switch(local_u8ReceivedData)
//		{
//
//		//first room
//		case '1':
//
//			HLED_voidTurnOn(DIO_PORTD, PIN2);
//			HLCD_voidDisplayString("Light ROOM1 ON");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//		case '2':
//
//			HLED_voidTurnOff(DIO_PORTD, PIN2);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM1 OFF\r\n");
//			HLCD_voidDisplayString("Light ROOM2 OFF");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//			//second room
//		case '3':
//
//			HLED_voidTurnOn(DIO_PORTD, PIN3);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM2 ON\r\n");
//			HLCD_voidDisplayString("Light ROOM2 ON");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//		case '4':
//
//			HLED_voidTurnOff(DIO_PORTD, PIN3);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM2 OFF\r\n");
//			HLCD_voidDisplayString("Light ROOM2 OFF");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//			//third room
//		case '5':
//
//			HLED_voidTurnOn(DIO_PORTD, PIN4);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM3 ON\r\n");
//			HLCD_voidDisplayString("Light ROOM3 ON");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//		case '6':
//
//			HLED_voidTurnOff(DIO_PORTD, PIN4);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM3 OFF\r\n");
//			HLCD_voidDisplayString("Light ROOM3 OFF");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//			//fourth room
//		case '7':
//
//			HLED_voidTurnOn(DIO_PORTD, PIN6);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM4 ON\r\n");
//			HLCD_voidDisplayString("Light ROOM4 ON");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//		case '8':
//
//			HLED_voidTurnOff(DIO_PORTD, PIN6);
//			MUART_voidSendStringSyncNonBlocking("Light ROOM4 OFF\r\n");
//			HLCD_voidDisplayString("Light ROOM4 OFF");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//			//the door
//		case 'o':
//		case 'O':
//
//			MTIMER1_voidSetOCR1AValue(1000);
//			MUART_voidSendStringSyncNonBlocking("Door Is Opened\r\n");
//			HLCD_voidDisplayString("Door Is Opened");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//		case 'c':
//		case 'C':
//
//			MTIMER1_voidSetOCR1AValue(2000);
//			MUART_voidSendStringSyncNonBlocking("Door Is Cloosed\r\n");
//			HLCD_voidDisplayString("Door Is Cloosed");
//			_delay_ms(500);
//			HLCD_voidClearDisplay();
//			break;
//
//
//		case 'b':
//				MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_OUTPUT);
//				MTIMER0_voidSetOCR0Value(200);
//				_delay_ms(300);
//				MTIMER0_voidSetOCR0Value(0);
//				_delay_ms(300);
//				MTIMER0_voidSetOCR0Value(200);
//				_delay_ms(300);
//				MTIMER0_voidSetOCR0Value(0);
//				_delay_ms(300);
//				MTIMER0_voidSetOCR0Value(200);
//				_delay_ms(300);
//				MTIMER0_voidSetOCR0Value(0);
//				MDIO_voidSetPinDirection(DIO_PORTB,PIN3,DIO_INPUT);
//			break;
//		}
//	}
//}
