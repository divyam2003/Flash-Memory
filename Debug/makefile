################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
MEMORYMAP += \
memory-map.xml \

IHEXFILES += \
FM.hex \

SRECFILES += \
FM.srec \

LISTINGS += \
FM.lst \


# All Target
all: FM secondary-outputs

# Tool invocations
FM: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU C Linker'
	arm-none-eabi-gcc -mthumb -mcpu=cortex-m3 -specs=bare.specs -Wl,-Map=$(EXECUTABLE).map -o"FM" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

memory-map.xml: $(EXECUTABLE)
	@echo 'Invoking: Memory map generator'
	actel-map -o "memory-map.xml" $(EXECUTABLE) $(BUILDCMD)
	@echo 'Finished building: $@'
	@echo ' '

FM.hex: $(EXECUTABLE)
	@echo 'Invoking: GNU Intel Hex File Generator'
	arm-none-eabi-objcopy -O ihex $(EXECUTABLE) "FM.hex"
	@echo 'Finished building: $@'
	@echo ' '

FM.srec: $(EXECUTABLE)
	@echo 'Invoking: GNU S-Record Generator'
	arm-none-eabi-objcopy -O srec $(EXECUTABLE) "FM.srec"
	@echo 'Finished building: $@'
	@echo ' '

FM.lst: $(EXECUTABLE)
	@echo 'Invoking: GNU Listing Generator'
	arm-none-eabi-objdump -h -S $(EXECUTABLE) > "FM.lst"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean::
	-$(RM) $(MEMORYMAP)$(OBJS)$(C_DEPS)$(SRECFILES)$(IHEXFILES)$(LISTINGS)$(EXECUTABLE) FM
	-@echo ' '

secondary-outputs: $(MEMORYMAP) $(IHEXFILES) $(SRECFILES) $(LISTINGS)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
