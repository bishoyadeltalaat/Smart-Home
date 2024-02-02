/*
 * LCD_Program.c
 *
 *  Created on: Nov 3, 2023
 *      Author: D E L L
 */

#include "../Include/LIB/STD_TYPES.h"
#include "../Include/LIB/BIT_MATH.h"
#include <util/delay.h>

// Include DIO
#include "../Include/MCAL/DIO/DIO_Interface.h"

#include "../Include/HAL/LCD/LCD_Interface.h"
#include "../Include/HAL/LCD/LCD_Private.h"
#include "../Include/HAL/LCD/LCD_Cfg.h"

#define F_CPU 8000000UL

void HLCD_voidSendCommand (u8 A_u8Command)
{
	// To send Command --> (RS-->0) , (RW-->0)
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_RESET);
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_RESET);

	// Send Command
	MDIO_voidSetPortValue(LCD_DATA_PORT, A_u8Command);

	// Set Pulse on E Pin
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_SET);
	_delay_ms(2);
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_RESET);
}

void HLCD_voidSendData (u8 A_u8Data)
{
	// To send Data --> (RS-->1) , (RW-->0)
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RS_PIN, DIO_SET);
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_RW_PIN, DIO_RESET);

	// Send Data
	MDIO_voidSetPortValue(LCD_DATA_PORT, A_u8Data);

	// Set Pulse on E Pin
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_SET);
	_delay_ms(2);
	MDIO_voidSetPinValue(LCD_CTRL_PORT, LCD_E_PIN, DIO_RESET);
}


void HLCD_voidInit(void)
{
	// Wait for more than 30ms after VDD rises to 4.5v
	_delay_ms(30);

	// Function Set Command then wait for more than 39us
	HLCD_voidSendCommand(FUNCTION_SET);
	_delay_ms(1);

	// Display ON/OFF Control Command then wait for more than 39us
	HLCD_voidSendCommand(DISPLAY_ON_OFF_CONTROL);
	_delay_ms(1);

	// Display Clear Command then wait for more than 1.53ms
	HLCD_voidSendCommand(DISPLAY_CLEAR);
	_delay_ms(2);

	// Entry Mode Set Command then wait for more than 39us
	HLCD_voidSendCommand(ENTRY_MODE_SET);
	_delay_ms(1);

}

void HLCD_voidClearDisplay(void)
{
	// Display Clear Command then wait for more than 1.53ms
	HLCD_voidSendCommand(DISPLAY_CLEAR);
	_delay_ms(2);
}

void HLCD_voidDisplayString(u8 *A_8uPtrToString)
{
	while (*A_8uPtrToString > 0)
	{
		HLCD_voidSendData(*A_8uPtrToString++);
	}
}


void HLCD_voidGoToPos (LCD_ROW_e A_LCDRow, LCD_COL_e A_LCDCol)
{
	switch (A_LCDRow)
	{
	case LCD_ROW1:
		HLCD_voidSendCommand(ROW1_BASE_ADD + A_LCDCol);
		break;
	case LCD_ROW2:
		HLCD_voidSendCommand(ROW2_BASE_ADD + A_LCDCol);
		break;
	default:
		break;
	}
}

void HLCD_voidDisplayNumber (u32 A_u32Number)
{
	u32 local_u32Num = 1;
	if (A_u32Number == 0)
	{
		HLCD_voidSendData('0');
	}

	while (A_u32Number != 0)
	{
		local_u32Num = (local_u32Num * 10) + (A_u32Number % 10);
		A_u32Number = A_u32Number / 10;
	}
	while (local_u32Num != 1)
	{
		HLCD_voidSendData ((local_u32Num % 10) + 48);
		local_u32Num = local_u32Num / 10;
	}
}


void HLCD_voidSendSpecialSymbol (u8 *A_pu8SymbolArray, LCD_PATTERNS_e A_PatternNum,LCD_ROW_e A_RowNo, LCD_COL_e A_ColNo)
{
	u8 local_u8CGRAMAddress;

	// Calculate CGRAM Address
	local_u8CGRAMAddress = A_PatternNum * 8;
	SET_BIT(local_u8CGRAMAddress,6);
	// Send Set CGRAM Address Command
	HLCD_voidSendCommand(local_u8CGRAMAddress);

	for (u8 local_u8Counter=0; local_u8Counter<8; local_u8Counter++)
	{
		// Send Byte by Byte from the Symbol Array
		HLCD_voidSendData(A_pu8SymbolArray[local_u8Counter]);
	}

	// Send Command to Set DDRAM Address
	HLCD_voidGoToPos(A_RowNo, A_ColNo);
	// Display Pattern
	HLCD_voidSendData(A_PatternNum);
}
