/*
 * UART_Private.h
 *
 *  Created on: May 4, 2023
 *      Author: abdelrahmanhossam
 */

#ifndef INCLUDE_MCAL_UART_UART_PRIVATE_H_
#define INCLUDE_MCAL_UART_UART_PRIVATE_H_

/*address of UART Control and status register A*/
#define UCSRA *((volatile u8*)0x2B)

/*address of UART Control and status register B*/
#define UCSRB *((volatile u8*)0x2A)

/*address of UART Control and status register C*/
#define UCSRC *((volatile u8*)0x40)

/*address of USART I/O register*/
#define UDR   *((volatile u8*)0x2C)

#define UBRRL *((volatile u8*)0x29)
#define UBRRH *((volatile u8*)0x40)

/* The equation to calculate the UBBR value */
#define BAUD_RATE_EQUATION (F_CPU/16/BAUDRATE_VALUE-1)



#endif /* INCLUDE_MCAL_UART_UART_PRIVATE_H_ */
