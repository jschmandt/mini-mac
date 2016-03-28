################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="main.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

md5.obj: ../md5.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="md5.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sha1.obj: ../sha1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="sha1.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

sha256.obj: ../sha256.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="sha256.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


