################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
source/can.obj: ../source/can.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/can.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/dabort.obj: ../source/dabort.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/dabort.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/esm.obj: ../source/esm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/esm.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/gio.obj: ../source/gio.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/gio.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/md5.obj: ../source/md5.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/md5.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/minimac.obj: ../source/minimac.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/minimac.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/notification.obj: ../source/notification.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/notification.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/pinmux.obj: ../source/pinmux.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/pinmux.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/rti.obj: ../source/rti.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/rti.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sci.obj: ../source/sci.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sci.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sha1.obj: ../source/sha1.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sha1.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sha256.obj: ../source/sha256.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sha256.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_core.obj: ../source/sys_core.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_core.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_dma.obj: ../source/sys_dma.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_dma.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_intvecs.obj: ../source/sys_intvecs.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_intvecs.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_main.obj: ../source/sys_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_main.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_mpu.obj: ../source/sys_mpu.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_mpu.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_pcr.obj: ../source/sys_pcr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_pcr.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_phantom.obj: ../source/sys_phantom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_phantom.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_pmm.obj: ../source/sys_pmm.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_pmm.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_pmu.obj: ../source/sys_pmu.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_pmu.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_selftest.obj: ../source/sys_selftest.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_selftest.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_startup.obj: ../source/sys_startup.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_startup.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sys_vim.obj: ../source/sys_vim.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/sys_vim.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/system.obj: ../source/system.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/bin/armcl" -mv7R4 --code_state=32 --float_support=VFPv3D16 --include_path="G:/ti/ccsv6/tools/compiler/ti-cgt-arm_16.3.0.STS/include" --include_path="C:/Users/Jackson/Desktop/minimac/code/hercules/CAN_bench_network/include" -g --display_error_number --diag_wrap=off --diag_warning=225 --enum_type=packed --abi=eabi --preproc_with_compile --preproc_dependency="source/system.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


