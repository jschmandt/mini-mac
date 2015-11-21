################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
openssl/md5_dgst.obj: ../openssl/md5_dgst.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API/USB_Common" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib/MSP430F5xx_6xx/inc" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_app" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_config" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="openssl/md5_dgst.pp" --obj_directory="openssl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

openssl/md5_one.obj: ../openssl/md5_one.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/bin/cl430" -vmspx --abi=eabi --data_model=restricted --use_hw_mpy=F5 --include_path="C:/ti/ccsv6/ccs_base/msp430/include" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API/USB_Common" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib/MSP430F5xx_6xx" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/driverlib/MSP430F5xx_6xx/inc" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_API" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_app" --include_path="C:/Users/Jack/workspace_v6_1/cmpe652_msp430/minimac/USB_config" --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-msp430_4.4.4/include" --advice:power=all -g --define=__MSP430F5529__ --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="openssl/md5_one.pp" --obj_directory="openssl" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


