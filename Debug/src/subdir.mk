################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/NewPlayer.c \
../src/PWM.c \
../src/SPI.c \
../src/Timer16_32.c \
../src/UART.c \
../src/cr_startup_lpc11xx.c \
../src/crp.c \
../src/xprintf.c 

OBJS += \
./src/NewPlayer.o \
./src/PWM.o \
./src/SPI.o \
./src/Timer16_32.o \
./src/UART.o \
./src/cr_startup_lpc11xx.o \
./src/crp.o \
./src/xprintf.o 

C_DEPS += \
./src/NewPlayer.d \
./src/PWM.d \
./src/SPI.d \
./src/Timer16_32.d \
./src/UART.d \
./src/cr_startup_lpc11xx.d \
./src/crp.d \
./src/xprintf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M0 -D__USE_CMSIS=CMSISv1p30_LPC11xx -D__LPC11XX__ -D__REDLIB__ -I"/home/evaota/LPCXpresso/workspace/CMSISv1p30_LPC11xx/inc" -O1 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


