################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../ST_Framework/Src/Utilities/Dabler.s 

C_SRCS += \
../ST_Framework/Src/Utilities/Utilities.c 

OBJS += \
./ST_Framework/Src/Utilities/Dabler.o \
./ST_Framework/Src/Utilities/Utilities.o 

S_DEPS += \
./ST_Framework/Src/Utilities/Dabler.d 

C_DEPS += \
./ST_Framework/Src/Utilities/Utilities.d 


# Each subdirectory must supply rules for building sources it contributes
ST_Framework/Src/Utilities/%.o: ../ST_Framework/Src/Utilities/%.s ST_Framework/Src/Utilities/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
ST_Framework/Src/Utilities/%.o ST_Framework/Src/Utilities/%.su ST_Framework/Src/Utilities/%.cyclo: ../ST_Framework/Src/Utilities/%.c ST_Framework/Src/Utilities/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ST_Framework-2f-Src-2f-Utilities

clean-ST_Framework-2f-Src-2f-Utilities:
	-$(RM) ./ST_Framework/Src/Utilities/Dabler.d ./ST_Framework/Src/Utilities/Dabler.o ./ST_Framework/Src/Utilities/Utilities.cyclo ./ST_Framework/Src/Utilities/Utilities.d ./ST_Framework/Src/Utilities/Utilities.o ./ST_Framework/Src/Utilities/Utilities.su

.PHONY: clean-ST_Framework-2f-Src-2f-Utilities

