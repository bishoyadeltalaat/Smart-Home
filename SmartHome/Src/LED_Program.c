/*
 * LED_Program.c
 *
 *  Created on: Sep 9, 2023
 *      Author: abdelrahmanhossam
 */

// Include LIB
#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"
#include <util/delay.h>

// Include DIO
#include "../Include/MCAL/DIO/DIO_Interface.h"

// Include LED
#include "../Include/HAL/LED/LED_Interface.h"
#include "../Include/HAL/LED/LED_Private.h"
#include "../Include/HAL/LED/LED_Cfg.h"


/*
 * Including
 * -----------------------------------
 * LIB --> STD_TYPES.h , BIT_MATH.h
 * MCAL
 * HAL
 */


void HLED_voidTurnOn  (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{
	MDIO_voidSetPinValue(A_DIOPort, A_PINID, DIO_SET);
}
void HLED_voidTurnOff (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{
	MDIO_voidSetPinValue(A_DIOPort, A_PINID, DIO_RESET);
}
void HLED_voidToggleLED (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID)
{
	MDIO_voidTogglePinValue(A_DIOPort, A_PINID);
}
