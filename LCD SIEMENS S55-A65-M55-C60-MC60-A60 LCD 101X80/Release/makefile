################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
s55Display.lss \

FLASH_IMAGE += \
s55Display.hex \

EEPROM_IMAGE += \
s55Display.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: s55Display.elf secondary-outputs

# Tool invocations
s55Display.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,s55Display.map -mmcu=atmega8 -o"s55Display.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

s55Display.lss: s55Display.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S s55Display.elf  >"s55Display.lss"
	@echo 'Finished building: $@'
	@echo ' '

s55Display.hex: s55Display.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex s55Display.elf  "s55Display.hex"
	@echo 'Finished building: $@'
	@echo ' '

s55Display.eep: s55Display.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex s55Display.elf  "s55Display.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: s55Display.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=berkeley -t s55Display.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(ASM_DEPS)$(EEPROM_IMAGE)$(FLASH_IMAGE)$(ELFS)$(LSS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS) s55Display.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
