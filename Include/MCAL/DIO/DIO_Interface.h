/*
 * DIO_Interface.h
 *
 *  Created on: Sep 8, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_DIO_DIO_INTERFACE_H_
#define INCLUDE_MCAL_DIO_DIO_INTERFACE_H_

typedef enum{
	DIO_PORTA=0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}DIO_PORT_e;

typedef enum{
	PIN0=0,
	PIN1,
	PIN2,
	PIN3,
	PIN4,
	PIN5,
	PIN6,
	PIN7
}DIO_PIN_e;

typedef enum{
	DIO_INPUT=0,
	DIO_OUTPUT
}DIO_DIRECTION_e;

typedef enum{
	DIO_RESET=0,
	DIO_SET
}DIO_VALUE_e;

void MDIO_voidInit();
void MDIO_voidSetPinDirection (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID, DIO_DIRECTION_e A_PINDirection);
void MDIO_voidSetPinValue (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID, DIO_VALUE_e A_PINValue);
DIO_VALUE_e MDIO_GetPinValue (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID);
void MDIO_voidSetPortDirection (DIO_PORT_e A_DIOPort, u8 A_u8Direction);
void MDIO_voidSetPortValue (DIO_PORT_e A_DIOPort, u8 A_u8Value);


#endif /* INCLUDE_MCAL_DIO_DIO_INTERFACE_H_ */
