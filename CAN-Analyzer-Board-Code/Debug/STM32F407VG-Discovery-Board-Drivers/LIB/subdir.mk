################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F407VG-Discovery-Board-Drivers/LIB/utils.c 

OBJS += \
./STM32F407VG-Discovery-Board-Drivers/LIB/utils.o 

C_DEPS += \
./STM32F407VG-Discovery-Board-Drivers/LIB/utils.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F407VG-Discovery-Board-Drivers/LIB/%.o STM32F407VG-Discovery-Board-Drivers/LIB/%.su STM32F407VG-Discovery-Board-Drivers/LIB/%.cyclo: ../STM32F407VG-Discovery-Board-Drivers/LIB/%.c STM32F407VG-Discovery-Board-Drivers/LIB/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32F407VG-Discovery-Board-Drivers" -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/CAN-Analyzer/CAN-Analyzer-Board-Code/Application/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LIB

clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LIB:
	-$(RM) ./STM32F407VG-Discovery-Board-Drivers/LIB/utils.cyclo ./STM32F407VG-Discovery-Board-Drivers/LIB/utils.d ./STM32F407VG-Discovery-Board-Drivers/LIB/utils.o ./STM32F407VG-Discovery-Board-Drivers/LIB/utils.su

.PHONY: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LIB

