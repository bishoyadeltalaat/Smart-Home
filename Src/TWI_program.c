
#include "../include/LIB/STD_TYPES.h"
#include "../include/LIB/BIT_MATH.h"


#include "../include/MCAL/TWI/TWI_interface.h"
#include "../include/MCAL/TWI/TWI_private.h"
#include "../include/MCAL/TWI/TWI_config.h"

/*Set Master Address to 0 if master will not be addressed*/
void TWI_voidInitMaster(u8 Copy_u8Address)
{
	/*Enable Acknowledge Bit*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*Set SCL frequency to 100KHz, with 8MHz system frequency*/
	/*1- Set TWBR = 2*/
	TWBR = 2;
	/*2- Clear The Prescaler bit (TWPS0 - TWPS1)*/
	CLR_BIT(TWSR, TWSR_TWPS0);
	CLR_BIT(TWSR, TWSR_TWPS1);

	/*Check if the master node will be addressed or not*/
	if(Copy_u8Address == 0)
	{
		/*Do Nothing*/
	}
	else
	{
		/*Set The Required Address to The Master*/ //bits from 1 to 7
		TWAR = (Copy_u8Address << 1);
	}

	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}

void TWI_voidInitSlave(u8 Copy_u8Address)
{
	/*Set The Required Address to The Slave*/
	TWAR = Copy_u8Address << 1;

	/*Enable Acknowledge Bit*/
	SET_BIT(TWCR, TWCR_TWEA);

	/*Enable TWI*/
	SET_BIT(TWCR, TWCR_TWEN);
}


TWI_ErrorStatus_t TWI_ErrorStatusSendStartConditionWithACK(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Send Start Condition Bit*/
	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	if((TWSR & STATUS_BIT_MASK) != START_ACK)
	{
		Local_ErrorStatus = StartConditionError;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusSendRepeatedStartConditionWithACK(void)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;
	// clear INT flag
	// Send Repeated Start Condition
	// Enable TWI
	TWCR |= (1 << TWCR_TWINT) | (1 << TWCR_TWSTA) | (1 << TWCR_TWEN);
	/*Send Start Condition Bit*/
	//	SET_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	//	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	/*Check For The Condition Status Code*/
	if((TWSR & STATUS_BIT_MASK) != REP_START_ACK)
	{
		Local_ErrorStatus = RepeatedStartError;
	}
	else
	{
		/*Do Nothing*/
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusSendSlaveAddressWithWriteACK(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Set 7 bits slave address to the bus*/
	TWDR = (Copy_u8SlaveAddress << 1);

	/*Set The Write Request in the LSB in the data Register*/
	CLR_BIT(TWDR, TWDR_TWD0);

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	/*Check For The Condition Status Code*/
	if((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_WR_ACK)
	{
		Local_ErrorStatus = SlaveAddressWithWriteError;
	}
	return Local_ErrorStatus;
}



TWI_ErrorStatus_t TWI_ErrorStatusSendSlaveAddressWithReadACK(u8 Copy_u8SlaveAddress)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Set 7 bits slave address to the bus*/
	TWDR = Copy_u8SlaveAddress << 1;

	/*Set The Read Request in the LSB in the data Register*/
	SET_BIT(TWDR, TWDR_TWD0);

	/*Clear The Start Condition Bit*/
	CLR_BIT(TWCR, TWCR_TWSTA);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	/*Check For The Condition Status Code*/
	if((TWSR & STATUS_BIT_MASK) != SLAVE_ADD_AND_RD_ACK)
	{
		Local_ErrorStatus = SlaveAddressWithReadError;
	}
	return Local_ErrorStatus;
}




TWI_ErrorStatus_t TWI_ErrorStatusMasterWriteDataByteWithACK(u8 Copy_u8DataByte)
{

	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Set The Data To The TWDR Register*/
	TWDR = Copy_u8DataByte;

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	/*Check For The Condition Status Code*/
	if((TWSR & STATUS_BIT_MASK) != MSTR_WR_BYTE_ACK)
	{
		Local_ErrorStatus = MasterWriteByteWithACKError;
	}
	return Local_ErrorStatus;
}


TWI_ErrorStatus_t TWI_ErrorStatusMasterReadDataByteWithACK(u8 * Copy_pu8ReceivedByte)
{
	TWI_ErrorStatus_t Local_ErrorStatus = NoError;

	/*Clear The TWINT Flag, To Make The Slave To Send its Data*/
	SET_BIT(TWCR, TWCR_TWINT);

	/*wait until the operation finishes and the flag is raised again*/
	while(GET_BIT(TWCR, TWCR_TWINT) == 0 );

	/*Check For The Condition Status Code*/
	if((TWSR & STATUS_BIT_MASK) != MSTR_RD_BYTE_WITH_ACK)
	{
		Local_ErrorStatus = MasterReadByteWithACKError;
	}
	else
	{
		/*Read The Received Data*/
		*Copy_pu8ReceivedByte = TWDR;
	}

	return Local_ErrorStatus;

}


void TWI_voidSendStopCondition(void)
{
	/*Send a stop condition on the bus*/
	SET_BIT(TWCR, TWCR_TWSTO);

	/*Clear The TWINT Flag*/
	SET_BIT(TWCR, TWCR_TWINT);
}








