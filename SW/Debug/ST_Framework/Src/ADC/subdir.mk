################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST_Framework/Src/ADC/ADC.c 

OBJS += \
./ST_Framework/Src/ADC/ADC.o 

C_DEPS += \
./ST_Framework/Src/ADC/ADC.d 


# Each subdirectory must supply rules for building sources it contributes
ST_Framework/Src/ADC/%.o ST_Framework/Src/ADC/%.su ST_Framework/Src/ADC/%.cyclo: ../ST_Framework/Src/ADC/%.c ST_Framework/Src/ADC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST_Framework-2f-Src-2f-ADC

clean-ST_Framework-2f-Src-2f-ADC:
	-$(RM) ./ST_Framework/Src/ADC/ADC.cyclo ./ST_Framework/Src/ADC/ADC.d ./ST_Framework/Src/ADC/ADC.o ./ST_Framework/Src/ADC/ADC.su

.PHONY: clean-ST_Framework-2f-Src-2f-ADC

