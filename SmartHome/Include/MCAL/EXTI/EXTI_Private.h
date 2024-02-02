/*
 * EXTI_Private.h
 *
 *  Created on: Nov 5, 2023
 *      Author: D E L L
 */

#ifndef INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_
#define INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_

#define MCUCR  (*(volatile u8 *)0x55)
#define MCUCSR (*(volatile u8 *)0x54)
#define GICR   (*(volatile u8 *)0x5B)
#define GIFR   (*(volatile u8 *)0x5A)


#define SENSE_MODE_MASK 3
#define EXTI0_SENSE_MODE_BITS 0
#define EXTI1_SENSE_MODE_BITS 2
#define EXTI2_SENSE_MODE_BITS 6

#define EXTI0_ENABLE_BIT 6
#define EXTI1_ENABLE_BIT 7
#define EXTI2_ENABLE_BIT 5

#endif /* INCLUDE_MCAL_EXTI_EXTI_PRIVATE_H_ */
