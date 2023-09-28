################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application/src/CANAnalyzer.c 

OBJS += \
./Application/src/CANAnalyzer.o 

C_DEPS += \
./Application/src/CANAnalyzer.d 


# Each subdirectory must supply rules for building sources it contributes
Application/src/%.o Application/src/%.su Application/src/%.cyclo: ../Application/src/%.c Application/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/ahmed/Desktop/Github/CAN-Analyzer/CAN-Analyzer-Board-Code/Application/inc" -I"/home/ahmed/Desktop/Github/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32-Drivers" -I"/home/ahmed/Desktop/Github/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32_Drivers_Configurations" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-src

clean-Application-2f-src:
	-$(RM) ./Application/src/CANAnalyzer.cyclo ./Application/src/CANAnalyzer.d ./Application/src/CANAnalyzer.o ./Application/src/CANAnalyzer.su

.PHONY: clean-Application-2f-src

