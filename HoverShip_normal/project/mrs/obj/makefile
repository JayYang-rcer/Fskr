################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include zf_driver/subdir.mk
-include zf_device/subdir.mk
-include zf_components/subdir.mk
-include zf_common/subdir.mk
-include user_c/subdir.mk
-include sdk/Startup/subdir.mk
-include sdk/Peripheral/subdir.mk
-include sdk/Core/subdir.mk
-include code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
HoverShip_normal.hex \

SECONDARY_LIST += \
HoverShip_normal.lst \

SECONDARY_SIZE += \
HoverShip_normal.siz \


# 所有目标
all: HoverShip_normal.elf secondary-outputs

# 工具调用
HoverShip_normal.elf: $(OBJS) $(USER_OBJS)
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -T "D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -L"../" -L"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -Wl,-Map,"HoverShip_normal.map" --specs=nano.specs -u _printf_float --specs=nosys.specs -Wl,--print-memory-usage -o "HoverShip_normal.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@	@
HoverShip_normal.hex: HoverShip_normal.elf
	@	riscv-none-embed-objcopy -O ihex "HoverShip_normal.elf"  "HoverShip_normal.hex"
	@	@
HoverShip_normal.lst: HoverShip_normal.elf
	@	riscv-none-embed-objdump --source --all-headers --demangle --line-numbers --wide "HoverShip_normal.elf" > "HoverShip_normal.lst"
	@	@
HoverShip_normal.siz: HoverShip_normal.elf
	@	riscv-none-embed-size --format=berkeley "HoverShip_normal.elf"
	@	@
# 其他目标
clean:
	-$(RM) $(ASM_UPPER_DEPS)$(OBJS)$(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE)$(ASM_DEPS)$(S_DEPS)$(S_UPPER_DEPS)$(C_DEPS) HoverShip_normal.elf
	-@
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
