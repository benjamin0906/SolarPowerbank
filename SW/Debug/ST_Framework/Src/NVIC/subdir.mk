################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST_Framework/Src/NVIC/NVIC.c 

OBJS += \
./ST_Framework/Src/NVIC/NVIC.o 

C_DEPS += \
./ST_Framework/Src/NVIC/NVIC.d 


# Each subdirectory must supply rules for building sources it contributes
ST_Framework/Src/NVIC/%.o ST_Framework/Src/NVIC/%.su ST_Framework/Src/NVIC/%.cyclo: ../ST_Framework/Src/NVIC/%.c ST_Framework/Src/NVIC/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST_Framework-2f-Src-2f-NVIC

clean-ST_Framework-2f-Src-2f-NVIC:
	-$(RM) ./ST_Framework/Src/NVIC/NVIC.cyclo ./ST_Framework/Src/NVIC/NVIC.d ./ST_Framework/Src/NVIC/NVIC.o ./ST_Framework/Src/NVIC/NVIC.su

.PHONY: clean-ST_Framework-2f-Src-2f-NVIC

