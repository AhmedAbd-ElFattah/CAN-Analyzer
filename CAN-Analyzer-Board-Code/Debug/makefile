################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include STM32_Drivers_Configurations/subdir.mk
-include STM32-Drivers/LMCAL/SYSTICK/subdir.mk
-include STM32-Drivers/LMCAL/SCB/subdir.mk
-include STM32-Drivers/LMCAL/NVIC/subdir.mk
-include STM32-Drivers/LIB/RandomNumberGenerator/subdir.mk
-include STM32-Drivers/LIB/Delay/subdir.mk
-include STM32-Drivers/LIB/CRC/subdir.mk
-include STM32-Drivers/LIB/subdir.mk
-include STM32-Drivers/HMCAL/USART/subdir.mk
-include STM32-Drivers/HMCAL/TIM/subdir.mk
-include STM32-Drivers/HMCAL/SYSCFG/subdir.mk
-include STM32-Drivers/HMCAL/SPI/subdir.mk
-include STM32-Drivers/HMCAL/RCC/subdir.mk
-include STM32-Drivers/HMCAL/Interrupt/subdir.mk
-include STM32-Drivers/HMCAL/IWDG/subdir.mk
-include STM32-Drivers/HMCAL/GPIO/subdir.mk
-include STM32-Drivers/HMCAL/FMI/subdir.mk
-include STM32-Drivers/HMCAL/EXTI/subdir.mk
-include STM32-Drivers/HMCAL/DMA/subdir.mk
-include STM32-Drivers/HMCAL/DAC/subdir.mk
-include STM32-Drivers/HMCAL/CAN/subdir.mk
-include STM32-Drivers/HMCAL/ADC/subdir.mk
-include STM32-Drivers/HAL/TFTLCD/subdir.mk
-include STM32-Drivers/HAL/SevenSegment_Module56D330/subdir.mk
-include STM32-Drivers/HAL/SevenSegment/subdir.mk
-include STM32-Drivers/HAL/ServoMotor/subdir.mk
-include STM32-Drivers/HAL/LED/subdir.mk
-include STM32-Drivers/HAL/Keypad/subdir.mk
-include STM32-Drivers/HAL/DCMotor/subdir.mk
-include STM32-Drivers/HAL/Buzzer/subdir.mk
-include STM32-Drivers/HAL/Button/subdir.mk
-include Application/src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := CAN-Analyzer-Board-Code
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
CAN-Analyzer-Board-Code.elf \

MAP_FILES += \
CAN-Analyzer-Board-Code.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
CAN-Analyzer-Board-Code.list \


# All Target
all: main-build

# Main-build Target
main-build: CAN-Analyzer-Board-Code.elf secondary-outputs

# Tool invocations
CAN-Analyzer-Board-Code.elf CAN-Analyzer-Board-Code.map: $(OBJS) $(USER_OBJS) /home/ahmed/Desktop/Github/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32F446RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "CAN-Analyzer-Board-Code.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/ahmed/Desktop/Github/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32F446RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="CAN-Analyzer-Board-Code.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

CAN-Analyzer-Board-Code.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "CAN-Analyzer-Board-Code.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) CAN-Analyzer-Board-Code.elf CAN-Analyzer-Board-Code.list CAN-Analyzer-Board-Code.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
