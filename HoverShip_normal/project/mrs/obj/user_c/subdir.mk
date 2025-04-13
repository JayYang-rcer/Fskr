################################################################################
# MRS Version: 1.9.1
# 自动生成的文件。不要编辑！
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/user/src/isr.c \
D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/新建文件夹/19Feisi_CAR/HoverShip_normal/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\新建文件夹\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

