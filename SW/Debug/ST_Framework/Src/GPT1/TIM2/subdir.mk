################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST_Framework/Src/GPT1/TIM2/TIM2.c 

OBJS += \
./ST_Framework/Src/GPT1/TIM2/TIM2.o 

C_DEPS += \
./ST_Framework/Src/GPT1/TIM2/TIM2.d 


# Each subdirectory must supply rules for building sources it contributes
ST_Framework/Src/GPT1/TIM2/%.o ST_Framework/Src/GPT1/TIM2/%.su ST_Framework/Src/GPT1/TIM2/%.cyclo: ../ST_Framework/Src/GPT1/TIM2/%.c ST_Framework/Src/GPT1/TIM2/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST_Framework-2f-Src-2f-GPT1-2f-TIM2

clean-ST_Framework-2f-Src-2f-GPT1-2f-TIM2:
	-$(RM) ./ST_Framework/Src/GPT1/TIM2/TIM2.cyclo ./ST_Framework/Src/GPT1/TIM2/TIM2.d ./ST_Framework/Src/GPT1/TIM2/TIM2.o ./ST_Framework/Src/GPT1/TIM2/TIM2.su

.PHONY: clean-ST_Framework-2f-Src-2f-GPT1-2f-TIM2

