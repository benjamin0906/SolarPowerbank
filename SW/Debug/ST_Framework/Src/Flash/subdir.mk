################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ST_Framework/Src/Flash/Flash.c 

OBJS += \
./ST_Framework/Src/Flash/Flash.o 

C_DEPS += \
./ST_Framework/Src/Flash/Flash.d 


# Each subdirectory must supply rules for building sources it contributes
ST_Framework/Src/Flash/%.o ST_Framework/Src/Flash/%.su ST_Framework/Src/Flash/%.cyclo: ../ST_Framework/Src/Flash/%.c ST_Framework/Src/Flash/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST_Framework-2f-Src-2f-Flash

clean-ST_Framework-2f-Src-2f-Flash:
	-$(RM) ./ST_Framework/Src/Flash/Flash.cyclo ./ST_Framework/Src/Flash/Flash.d ./ST_Framework/Src/Flash/Flash.o ./ST_Framework/Src/Flash/Flash.su

.PHONY: clean-ST_Framework-2f-Src-2f-Flash

