/*
 * LED_Interface.h
 *
 *  Created on: Sep 9, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_HAL_LED_LED_INTERFACE_H_
#define INCLUDE_HAL_LED_LED_INTERFACE_H_

void HLED_voidTurnOn  (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID);
void HLED_voidTurnOff (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID);
void HLED_voidToggleLED (DIO_PORT_e A_DIOPort,DIO_PIN_e A_PINID);


#endif /* INCLUDE_HAL_LED_LED_INTERFACE_H_ */
