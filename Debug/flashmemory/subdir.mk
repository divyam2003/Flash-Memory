################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../flashmemory/flashm.c \
../flashmemory/main.c 

OBJS += \
./flashmemory/flashm.o \
./flashmemory/main.o 

C_DEPS += \
./flashmemory/flashm.d \
./flashmemory/main.d 


# Each subdirectory must supply rules for building sources it contributes
flashmemory/%.o: ../flashmemory/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GNU C Compiler'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -I/HP/RTOSDemo_Hardware_Platform/drivers/mss_spi/mss_spi.h -I"D:\cdh\softconsol\HP\RTOSDemo_Hardware_Platform\drivers\mss_spi\mss_spi.h" -I/HP/RTOSDemo_Hardware_Platform/drivers/mss_gpio/mss_gpio.h -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


