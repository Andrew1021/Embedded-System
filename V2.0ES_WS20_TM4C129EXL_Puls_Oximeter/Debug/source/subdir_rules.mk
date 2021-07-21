################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
source/%.obj: ../source/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/Studium/Embedded_Systems/GitRepo/group5/V2.0ES_WS20_TM4C129EXL_Puls_Oximeter" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.2.0.295/examples/boards/ek-tm4c1294xl" --include_path="C:/Tools/TexasInstruments/TivaWare_C_Series-2.2.0.295" --include_path="C:/Tools/TexasInstruments/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.1.LTS/include" --define=ccs="ccs" --define=TARGET_IS_TM4C129_RA0 --define=PART_TM4C129ENCPDT -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="source/$(basename $(<F)).d_raw" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


