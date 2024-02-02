/*************************************************************************/
/* !File Name:         TWI_interface.h                                     */
/* !Layer    :         HAL                                              */
/* !Author   :         Abdullah M. Abdullah                              */
/* !Date     :         2 SEP, 2021                                       */
/* !Version  :         v1.0                                              */
/*************************************************************************/

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidSendDataByte(u16 Copy_u16LocationAddress, u8 Copy_u8DataByte);

u8 EEPROM_u8ReadDataByte(u16 Copy_u16LocationAddress);

#endif
