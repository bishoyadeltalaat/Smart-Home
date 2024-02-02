################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/App.c \
../Src/DIO_Program.c \
../Src/EEPROM_program.c \
../Src/EXTI_Program.c \
../Src/GI_program.c \
../Src/LCD_Program.c \
../Src/LED_Program.c \
../Src/SMARTHOME_Program.c \
../Src/TIMERS_Program.c \
../Src/TWI_program.c \
../Src/UART_Prgoram.c 

OBJS += \
./Src/App.o \
./Src/DIO_Program.o \
./Src/EEPROM_program.o \
./Src/EXTI_Program.o \
./Src/GI_program.o \
./Src/LCD_Program.o \
./Src/LED_Program.o \
./Src/SMARTHOME_Program.o \
./Src/TIMERS_Program.o \
./Src/TWI_program.o \
./Src/UART_Prgoram.o 

C_DEPS += \
./Src/App.d \
./Src/DIO_Program.d \
./Src/EEPROM_program.d \
./Src/EXTI_Program.d \
./Src/GI_program.d \
./Src/LCD_Program.d \
./Src/LED_Program.d \
./Src/SMARTHOME_Program.d \
./Src/TIMERS_Program.d \
./Src/TWI_program.d \
./Src/UART_Prgoram.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


