################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.c 

OBJS += \
./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.o 

C_DEPS += \
./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.d 


# Each subdirectory must supply rules for building sources it contributes
STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/%.o STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/%.su STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/%.cyclo: ../STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/%.c STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F446RETx -c -I../Inc -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/CAN-Analyzer/CAN-Analyzer-Board-Code/STM32F407VG-Discovery-Board-Drivers" -I"/home/ahmed/Desktop/MyFiles/MyProject-FinalCV/CAN-Analyzer/CAN-Analyzer-Board-Code/Application/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-NVIC

clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-NVIC:
	-$(RM) ./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.cyclo ./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.d ./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.o ./STM32F407VG-Discovery-Board-Drivers/LMCAL/NVIC/NVIC.su

.PHONY: clean-STM32F407VG-2d-Discovery-2d-Board-2d-Drivers-2f-LMCAL-2f-NVIC

