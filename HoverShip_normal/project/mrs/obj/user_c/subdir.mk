################################################################################
# MRS Version: 1.9.1
# �Զ����ɵ��ļ�����Ҫ�༭��
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/user/src/isr.c \
D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/user/src/main.c 

OBJS += \
./user_c/isr.o \
./user_c/main.o 

C_DEPS += \
./user_c/isr.d \
./user_c/main.d 


# Each subdirectory must supply rules for building sources it contributes
user_c/isr.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/user/src/isr.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@
user_c/main.o: D:/�½��ļ���/19Feisi_CAR/HoverShip_normal/project/user/src/main.c
	@	@	riscv-none-embed-gcc -march=rv32imafc -mabi=ilp32f -msmall-data-limit=8 -mno-save-restore -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -pedantic -Wunused -Wuninitialized -Wall  -g -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\Libraries\doc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_components" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Core" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Ld" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Peripheral" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\sdk\Startup" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\user\inc" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_common" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_device" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\project\code" -I"D:\�½��ļ���\19Feisi_CAR\HoverShip_normal\libraries\zf_driver" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@	@

