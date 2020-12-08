################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --fp_mode=strict --include_path="D:/CLG/Automotive Embedded/Projects/MASTER_ECU" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --strict_ansi --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --check_misra="2,-2.2,3,4,5,6,7,8,9,10,11,-11.3,-11.4,12,13,14,15,16,17,18,19,-19.4,20" --misra_advisory=warning --misra_required=warning --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SYSTICK.obj: ../SYSTICK.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --fp_mode=strict --include_path="D:/CLG/Automotive Embedded/Projects/MASTER_ECU" --include_path="C:/ti/TivaWare_C_Series-2.1.4.178" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.4.LTS/include" --define=ccs="ccs" --define=PART_TM4C123GH6PM -g --strict_ansi --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --check_misra="2,-2.2,3,4,5,6,7,8,9,10,11,-11.3,-11.4,12,13,14,15,16,17,18,19,-19.4,20" --misra_advisory=warning --misra_required=warning --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


