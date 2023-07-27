################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../flashm.c \
../main.c 

OBJS += \
./flashm.o \
./main.o 

C_DEPS += \
./flashm.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -I"C:\Program Files (x86)\Microsemi\SoftConsole v3.4\Arm\Inc" -I"D:\cdh\softconsol\FM" -I"D:\cdh\softconsol\HP\hal" -I"D:\cdh\softconsol\HP\drivers\mss_gpio" -I"D:\cdh\softconsol\HP\drivers\mss_spi" -I"D:\cdh\softconsol\HP\CMSIS" -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


