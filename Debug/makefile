################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/wav/subdir.mk
-include src/fatfs/subdir.mk
-include src/subdir.mk
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
all: NewPlayer.axf

# Tool invocations
NewPlayer.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"/home/evaota/LPCXpresso/workspace/CMSISv1p30_LPC11xx/Debug" -Xlinker -Map="NewPlayer.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "NewPlayer_Debug.ld" -o "NewPlayer.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) NewPlayer.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "NewPlayer.axf"; # arm-none-eabi-objcopy -v -O binary "NewPlayer.axf" "NewPlayer.bin" ; # checksum -p LPC1114FN_102 -d "NewPlayer.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
