################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/BQ25690_Driver.c \
../Src/BqLayout.c \
../Src/MeasLayout.c \
../Src/OLED_Driver.c \
../Src/PAC193x_Driver.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/BQ25690_Driver.o \
./Src/BqLayout.o \
./Src/MeasLayout.o \
./Src/OLED_Driver.o \
./Src/PAC193x_Driver.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/BQ25690_Driver.d \
./Src/BqLayout.d \
./Src/MeasLayout.d \
./Src/OLED_Driver.d \
./Src/PAC193x_Driver.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DSTM32C011F4Ux -DSTM32 -DSTM32C0 -c -I../Inc -I"C:/Users/Benjamin/STM32CubeIDE/workspace_2.2.0/SolarPowerbankControl/ST_Framework/Inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/BQ25690_Driver.cyclo ./Src/BQ25690_Driver.d ./Src/BQ25690_Driver.o ./Src/BQ25690_Driver.su ./Src/BqLayout.cyclo ./Src/BqLayout.d ./Src/BqLayout.o ./Src/BqLayout.su ./Src/MeasLayout.cyclo ./Src/MeasLayout.d ./Src/MeasLayout.o ./Src/MeasLayout.su ./Src/OLED_Driver.cyclo ./Src/OLED_Driver.d ./Src/OLED_Driver.o ./Src/OLED_Driver.su ./Src/PAC193x_Driver.cyclo ./Src/PAC193x_Driver.d ./Src/PAC193x_Driver.o ./Src/PAC193x_Driver.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

