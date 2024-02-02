/*
 * TIMERS_Cfg.h
 *
 *  Created on: Nov 7, 2023
 *      Author: D E L L
 */

#ifndef INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_

#define TIMER0_MODE  FAST_PWM_MODE


/*
 * 0b000 No clock source (Timer/Counter stopped).
 * 0b001 clkI/O/(No prescaling)
 * 0b010 clkI/O/8 (From prescaler)
 * 0b011 clkI/O/64 (From prescaler)
 * 0b100 clkI/O/256 (From prescaler)
 * 0b101 clkI/O/1024 (From prescaler)
 * 0b110 External clock source on T0 pin. Clock on falling edge.
 * 0b111 External clock source on T0 pin. Clock on rising edge.
 */

#define TIMER0_CLK 0b010

#define OCR0_VALUE 199


/*
 * 0b00 Normal port operation, OC0 disconnected.
 * 0b01 Toggle OC0 on compare match
 * 0b10 Clear OC0 on compare match
 * 0b11 Set OC0 on compare match
 */

/*
 * Fast PWM
 * 0 Normal port operation, OC0 disconnected.
 * 2 Non-Inverting
 * 3 Inverting
 */
#define OC0_MODE 3
#endif /* INCLUDE_MCAL_TIMERS_TIMERS_CFG_H_ */
