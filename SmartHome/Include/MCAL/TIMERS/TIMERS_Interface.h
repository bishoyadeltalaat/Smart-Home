#ifndef INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_
#define INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_

#define NORMAL_MODE			0
#define PHASE_CORRECT_MODE  1
#define CTC_MODE			2
#define FAST_PWM_MODE		3



void MTIMER0_voidInit (void);
void MTIMER0_voidSetPreloadValue (u8 A_u8NoOfTicks);
void MTIMER0_voidSetOVFCallback (void (*A_PtrToFunc)(void));
void MTIMER0_voidSetCTCCallback (void (*A_PtrToFunc)(void));
void MTIMER0_voidSetOCR0Value (u8 A_u8OCR0Value);
void MTIMER0_voidStopTimer (void);
void MTIMER1_voidInit();
void MTIMER1_voidSetOCR1AValue(u16 A_u16value);
void MTIMER1_voidICUSWInit();
void MTIMER1_voidSetTimer1Value(u16 A_u16Value);
u16 MTIMER1_u16ReadTimer1Value(void);

#endif /* INCLUDE_MCAL_TIMERS_TIMERS_INTERFACE_H_ */
