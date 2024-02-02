/*
 * UART_Prgoram.c
 *
 *  Created on: May 4, 2023
 *      Author: abdelrahmanhossam
 */


#include <util/delay.h>
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"

#include "../include/MCAL/UART/UART_Interface.h"
#include "../include/MCAL/UART/UART_Private.h"
#include "../include/MCAL/UART/UART_Cfg.h"


#define F_CPU 8000000UL
#define NULL 0

static void (*FuncPtr[3]) (void) = {NULL,NULL,NULL};

void MUART_voidInit(void)
{
	u16 local_u16BaudRate = BAUD_RATE_EQUATION;
	// Set Baudrate
	UBRRL = (u8) local_u16BaudRate;
	UBRRH = (u8) (local_u16BaudRate >> 8);

	// Character Size 8-bit
	CLR_BIT(UCSRB,2);

	// Character Size 8-bit
	// Mode Asynchronous operation
	// Parity Disabled
	// 1 Stop Bit
	UCSRC = CONC_BIT(1,0,0,0,0,1,1,0);

	// Enable Receiver
	// Enable Transmitter
	SET_BIT(UCSRB,3);
	SET_BIT(UCSRB,4);
}


void MUART_voidSendByteSyncBlocking (u8 A_u8DataByte)
{
	// wait until UDR is empty
	while (GET_BIT(UCSRA,5)==0);

	// Set Data into Tx Register and start Transmission
	UDR = A_u8DataByte;

	// wait until UDR is empty
	while (GET_BIT(UCSRA,5)==0);

	// Clear transmit Interrupt flag
	SET_BIT(UCSRA,6);

}

void MUART_voidSendByteSyncNonBlocking (u8 A_u8DataByte)
{
	u32 local_u32Timeout=0;

	// wait until UDR is empty
	while (GET_BIT(UCSRA,5)==0)
	{
		local_u32Timeout++;
		if (local_u32Timeout == NON_BLOCKING_TIME_OUT)
		{
			break;
		}
	}

	if (local_u32Timeout != NON_BLOCKING_TIME_OUT)
	{
		local_u32Timeout = 0;
		// Set Data into Tx Register and start Transmission
		UDR = A_u8DataByte;
		// wait until UDR is empty
		while (GET_BIT(UCSRA,5)==0)
		{
			local_u32Timeout++;
			if (local_u32Timeout == NON_BLOCKING_TIME_OUT)
			{
				break;
			}
		}
		// Clear transmit Interrupt flag
		SET_BIT(UCSRA,6);
	}

}


void MUART_voidSendStringSyncNonBlocking (u8 *A_pu8String)
{
	while(*A_pu8String > 0)
	{
		MUART_voidSendByteSyncNonBlocking(*A_pu8String++);
	}
}


void MUART_voidSendByteAsync (u8 A_u8DataByte)
{
	// Check if Data Register is empty
	if (GET_BIT(UCSRA,5)==1)
	{
		// Send Data
		UDR = A_u8DataByte;
	}
}
void MUART_voidReceiveStringSync(u8 * Copy_u8ReceiveData){
	u8 counter =0;
	volatile u8 recChar;
	recChar =  MUART_u8ReadByteSyncBlocking();
	if(Copy_u8ReceiveData != NULL){
		while(recChar !=13){
			MUART_voidSendByteAsync(recChar);
			//read data
			Copy_u8ReceiveData[counter]= recChar;
			counter ++ ;
			recChar =  MUART_u8ReadByteSyncBlocking();

		}
	}
}

u8 MUART_u8ReadByteSyncBlocking (void)
{

	// Wait for Rx Flag
	while(GET_BIT(UCSRA,7)==0);

	return UDR;
}

u8 MUART_u8ReadByteAsync (void)
{
	return UDR;
}

u8 MUART_u8ReadByteSyncNonBlocking (void)
{
	u8 local_u8ReceivedData = NO_VALUE_RETURNED;
	u16 local_u16Timeout = 0;
	// Wait for Rx Flag
	while(GET_BIT(UCSRA,7)==0)
	{
		local_u16Timeout++;
		if (local_u16Timeout == NON_BLOCKING_TIME_OUT)
		{
			break;
		}
	}

	if (local_u16Timeout != NON_BLOCKING_TIME_OUT)
	{
		// Read Received Data from the UDR
		local_u8ReceivedData = UDR;
	}
	return local_u8ReceivedData;
}


void MUART_VoidSendNumber(u32 Copy_u32Data)
{
	/*Loop counter for the two Loops*/
	u8 Local_u8LoopCounter = 0;
	/*Extract single number in that variable*/
	u8 Local_u8SingleNumber = 0;
	/*Store number of Zeros at the end */
	u8 Local_Copy_u8DigitNumbers = 0;
	/*Store the reversed number*/
	u32 Local_Copy_u32DataReversed = 1;

	if(Copy_u32Data != 0)
	{
		while(Copy_u32Data != 0)
		{
			/*Extract Last single number from the whole number*/
			Local_u8SingleNumber = Copy_u32Data % 10;
			/*storing the number reversed*/
			Local_Copy_u32DataReversed = (Local_Copy_u32DataReversed*10) + (Local_u8SingleNumber);
			/*Delete the extracted number from the whole number*/
			Copy_u32Data /= 10;
			/*Increment the Loop counter*/
			Local_u8LoopCounter++;
			/*Counting the digit numbers*/
			Local_Copy_u8DigitNumbers++;
		}

		for(Local_u8LoopCounter = 0; Local_u8LoopCounter < Local_Copy_u8DigitNumbers; Local_u8LoopCounter++)
		{
			/*Extract Last single number from the whole number*/
			Local_u8SingleNumber = Local_Copy_u32DataReversed % 10;
			/*Delete the extracted number from the whole number*/
			Local_Copy_u32DataReversed /= 10;
			/*Sending the extracted single number Asci code from the Asci array to the LCD */
			 MUART_voidSendByteAsync('0' + Local_u8SingleNumber);
		}
	}
	else
	{
		/*Sending Char Zero*/
		 MUART_voidSendByteAsync('0');
	}
}



void MUART_voidSetCallBack (UART_INTERRUPTS_e A_InterruptSource , void (*A_PtoFunc)(void))
{
	if ((A_InterruptSource<=UART_TX_INTERRUPT)&&(A_PtoFunc != NULL))
	{
		FuncPtr [A_InterruptSource] = A_PtoFunc;
	}
}


void __vector_13(void) __attribute__((signal));
void __vector_13(void)
{
	if (FuncPtr[UART_RX_INTERRUPT] != NULL)
	{
		FuncPtr[UART_RX_INTERRUPT]();
	}
}

void __vector_14(void) __attribute__((signal));
void __vector_14(void)
{
	if (FuncPtr[UART_UDRE_INTERRUPT] != NULL)
	{
		FuncPtr[UART_UDRE_INTERRUPT]();
	}
}

void __vector_15(void) __attribute__((signal));
void __vector_15(void)
{
	if (FuncPtr[UART_TX_INTERRUPT] != NULL)
	{
		FuncPtr[UART_TX_INTERRUPT]();
	}
}
