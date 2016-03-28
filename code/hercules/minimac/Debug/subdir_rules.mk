################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --diag_wrap=off --display_error_number --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

md5.obj: ../md5.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --diag_wrap=off --display_error_number --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="md5.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sha1.obj: ../sha1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --diag_wrap=off --display_error_number --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="sha1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sha256.obj: ../sha256.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --abi=eabi --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-arm_5.2.7/include" -g --diag_wrap=off --display_error_number --diag_warning=225 --enum_type=packed --preproc_with_compile --preproc_dependency="sha256.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


