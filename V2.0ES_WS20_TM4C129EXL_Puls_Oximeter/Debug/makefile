################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main.obj" \
"./tm4c129encpdt_startup_ccs.obj" \
"./booster_pack_display/CFAF128128B0145T.obj" \
"./source/ADC.obj" \
"./source/Beeper.obj" \
"./source/Button.obj" \
"./source/Calculation.obj" \
"./source/DAC_MCP4728.obj" \
"./source/Delay.obj" \
"./source/FIFO.obj" \
"./source/Init.obj" \
"./source/LCD.obj" \
"./source/LUT.obj" \
"./source/OMM_Modul.obj" \
"./source/PWM.obj" \
"./source/Processing.obj" \
"./source/Safety_Modul.obj" \
"./source/Timer.obj" \
"./source/UART.obj" \
"../tm4c129encpdt.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/Tools/TexasInstruments/TivaWare_C_Series-2.2.0.295/driverlib/ccs/Debug/driverlib.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include booster_pack_display/subdir_vars.mk
-include source/subdir_vars.mk
-include subdir_rules.mk
-include booster_pack_display/subdir_rules.mk
-include source/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Puls_Oximeter_final_old.out \

EXE_OUTPUTS__QUOTED += \
"Puls_Oximeter_final_old.out" \

BIN_OUTPUTS += \
Puls_Oximeter_final_old.hex \

BIN_OUTPUTS__QUOTED += \
"Puls_Oximeter_final_old.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "Puls_Oximeter_final_old.out"

# Tool invocations
Puls_Oximeter_final_old.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --define=ccs="ccs" --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"Puls_Oximeter_final_old.map" --heap_size=0 --stack_size=512 -i"C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/lib" -i"C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="Puls_Oximeter_final_old_linkInfo.xml" --rom_model -o "Puls_Oximeter_final_old.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Puls_Oximeter_final_old.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armhex"  -o "Puls_Oximeter_final_old.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "main.obj" "tm4c129encpdt_startup_ccs.obj" "booster_pack_display\CFAF128128B0145T.obj" "source\ADC.obj" "source\Beeper.obj" "source\Button.obj" "source\Calculation.obj" "source\DAC_MCP4728.obj" "source\Delay.obj" "source\FIFO.obj" "source\Init.obj" "source\LCD.obj" "source\LUT.obj" "source\OMM_Modul.obj" "source\PWM.obj" "source\Processing.obj" "source\Safety_Modul.obj" "source\Timer.obj" "source\UART.obj" 
	-$(RM) "main.d" "tm4c129encpdt_startup_ccs.d" "booster_pack_display\CFAF128128B0145T.d" "source\ADC.d" "source\Beeper.d" "source\Button.d" "source\Calculation.d" "source\DAC_MCP4728.d" "source\Delay.d" "source\FIFO.d" "source\Init.d" "source\LCD.d" "source\LUT.d" "source\OMM_Modul.d" "source\PWM.d" "source\Processing.d" "source\Safety_Modul.d" "source\Timer.d" "source\UART.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

