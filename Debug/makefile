################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./arrow_down_bitmap.obj" \
"./arrow_left_bitmap.obj" \
"./arrow_right_bitmap.obj" \
"./arrow_up_bitmap.obj" \
"./bopit_bitmap.obj" \
"./button1_bitmap.obj" \
"./button2_bitmap.obj" \
"./buzzer.obj" \
"./i2c.obj" \
"./lcd.obj" \
"./lightbulb_bitmap.obj" \
"./main.obj" \
"./startup_msp432p401r_ccs.obj" \
"./system_msp432p401r.obj" \
"./task_accelerometer.obj" \
"./task_action_timer.obj" \
"./task_amb_light.obj" \
"./task_bop_it.obj" \
"./task_buttons.obj" \
"./FreeRTOS/croutine.obj" \
"./FreeRTOS/event_groups.obj" \
"./FreeRTOS/heap_4.obj" \
"./FreeRTOS/list.obj" \
"./FreeRTOS/queue.obj" \
"./FreeRTOS/stream_buffer.obj" \
"./FreeRTOS/tasks.obj" \
"./FreeRTOS/timers.obj" \
"./FreeRTOS/portable/port.obj" \
"./FreeRTOS/portable/portasm.obj" \
"../msp432p401r.cmd" \
$(GEN_CMDS__FLAG) \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include FreeRTOS/subdir_vars.mk
-include FreeRTOS/portable/subdir_vars.mk
-include subdir_rules.mk
-include FreeRTOS/subdir_rules.mk
-include FreeRTOS/portable/subdir_rules.mk
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
final_project_v2.out \

EXE_OUTPUTS__QUOTED += \
"final_project_v2.out" \

BIN_OUTPUTS += \
final_project_v2.hex \

BIN_OUTPUTS__QUOTED += \
"final_project_v2.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "final_project_v2.out"

# Tool invocations
final_project_v2.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --advice:power=all --define=__MSP432P401R__ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi -z -m"final_project_v2.map" --heap_size=1024 --stack_size=512 -i"C:/ti/ccs1010/ccs/ccs_base/arm/include" -i"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/lib" -i"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="final_project_v2_linkInfo.xml" --rom_model -o "final_project_v2.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

final_project_v2.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs1010/ccs/tools/compiler/ti-cgt-arm_20.2.3.LTS/bin/armhex" --memwidth=8 --romwidth=8 -o "final_project_v2.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "arrow_down_bitmap.obj" "arrow_left_bitmap.obj" "arrow_right_bitmap.obj" "arrow_up_bitmap.obj" "bopit_bitmap.obj" "button1_bitmap.obj" "button2_bitmap.obj" "buzzer.obj" "i2c.obj" "lcd.obj" "lightbulb_bitmap.obj" "main.obj" "startup_msp432p401r_ccs.obj" "system_msp432p401r.obj" "task_accelerometer.obj" "task_action_timer.obj" "task_amb_light.obj" "task_bop_it.obj" "task_buttons.obj" "FreeRTOS\croutine.obj" "FreeRTOS\event_groups.obj" "FreeRTOS\heap_4.obj" "FreeRTOS\list.obj" "FreeRTOS\queue.obj" "FreeRTOS\stream_buffer.obj" "FreeRTOS\tasks.obj" "FreeRTOS\timers.obj" "FreeRTOS\portable\port.obj" "FreeRTOS\portable\portasm.obj" 
	-$(RM) "arrow_down_bitmap.d" "arrow_left_bitmap.d" "arrow_right_bitmap.d" "arrow_up_bitmap.d" "bopit_bitmap.d" "button1_bitmap.d" "button2_bitmap.d" "buzzer.d" "i2c.d" "lcd.d" "lightbulb_bitmap.d" "main.d" "startup_msp432p401r_ccs.d" "system_msp432p401r.d" "task_accelerometer.d" "task_action_timer.d" "task_amb_light.d" "task_bop_it.d" "task_buttons.d" "FreeRTOS\croutine.d" "FreeRTOS\event_groups.d" "FreeRTOS\heap_4.d" "FreeRTOS\list.d" "FreeRTOS\queue.d" "FreeRTOS\stream_buffer.d" "FreeRTOS\tasks.d" "FreeRTOS\timers.d" "FreeRTOS\portable\port.d" 
	-$(RM) "FreeRTOS\portable\portasm.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

