################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (14.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include ST_Framework/Src/VREFBUF/subdir.mk
-include ST_Framework/Src/Utilities/subdir.mk
-include ST_Framework/Src/USART/subdir.mk
-include ST_Framework/Src/TIM6_7/subdir.mk
-include ST_Framework/Src/TIM17/subdir.mk
-include ST_Framework/Src/TIM15/subdir.mk
-include ST_Framework/Src/TIM14/subdir.mk
-include ST_Framework/Src/TIM11/subdir.mk
-include ST_Framework/Src/SysTick/subdir.mk
-include ST_Framework/Src/SYSCFG/subdir.mk
-include ST_Framework/Src/SPI/subdir.mk
-include ST_Framework/Src/RTC/subdir.mk
-include ST_Framework/Src/RCC/subdir.mk
-include ST_Framework/Src/Pwr/subdir.mk
-include ST_Framework/Src/NVIC/subdir.mk
-include ST_Framework/Src/I2C/subdir.mk
-include ST_Framework/Src/GPT1/TIM5/subdir.mk
-include ST_Framework/Src/GPT1/TIM3/subdir.mk
-include ST_Framework/Src/GPT1/TIM2/subdir.mk
-include ST_Framework/Src/GPT/subdir.mk
-include ST_Framework/Src/GPIO/subdir.mk
-include ST_Framework/Src/Flash/subdir.mk
-include ST_Framework/Src/EXTI/subdir.mk
-include ST_Framework/Src/DMAMUX/subdir.mk
-include ST_Framework/Src/DMA/subdir.mk
-include ST_Framework/Src/DBG/subdir.mk
-include ST_Framework/Src/DAC/subdir.mk
-include ST_Framework/Src/Core/subdir.mk
-include ST_Framework/Src/BasicTIM/subdir.mk
-include ST_Framework/Src/ADC/subdir.mk
-include ST_Framework/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := SolarPowerbankControl
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
SolarPowerbankControl.elf \

MAP_FILES += \
SolarPowerbankControl.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
SolarPowerbankControl.list \


# All Target
all: main-build

# Main-build Target
main-build: SolarPowerbankControl.elf secondary-outputs

# Tool invocations
SolarPowerbankControl.elf SolarPowerbankControl.map: $(OBJS) $(USER_OBJS) C:\Users\Benjamin\STM32CubeIDE\workspace_2.2.0\SolarPowerbankControl\STM32C011F4UX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "SolarPowerbankControl.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\Benjamin\STM32CubeIDE\workspace_2.2.0\SolarPowerbankControl\STM32C011F4UX_FLASH.ld" --specs=nosys.specs -Wl,-Map="SolarPowerbankControl.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

SolarPowerbankControl.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "SolarPowerbankControl.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) SolarPowerbankControl.elf SolarPowerbankControl.list SolarPowerbankControl.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
