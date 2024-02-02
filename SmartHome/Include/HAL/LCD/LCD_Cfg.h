#ifndef INCLUDE_HAL_LCD_LCD_CFG_H_
#define INCLUDE_HAL_LCD_LCD_CFG_H_

#define LCD_DATA_PORT DIO_PORTA
#define LCD_CTRL_PORT DIO_PORTB

#define LCD_RS_PIN  PIN0
#define LCD_RW_PIN  PIN1
#define LCD_E_PIN   PIN2


/*
 *  0 --> 1 Line
 *  1 --> 2 Lines
 */
#define LCD_NO_OF_LINES 1

/*
 *  0 --> 5 * 7
 *  1 --> 5 * 10
 */
#define LCD_CHAR_SIZE 0

/*
 *  0 --> OFF
 *  1 --> ON
 */
#define DISPLAY_STATUS 1

/*
 *  0 --> OFF
 *  1 --> ON
 */
#define CURSOR_DISPLAY 1

/*
 *  0 --> OFF
 *  1 --> ON
 */
#define CURSOR_BLINK 1

/*
 *  0 --> Right to Left
 *  1 --> Left to Right
 */
#define DISPLAY_DIRECTION 1


/*
 *  0 --> OFF
 *  1 --> ON
 */
#define SHIFT_ENABLE 0

#endif /* INCLUDE_HAL_LCD_LCD_CFG_H_ */
