################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include emlib/subdir.mk
-include CMSIS/EFR32MG21/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: BRD4181A_EFR32MG21_iadc_scan_ldma.axf

# Tool invocations
BRD4181A_EFR32MG21_iadc_scan_ldma.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g3 -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "BRD4181A_EFR32MG21_iadc_scan_ldma.ld" -Xlinker --gc-sections -Xlinker -Map="BRD4181A_EFR32MG21_iadc_scan_ldma.map" -mfpu=fpv5-sp-d16 -mfloat-abi=softfp --specs=nano.specs -o BRD4181A_EFR32MG21_iadc_scan_ldma.axf "./CMSIS/EFR32MG21/startup_efr32mg21.o" "./CMSIS/EFR32MG21/system_efr32mg21.o" "./emlib/em_cmu.o" "./emlib/em_core.o" "./emlib/em_emu.o" "./emlib/em_gpio.o" "./emlib/em_iadc.o" "./emlib/em_ldma.o" "./emlib/em_system.o" "./src/main_scan_ldma.o" "./src/single_iadc.o" -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building hex file: BRD4181A_EFR32MG21_iadc_scan_ldma.hex'
	arm-none-eabi-objcopy -O ihex "BRD4181A_EFR32MG21_iadc_scan_ldma.axf" "BRD4181A_EFR32MG21_iadc_scan_ldma.hex"
	@echo ' '

	@echo 'Building bin file: BRD4181A_EFR32MG21_iadc_scan_ldma.bin'
	arm-none-eabi-objcopy -O binary "BRD4181A_EFR32MG21_iadc_scan_ldma.axf" "BRD4181A_EFR32MG21_iadc_scan_ldma.bin"
	@echo ' '

	@echo 'Building s37 file: BRD4181A_EFR32MG21_iadc_scan_ldma.s37'
	arm-none-eabi-objcopy -O srec "BRD4181A_EFR32MG21_iadc_scan_ldma.axf" "BRD4181A_EFR32MG21_iadc_scan_ldma.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "BRD4181A_EFR32MG21_iadc_scan_ldma.axf" -A
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) BRD4181A_EFR32MG21_iadc_scan_ldma.axf
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
